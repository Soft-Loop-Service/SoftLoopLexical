
#ifndef __PRAS
#define __PRAS

#include "./../LR_table/LR_table.hpp"
#include "./../LR_table/LR_table_definition.hpp"
#include "./../LR_table/LR_table_cell.hpp"
#include "./../syntactic/syntactic_analysis_tree.hpp"
#include "./process_analysis_definition.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

int operation_arithmetic_temp_count = 0;

void operationArithmetic(vSyntacticTree &process_stack, vProcessAnalysis &process_result)
{

    SyntacticTreeNode current_node = process_stack[process_stack.size() - 1];

    if (process_stack.size() < 2)
    {
        return;
    }

    if (current_node.node_type != syntactic_tree_node_type_operation_formula)
    {
        return;
    }

    SyntacticTreeNode node1 = process_stack[process_stack.size() - 2];
    SyntacticTreeNode node2 = process_stack[process_stack.size() - 3];

    for (int i = 0; i < 3; i++)
    {
        process_stack.erase(process_stack.end() - 1);
    }
    SyntacticTreeNode new_node = {"temp" + to_string(operation_arithmetic_temp_count), is_id_TerminalSymbol, {}, syntactic_tree_node_type_number};
    process_stack.push_back(new_node);

    ProcessAnalysisCalculation pa = ProcessAnalysisCalculation(current_node.token);

    printf("%s : %s %s\n", ("temp" + to_string(operation_arithmetic_temp_count)).c_str(), node2.token.c_str(), node1.token.c_str());
    pa.setVariable(ProcessVariable("temp" + to_string(operation_arithmetic_temp_count)), ProcessVariable(node2.token), ProcessVariable(node1.token));
    process_result.push_back(pa);
    operation_arithmetic_temp_count++;

    // if (current_node.token == "+")
    // {
    //     int calc = n2 + n1;

    //     SyntacticTreeNode new_node = {to_string(calc), is_id_TerminalSymbol, {}, syntactic_tree_node_type_number};
    //     process_stack.push_back(new_node);

    //     printf("ope : %d + %d = %d\n", n2, n1, calc);
    //     // operationAddition(current_node, process);
    //     return;
    // }
    // if (current_node.token == "-")
    // {
    //     int calc = n2 - n1;

    //     SyntacticTreeNode new_node = {to_string(calc), is_id_TerminalSymbol, {}, syntactic_tree_node_type_number};
    //     process_stack.push_back(new_node);
    //     printf("ope : %d - %d = %d\n", n2, n1, calc);

    //     // operationSubtraction(current_node, process);
    //     return;
    // }
    // if (current_node.token == "*")
    // {
    //     int calc = n2 * n1;

    //     SyntacticTreeNode new_node = {to_string(calc), is_id_TerminalSymbol, {}, syntactic_tree_node_type_number};
    //     process_stack.push_back(new_node);
    //     printf("ope : %d * %d = %d\n", n2, n1, calc);

    //     // operationMultiplication(current_node, process);
    //     return;
    // }
    // if (current_node.token == "/")
    // {
    //     int calc = n2 / n1;

    //     SyntacticTreeNode new_node = {to_string(calc), is_id_TerminalSymbol, {}, syntactic_tree_node_type_number};
    //     process_stack.push_back(new_node);
    //     printf("ope : %d / %d = %d\n", n2, n1, calc);

    //     // operationSubtraction(current_node, process);
    //     return;
    // }
}

// int operationAddition(SyntacticTreeNode current_node, vSyntacticTree &process)
// {
// }

// int operationSubtraction(SyntacticTreeNode current_node, vSyntacticTree &process)
// {
// }

// int operationMultiplication(SyntacticTreeNode current_node, vSyntacticTree &process)
// {
// }

// int operationDivision(SyntacticTreeNode current_node, vSyntacticTree &process)
// {
// }

#endif