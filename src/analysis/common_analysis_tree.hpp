
#ifndef __CYNTDT
#define __CYNTDT

// 解析木

#include "./../LR_table/LR_table.hpp"
#include "./../LR_table/LR_table_definition.hpp"
#include "./../LR_table/LR_table_cell.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

struct SyntacticTreeNode // 構文解析用
{
    string token;
    int token_label;
    vint children;
    string parent_token;
};
typedef vector<SyntacticTreeNode> vSyntacticTree;

/// @brief
/// @param syntactic_analysis_tree
/// @param syntactic_analysis_formula
/// @param search_first_index 後ろから探索しているという条件で、探索済みの場所の先端の1つ手前
/// @param depth 深さ
void recursionSyntacticAnalysisTreeDFS(vSyntacticTree &syntactic_analysis_tree, vReduceFormula &syntactic_analysis_formula, int &search_first_index, int parent_node_index, int depth) // 導出木に変換するため深さ優先探索を行う。その地点で木構造に分類する。つまり細かく木構造に分割していくイメージ。
{

    printf("探索 現在:%d 親:%d\n", search_first_index, parent_node_index);

    ReduceFormula current_reduce_formula = syntactic_analysis_formula[search_first_index];

    struct SyntacticTreeNode new_node_nonterminal = {
        current_reduce_formula.token_left,
        is_id_NonterminalSymbol,
        {}};

    syntactic_analysis_tree.push_back(new_node_nonterminal);

    int new_current_index = syntactic_analysis_tree.size() - 1;

    int size = current_reduce_formula.token_vector.size();
    if (parent_node_index >= 0)
    {
        auto it_0 = syntactic_analysis_tree[parent_node_index].children.begin();
        syntactic_analysis_tree[parent_node_index].children.insert(it_0, new_current_index);
        syntactic_analysis_tree[new_current_index].parent_token = syntactic_analysis_tree[parent_node_index].token;

        printf("接続 %d - %d\n", parent_node_index, new_current_index);
    }

    // 親ノードがnumberであるならば、末端記号ノードも数字である。

    for (int i = size - 1; i >= 0; i--)
    {
        DeploymentTokenStruct bnf = current_reduce_formula.token_vector[i];

        if (bnf.label == is_id_TerminalSymbol)
        {

            // int node_type = getSyntacticAnalysisTreeNodeType(current_reduce_formula.token_left, bnf.token_str);

            printf("node_type : %s\n", current_reduce_formula.token_left.c_str());

            struct SyntacticTreeNode new_node_terminal = {bnf.token_str, is_id_TerminalSymbol, {}, current_reduce_formula.token_left};
            syntactic_analysis_tree.push_back(new_node_terminal);

            auto it_p = syntactic_analysis_tree[new_current_index].children.begin();
            syntactic_analysis_tree[new_current_index].children.insert(it_p, syntactic_analysis_tree.size() - 1);
            continue;
        }

        search_first_index--;

        recursionSyntacticAnalysisTreeDFS(syntactic_analysis_tree, syntactic_analysis_formula, search_first_index, new_current_index, (depth + 1));
    }
}

void debugSyntacticAnalysisTree(vSyntacticTree &syntactic_analysis_tree)
{
    for (int i = 0; i < syntactic_analysis_tree.size(); i++)
    {
        SyntacticTreeNode node = syntactic_analysis_tree[i];

        printf("node %d * * * * \n", i);
        printf("token %s\n", node.token.c_str());
        printf("token label %d\n", node.token_label);
        printf("parent token %s\n", node.parent_token.c_str());

        printf("children ");
        for (int j = 0; j < node.children.size(); j++)
        {
            printf("%d ", node.children[j]);
        }

        printf("\n\n");
    }
}

void commonAnalysisTree(vReduceFormula syntactic_analysis_formula, vSyntacticTree &syntactic_analysis_tree)
{

    // syntactic_analysis_formulaは構文解析の結果 後ろから見ていくことで木構造を構築する

    int size = syntactic_analysis_formula.size();
    int last = size - 1;

    recursionSyntacticAnalysisTreeDFS(syntactic_analysis_tree, syntactic_analysis_formula, last, -1, 0);
    debugSyntacticAnalysisTree(syntactic_analysis_tree);
}

#endif