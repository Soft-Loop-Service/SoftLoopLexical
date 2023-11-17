
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

class SoftjTree
{

private:
    vSyntacticTree *syntactic_analysis_tree;
    vProcessAnalysis *process_result;
    VariablePossessionControl vpc;

    template <class T>
    void assExpr(T value, int node_index, int &address, int &size)
    {

        SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
        SyntacticTreeNode child_left = (*syntactic_analysis_tree)[current_node.children[0]];
        SyntacticTreeNode child_right = (*syntactic_analysis_tree)[current_node.children[1]];

        printf("assExpr %d %d %d %s\n", node_index, current_node.children[0], current_node.children[1], current_node.token.c_str());

        if (current_node.token == "<value_definition>")
        {
            printf("a\n");
            VariablePossession<T> *vp_t;
            printf("b\n");

            vpc.getPointer(vp_t);
            printf("c\n");

            vp_t->add(value, address, size);
            printf("d\n");

            string message = "変数定義代入 " + child_right.token + " " + to_string(value);
            struct ProcessAnalysis pr = {message};
            process_result->push_back(pr);
        }
    }

    int equal(int node_index)
    {
        SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
        SyntacticTreeNode child_left = (*syntactic_analysis_tree)[current_node.children[0]];
        SyntacticTreeNode child_right = (*syntactic_analysis_tree)[current_node.children[1]];

        int address;
        int size;
        int right;
        right = calc(current_node.children[1]);
        assExpr(right, current_node.children[0], address, size);
    }
    int addition(int left, int right)
    {
        string message = "加算 " + to_string(left) + " + " + to_string(right);
        struct ProcessAnalysis pr = {message};
        process_result->push_back(pr);

        return left + right;
    }
    int subtraction(int left, int right)
    {
        string message = "減算 " + to_string(left) + " - " + to_string(right);
        struct ProcessAnalysis pr = {message};
        process_result->push_back(pr);
        return left - right;
    }
    int multiplication(int left, int right)
    {
        string message = "乗算 " + to_string(left) + " * " + to_string(right);
        struct ProcessAnalysis pr = {message};
        process_result->push_back(pr);
        return left * right;
    }
    int division(int left, int right)
    {
        string message = "割算 " + to_string(left) + " / " + to_string(right);
        struct ProcessAnalysis pr = {message};
        process_result->push_back(pr);
        return left / right;
    }

    int calc(int node_index)
    {

        SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
        if (current_node.parent_token == "<number>")
        {
            return stoi(current_node.token);
        }

        SyntacticTreeNode child_left = (*syntactic_analysis_tree)[current_node.children[0]];
        SyntacticTreeNode child_right = (*syntactic_analysis_tree)[current_node.children[1]];

        int left;
        int right;

        left = calc(current_node.children[0]);
        right = calc(current_node.children[1]);

        int ans;

        string token = current_node.token;
        const char *token_c = token.c_str();

        switch (*token_c)
        {
        case '+':
        {
            ans = addition(left, right);
            break;
        }
        case '-':
        {
            ans = subtraction(left, right);
            break;
        }
        case '*':
        {
            ans = multiplication(left, right);
            break;
        }
        case '/':
        {
            ans = division(left, right);
            break;
        }
        }

        printf("calcSoftjTree %d : %d %d\n", ans, left, right);

        return ans;
    }

    int recursion(int node_index)
    {
        SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];

        // char *text = current_node.token.c_str();

        string token = current_node.token;
        const char *token_c = token.c_str();

        switch (*token_c)
        {
        case '=':
        {
            equal(node_index);
            break;
        }
        case '+':
        case '-':
        case '*':
        case '/':
        {
            calc(node_index);
            break;
        }
        default:
        {

            for (int i = 0; i < current_node.children.size(); i++)
            {
                recursion(current_node.children[i]);
            }
            break;
        }
        }
    }

public:
    SoftjTree(vSyntacticTree &syntactic_analysis_tree, vProcessAnalysis &process_result , VariablePossessionControl &vpc)
    {
        this->syntactic_analysis_tree = &syntactic_analysis_tree;
        this->process_result = &process_result;
        this->vpc = vpc;

        recursion(0);
    }
};

#endif