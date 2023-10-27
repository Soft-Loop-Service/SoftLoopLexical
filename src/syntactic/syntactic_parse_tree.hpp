
#ifndef __SYNTPT
#define __SYNTPT

// 構文木

#include "./../LR_table/LR_table.hpp"
#include "./../LR_table/LR_table_definition.hpp"
#include "./../LR_table/LR_table_cell.hpp"
#include "./syntactic_analysis_tree.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

// 子どもが1つしかない場合に縮小する関数
int recursionCutSyntacticParseTree(vSyntacticTree &syntactic_parse_tree, int current_node_index)
{
    SyntacticTreeNode current_node = syntactic_parse_tree[current_node_index];

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

    for (int i = 0; i < current_node.children.size(); i++)
    {
        int child = current_node.children[i];
        int new_child = recursionCutSyntacticParseTree(syntactic_parse_tree, child);

        printf("node %d child change %d -> %d\n", current_node_index, child, new_child);

        syntactic_parse_tree[current_node_index].children[i] = new_child;

        recursionSyntacticParseTree(syntactic_parse_tree, new_child);
    }
}

void syntacticParseTree(vSyntacticTree &syntactic_parse_tree)
{
    recursionSyntacticParseTree(syntactic_parse_tree, 0);
    debugSyntacticAnalysisTree(syntactic_parse_tree);
}

#endif