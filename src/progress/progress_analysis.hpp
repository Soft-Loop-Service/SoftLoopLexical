
#ifndef __PRA
#define __PRA

#include "./../LR_table/LR_table.hpp"
#include "./../LR_table/LR_table_definition.hpp"
#include "./../LR_table/LR_table_cell.hpp"
#include "./../syntactic/syntactic_analysis_tree.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "./../../bnf_syntax/softj/softj.hpp"

void recursionProgressAnalysis(vSyntacticTree &syntactic_analysis_tree, vSyntacticTree &progress, vint parent_stack, int current_node_index)
{
    SyntacticTreeNode current_node = syntactic_analysis_tree[current_node_index];
    softj(syntactic_analysis_tree, progress, parent_stack, current_node_index);
    parent_stack.push_back(current_node_index);
    for (int i = 0; i < current_node.children.size(); i++)
    {
        int child = current_node.children[i];
        recursionProgressAnalysis(syntactic_analysis_tree, progress, parent_stack, child);
    }

    // if (current_node.token_label == is_id_TerminalSymbol)
    // {
    //     progress.push_back(current_node);
    // }
}
void progressAnalysis(vSyntacticTree syntactic_analysis_tree)
{
    printf("progressAnalysis\n");
    vSyntacticTree progress = {};
    vint parent_stack = {};
    recursionProgressAnalysis(syntactic_analysis_tree, progress, parent_stack, 0);
    debugSyntacticAnalysisTree(progress);
}

#endif