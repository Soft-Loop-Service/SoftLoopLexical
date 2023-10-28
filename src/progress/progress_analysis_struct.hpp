
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

void operationsArithmetic(SyntacticTreeNode current_node, vSyntacticTree &progress)
{

    if (progress.size() < 2)
    {
        return;
    }

    if (current_node.token != "+" && current_node.token != "-" && current_node.token != "*" && current_node.token != "/")
    {
        return;
    }

    SyntacticTreeNode node1 = progress[progress.size() - 1];
    SyntacticTreeNode node2 = progress[progress.size() - 2];
    if (node1.node_type != syntactic_tree_node_type_number || node2.node_type != syntactic_tree_node_type_number)
    {
        return;
    }

    progress.erase(progress.end() - 1);
    progress.erase(progress.end() - 1);

    printf("ope calc: %s %s %s\n", current_node.token.c_str(), node1.token.c_str(), node2.token.c_str());

    int n1 = stoi(node1.token);
    int n2 = stoi(node2.token);

    if (current_node.token == "+")
    {
        int calc = n1 + n2;

        SyntacticTreeNode new_node = {to_string(calc), is_id_TerminalSymbol, {}};
        progress.push_back(new_node);

        printf("ope : %d + %d = %d\n", n1, n2, calc);
        // operationAddition(current_node, progress);
        return;
    }
    if (current_node.token == "-")
    {
        int calc = n1 - n2;

        SyntacticTreeNode new_node = {to_string(calc), is_id_TerminalSymbol, {}};
        progress.push_back(new_node);
        printf("ope : %d - %d = %d\n", n1, n2, calc);

        // operationSubtraction(current_node, progress);
        return;
    }
    if (current_node.token == "*")
    {
        int calc = n1 * n2;

        SyntacticTreeNode new_node = {to_string(calc), is_id_TerminalSymbol, {}};
        progress.push_back(new_node);
        printf("ope : %d * %d = %d\n", n1, n2, calc);

        // operationMultiplication(current_node, progress);
        return;
    }
    if (current_node.token == "/")
    {
        int calc = n1 / n2;

        SyntacticTreeNode new_node = {to_string(calc), is_id_TerminalSymbol, {}};
        progress.push_back(new_node);
        printf("ope : %d / %d = %d\n", n1, n2, calc);

        // operationSubtraction(current_node, progress);
        return;
    }
}

// int operationAddition(SyntacticTreeNode current_node, vSyntacticTree &progress)
// {
// }

// int operationSubtraction(SyntacticTreeNode current_node, vSyntacticTree &progress)
// {
// }

// int operationMultiplication(SyntacticTreeNode current_node, vSyntacticTree &progress)
// {
// }

// int operationDivision(SyntacticTreeNode current_node, vSyntacticTree &progress)
// {
// }

#endif