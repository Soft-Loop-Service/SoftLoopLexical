
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
#include "./process_analysis_operation.hpp"
#include "./process_analysis_definition.hpp"

void recursionProcessAnalysis(vSyntacticTree &syntactic_analysis_tree, vSyntacticTree &process_stack, vProcessAnalysis &process_result, vint parent_stack, int current_node_index)
{
    SyntacticTreeNode current_node = syntactic_analysis_tree[current_node_index];
    // softj(syntactic_analysis_tree, process, parent_stack, current_node_index);

    for (int i = 0; i < current_node.children.size(); i++)
    {
        int child = current_node.children[i];
        recursionProcessAnalysis(syntactic_analysis_tree, process_stack, process_result, parent_stack, child);
    }

    parent_stack.push_back(current_node_index);

    if (current_node.token_label == is_id_TerminalSymbol)
    {
        // printf("スタックへの追加 %s\n", current_node.token.c_str());
        process_stack.push_back(current_node);
        operationProcessArithmetic(process_stack, process_result);
        operationProcessNewValue(process_stack, process_result);
    }
}

void debugProcessResult(vProcessAnalysis process_result)
{
    for (int i = 0; i < process_result.size(); i++)
    {

        process_result[i].process();
    }
}

void processAnalysis(vSyntacticTree syntactic_analysis_tree)
{
    printf("processAnalysis\n");
    vSyntacticTree process = {};
    vint parent_stack = {};
    vProcessAnalysis process_result = {};
    recursionProcessAnalysis(syntactic_analysis_tree, process, process_result, parent_stack, 0);
    debugSyntacticAnalysisTree(process);
    debugProcessResult(process_result);
}

#endif