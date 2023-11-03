
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

void operationProcessNewValue(vSyntacticTree &process_stack, vProcessAnalysis &process_result)
{
    if (process_stack.size() < 2)
    {
        return;
    }
    SyntacticTreeNode node1 = process_stack[process_stack.size() - 1];
    SyntacticTreeNode node2 = process_stack[process_stack.size() - 2];

    if (node2.node_type != syntactic_tree_node_type_valuetype)
    {
        return;
    }
    if (node1.node_type != syntactic_tree_node_type_valuename)
    {
        return;
    }
    process_stack.erase(process_stack.end() - 2);

    ProcessAnalysisNewVal pa = ProcessAnalysisNewVal();
    pa.setVariable(ProcessVariable("new val"), ProcessVariable(node2.token), ProcessVariable(node1.token));
    process_result.push_back(pa);
}
int operation_arithmetic_temp_count = 0;

void operationProcessArithmetic(vSyntacticTree &process_stack, vProcessAnalysis &process_result)
{

    SyntacticTreeNode current_node = process_stack[process_stack.size() - 1];

    if (process_stack.size() < 3)
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

    string temp_name = "temp" + to_string(operation_arithmetic_temp_count);
    SyntacticTreeNode new_node = {temp_name, is_id_TerminalSymbol, {}, syntactic_tree_node_type_number};
    process_stack.push_back(new_node);

    ProcessAnalysisCalculation pa = ProcessAnalysisCalculation(current_node.token);
    pa.setVariable(ProcessVariable(temp_name), ProcessVariable(node2.token), ProcessVariable(node1.token));
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