
#ifndef __SOFTJTREE
#define __SOFTJTREE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "./../../src/syntactic/syntactic_analysis_tree.hpp"
#include "./../../src/process/process_analysis_definition.hpp"

int equalSoftjTree(vSyntacticTree &syntactic_analysis_tree, vProcessAnalysis &process_result, int node_index)
{
    SyntacticTreeNode current_node = syntactic_analysis_tree[node_index];
}
int additionSoftjTree(vSyntacticTree &syntactic_analysis_tree, vProcessAnalysis &process_result, int left, int right)
{
    string message = "加算 " + to_string(left) + " + " + to_string(right);
    struct ProcessAnalysis pr = {message};
    process_result.push_back(pr);

    return left + right;
}
int subtractionSoftjTree(vSyntacticTree &syntactic_analysis_tree, vProcessAnalysis &process_result, int left, int right)
{
    string message = "減算 " + to_string(left) + " - " + to_string(right);
    struct ProcessAnalysis pr = {message};
    process_result.push_back(pr);
    return left - right;
}
int multiplicationSoftjTree(vSyntacticTree &syntactic_analysis_tree, vProcessAnalysis &process_result, int left, int right)
{
    string message = "乗算 " + to_string(left) + " * " + to_string(right);
    struct ProcessAnalysis pr = {message};
    process_result.push_back(pr);
    return left * right;
}
int divisionSoftjTree(vSyntacticTree &syntactic_analysis_tree, vProcessAnalysis &process_result, int left, int right)
{
    string message = "減算 " + to_string(left) + " / " + to_string(right);
    struct ProcessAnalysis pr = {message};
    process_result.push_back(pr);
    return left / right;
}

int calcSoftjTree(vSyntacticTree &syntactic_analysis_tree, vProcessAnalysis &process_result, int node_index)
{

    SyntacticTreeNode current_node = syntactic_analysis_tree[node_index];
    SyntacticTreeNode child_left = syntactic_analysis_tree[current_node.children[0]];
    SyntacticTreeNode child_right = syntactic_analysis_tree[current_node.children[1]];

    int left;
    int right;

    if (child_left.token_label == is_id_TerminalSymbol)
    {
        left = stoi(child_left.token);
    }
    if (child_right.token_label == is_id_TerminalSymbol)
    {
        right = stoi(child_right.token);
    }
    if (child_left.token_label == is_id_NonterminalSymbol)
    {
        left = calcSoftjTree(syntactic_analysis_tree, process_result, current_node.children[0]);
    }
    if (child_right.token_label == is_id_NonterminalSymbol)
    {
        right = calcSoftjTree(syntactic_analysis_tree, process_result, current_node.children[1]);
    }
    int ans;

    string token = current_node.token;
    const char *token_c = token.c_str();

    switch (*token_c)
    {
    case '+':
    {
        ans = additionSoftjTree(syntactic_analysis_tree, process_result, left, right);
        break;
    }
    case '-':
    {
        ans = subtractionSoftjTree(syntactic_analysis_tree, process_result, left, right);
        break;
    }
    case '*':
    {
        ans = multiplicationSoftjTree(syntactic_analysis_tree, process_result, left, right);
        break;
    }
    case '/':
    {
        ans = divisionSoftjTree(syntactic_analysis_tree, process_result, left, right);
        break;
    }
    }

    printf("calcSoftjTree %d = %d %d\n", ans, left, right);

    return ans;
}

int recursionSoftjTree(vSyntacticTree &syntactic_analysis_tree, vProcessAnalysis &process_result, int node_index)
{
    SyntacticTreeNode current_node = syntactic_analysis_tree[node_index];

    // char *text = current_node.token.c_str();

    string token = current_node.token;
    const char *token_c = token.c_str();

    switch (*token_c)
    {
    case '=':
    {
        equalSoftjTree(syntactic_analysis_tree, process_result, node_index);
        break;
    }
    case '+':
    case '-':
    case '*':
    case '/':
    {
        calcSoftjTree(syntactic_analysis_tree, process_result, node_index);
        break;
    }
    default:
    {

        for (int i = 0; i < current_node.children.size(); i++)
        {
            recursionSoftjTree(syntactic_analysis_tree, process_result, current_node.children[i]);
        }
        break;
    }
    }
}

int softjTree(vSyntacticTree &syntactic_analysis_tree, vProcessAnalysis &process_result)
{
    recursionSoftjTree(syntactic_analysis_tree, process_result, 0);
}

#endif