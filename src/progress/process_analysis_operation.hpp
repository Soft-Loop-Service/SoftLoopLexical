
#ifndef __PRAS
#define __PRAS

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

void operationArithmetic(vSyntacticTree &process_stack)
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
    if (node1.node_type != syntactic_tree_node_type_number || node2.node_type != syntactic_tree_node_type_number)
    {
        // printf("node_type %d %d\n", node1.node_type, node2.node_type);
        return;
    }

    for (int i = 0; i < 3; i++)
    {
        process_stack.erase(process_stack.end() - 1);
    }

    // printf("ope calc: %s %s %s\n", current_node.token.c_str(), node1.token.c_str(), node2.token.c_str());

    int n1 = stoi(node1.token);
    int n2 = stoi(node2.token);

    if (current_node.token == "+")
    {
        int calc = n2 + n1;

        SyntacticTreeNode new_node = {to_string(calc), is_id_TerminalSymbol, {}, syntactic_tree_node_type_number};
        process_stack.push_back(new_node);

        printf("ope : %d + %d = %d\n", n2, n1, calc);
        // operationAddition(current_node, process);
        return;
    }
    if (current_node.token == "-")
    {
        int calc = n2 - n1;

        SyntacticTreeNode new_node = {to_string(calc), is_id_TerminalSymbol, {}, syntactic_tree_node_type_number};
        process_stack.push_back(new_node);
        printf("ope : %d - %d = %d\n", n2, n1, calc);

        // operationSubtraction(current_node, process);
        return;
    }
    if (current_node.token == "*")
    {
        int calc = n2 * n1;

        SyntacticTreeNode new_node = {to_string(calc), is_id_TerminalSymbol, {}, syntactic_tree_node_type_number};
        process_stack.push_back(new_node);
        printf("ope : %d * %d = %d\n", n2, n1, calc);

        // operationMultiplication(current_node, process);
        return;
    }
    if (current_node.token == "/")
    {
        int calc = n2 / n1;

        SyntacticTreeNode new_node = {to_string(calc), is_id_TerminalSymbol, {}, syntactic_tree_node_type_number};
        process_stack.push_back(new_node);
        printf("ope : %d / %d = %d\n", n2, n1, calc);

        // operationSubtraction(current_node, process);
        return;
    }
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