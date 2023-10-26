
#ifndef __SYNTPT
#define __SYNTPT

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
    // int parent;
};
typedef vector<SyntacticTreeNode> vSyntacticTree;

/// @brief
/// @param syntactic_tree
/// @param syntactic_analysis_formula
/// @param search_first_index 後ろから探索しているという条件で、探索済みの場所の先端の1つ手前
/// @param depth 深さ
void recursionSyntacticPurseTreeDFS(vSyntacticTree &syntactic_tree, vReduceFormula &syntactic_analysis_formula, int &search_first_index, int parent_node_index, int depth) // 導出木に変換するため深さ優先探索を行う。その地点で木構造に分類する。つまり細かく木構造に分割していくイメージ。
{
    ReduceFormula current_reduce_formula = syntactic_analysis_formula[search_first_index];
    int size = current_reduce_formula.token_vector.size();

    struct SyntacticTreeNode new_node_nonterminal = {current_reduce_formula.token_left, is_id_NonterminalSymbol, {}};
    syntactic_tree.push_back(new_node_nonterminal);
    int new_parent_node_index = syntactic_tree.size() - 1;

    if (parent_node_index >= 0)
    {
        syntactic_tree[parent_node_index].children.push_back(new_parent_node_index);
        printf("接続 %d - %d\n", parent_node_index, new_parent_node_index);
    }

    for (int i = size - 1; i >= 0; i--)
    {
        DeploymentTokenStruct bnf = current_reduce_formula.token_vector[i];

        if (bnf.label == is_id_TerminalSymbol)
        {
            struct SyntacticTreeNode new_node_terminal = {bnf.token_str, is_id_TerminalSymbol, {}};
            syntactic_tree.push_back(new_node_terminal);
            syntactic_tree[new_parent_node_index].children.push_back(syntactic_tree.size() - 1);
            continue;
        }

        search_first_index--;
        int new_current_index = search_first_index;
        recursionSyntacticPurseTreeDFS(syntactic_tree, syntactic_analysis_formula, search_first_index, new_parent_node_index, (depth + 1));
    }
}

void debugSyntacticPurseTree(vSyntacticTree &syntactic_tree)
{
    for (int i = 0; i < syntactic_tree.size(); i++)
    {
        SyntacticTreeNode node = syntactic_tree[i];

        printf("node %d * * * * \n", i);
        printf("token %s\n", node.token.c_str());
        printf("token label %d\n", node.token_label);

        printf("children ");
        for (int j = 0; j < node.children.size(); j++)
        {
            printf("%d ", node.children[j]);
        }

        printf("\n\n");
    }
}

void syntacticPurseTree(LRTableMultilayer LR_table_multilayer, vstring token_string_vector, vReduceFormula syntactic_analysis_formula, vSyntacticTree &syntactic_tree)
{

    // syntactic_analysis_formulaは構文解析の結果 後ろから見ていくことで木構造を構築する

    int size = syntactic_analysis_formula.size() - 1;

    recursionSyntacticPurseTreeDFS(syntactic_tree, syntactic_analysis_formula, size, -1, 0);
    debugSyntacticPurseTree(syntactic_tree);
}

#endif