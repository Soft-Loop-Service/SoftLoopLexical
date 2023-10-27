
#ifndef __SYNTPT
#define __SYNTPT

// 構文木

#include "./../LR_table/LR_table.hpp"
#include "./../LR_table/LR_table_definition.hpp"
#include "./../LR_table/LR_table_cell.hpp"
#include "./syntactic_analysis_tree.hpp"
#include "./../../bnf_syntax/softj/softj.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

bool isTokenExpr(string token_str)
{
    const char *token = token_str.c_str();

    if (strchr("=+=/*", token[0]) != 0)
    {
        printf("isTokenExpr\n");
        return true;
    }

    return false;
}

// 子どものが四則演算であって、二分木にすべきかどうかの判断
int isCutExpr(vSyntacticTree &syntactic_parse_tree, int current_node_index)
{
    SyntacticTreeNode current_node = syntactic_parse_tree[current_node_index];

    for (int i = 0; i < current_node.children.size(); i++)
    {
        int child = current_node.children[i];
        SyntacticTreeNode child_node = syntactic_parse_tree[child];
        if (child_node.token_label == is_id_TerminalSymbol && isTokenExpr(child_node.token))
        {
            return child;
        }
    }

    return -1;

    // if (current_node.children.size() != 3)
    // {
    //     return -1;
    // }

    // int child1 = current_node.children[1];
    // SyntacticTreeNode child1_node = syntactic_parse_tree[child1];

    // if (!child1_node.token_label == is_id_TerminalSymbol || !isTokenExpr(child1_node.token))
    // {
    //     return -1;
    // }

    // return child1;
}

int cutExpr(vSyntacticTree &syntactic_parse_tree, int current_node_index)
{
    SyntacticTreeNode current_node = syntactic_parse_tree[current_node_index];
    int is_cut = isCutExpr(syntactic_parse_tree, current_node_index);
    if (is_cut == -1)
    {
        return current_node_index;
    }
    SyntacticTreeNode new_node = syntactic_parse_tree[is_cut];
    new_node.children = current_node.children;

    printf("二分木構築 %d -> %d %d %d\n", current_node_index, is_cut, syntactic_parse_tree.size(), new_node.children.size());
    auto it = new_node.children.begin();
    it += 1;
    new_node.children.erase(it);
    syntactic_parse_tree[current_node_index] = new_node;
}
// 四則演算および代入の二分木化
int recursionCutExpr(vSyntacticTree &syntactic_parse_tree, int current_node_index)
{
    cutExpr(syntactic_parse_tree, current_node_index);

    for (int i = 0; i < syntactic_parse_tree[current_node_index].children.size(); i++)
    {
        recursionCutExpr(syntactic_parse_tree, syntactic_parse_tree[current_node_index].children[i]);
    }
}

// 子どもが1つしかない場合に縮小する関数
int recursionCutSyntacticParseTree(vSyntacticTree &syntactic_parse_tree, int current_node_index)
{
    SyntacticTreeNode current_node = syntactic_parse_tree[current_node_index];

    if (current_node.children.size() == 0 && current_node.token_label != is_id_TerminalSymbol)
    {
        return -1;
    }

    if (current_node.children.size() != 1)
    {
        return current_node_index;
    }

    int child = current_node.children[0];

    int late = recursionCutSyntacticParseTree(syntactic_parse_tree, child);

    return late;
}

void recursionSyntacticParseTree(vSyntacticTree &syntactic_parse_tree, int current_node_index)
{
    printf("recursionSyntacticParseTree %d\n", current_node_index);

    SyntacticTreeNode current_node = syntactic_parse_tree[current_node_index];

    int i = 0;
    while (i < syntactic_parse_tree[current_node_index].children.size())
    {
        int child = syntactic_parse_tree[current_node_index].children[i];
        int new_child = recursionCutSyntacticParseTree(syntactic_parse_tree, child);

        printf("node %d %d child change %d -> %d\n", current_node_index, i, child, new_child);

        if (new_child == -1)
        {
            auto it = syntactic_parse_tree[current_node_index].children.begin();
            it += i;
            syntactic_parse_tree[current_node_index].children.erase(it);
            continue;
        }

        syntactic_parse_tree[current_node_index].children[i] = new_child;

        recursionSyntacticParseTree(syntactic_parse_tree, new_child);

        i++;
    }
}

void syntacticParseTree(vSyntacticTree &syntactic_parse_tree)
{
    recursionSyntacticParseTree(syntactic_parse_tree, 0);
    recursionCutExpr(syntactic_parse_tree, 0);
    debugSyntacticAnalysisTree(syntactic_parse_tree);
}

#endif