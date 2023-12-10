
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
    VariablePossessionUnion *vpc;

    template <class T>
    void assExpr(T value, int node_index, int &size)
    {

        SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];

        if (current_node.token == "<value_definition>")
        {
            printf("assExpr %d %d %d %s\n", node_index, current_node.children[0], current_node.children[1], current_node.token.c_str());

            SyntacticTreeNode child_left = (*syntactic_analysis_tree)[current_node.children[0]];
            SyntacticTreeNode child_right = (*syntactic_analysis_tree)[current_node.children[1]];

            string value_name = child_right.token;
            vpc->add(value, value_name, size);

            // vpc[0]->add(value, address, size);
            printf("d\n");

            string message = "変数定義代入 " + child_right.token + " " + to_string(value);
            struct ProcessAnalysis pr = {message};
            process_result->push_back(pr);

            return;
        }

        if (current_node.parent_token == "<value_name>")
        {
            string value_name = current_node.token;
            vpc->add(value, value_name, size);
            string message = "変数代入 " + current_node.token + " " + to_string(value);
            struct ProcessAnalysis pr = {message};
            process_result->push_back(pr);
            return;
        }
    }

    bool getBool(int val)
    {
        return val > 0;
    }

    int functionCalc(int node_index)
    {
    }

    int whileCalc(int node_index)
    {
        SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
        SyntacticTreeNode child0 = (*syntactic_analysis_tree)[current_node.children[0]];
        // SyntacticTreeNode child1 = (*syntactic_analysis_tree)[current_node.children[1]];
        // SyntacticTreeNode child2 = (*syntactic_analysis_tree)[current_node.children[2]];

        int calc_ans = calc(current_node.children[1]);
        bool ifbool = getBool(calc_ans);

        while (ifbool)
        {
            string message = "ループ条件式 true";
            struct ProcessAnalysis pr = {message};
            process_result->push_back(pr);
            recursion(current_node.children[2]);
            calc_ans = calc(current_node.children[1]);
            ifbool = getBool(calc_ans);
        }

        string message = "ループ条件式 false";
        struct ProcessAnalysis pr = {message};
        process_result->push_back(pr);
    }

    int ifCalc(int node_index)
    {
        SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
        SyntacticTreeNode child0 = (*syntactic_analysis_tree)[current_node.children[0]];
        // SyntacticTreeNode child1 = (*syntactic_analysis_tree)[current_node.children[1]];
        // SyntacticTreeNode child2 = (*syntactic_analysis_tree)[current_node.children[2]];
        int calc_ans = calc(current_node.children[1]);

        bool ifbool = getBool(calc_ans);

        if (ifbool)
        {
            string message = "条件式 true";
            struct ProcessAnalysis pr = {message};
            process_result->push_back(pr);
            recursion(current_node.children[2]);
        }
        else
        {
            string message = "条件式 false";
            struct ProcessAnalysis pr = {message};
            process_result->push_back(pr);
        }
    }

    int equal(int node_index)
    {

        SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
        SyntacticTreeNode child_left = (*syntactic_analysis_tree)[current_node.children[0]];
        SyntacticTreeNode child_right = (*syntactic_analysis_tree)[current_node.children[1]];

        int size;
        int right;
        right = calc(current_node.children[1]);
        assExpr(right, current_node.children[0], size);
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
    int less(int left, int right)
    {
        string message = "比較 " + to_string(left) + " < " + to_string(right);
        struct ProcessAnalysis pr = {message};
        process_result->push_back(pr);
        return left < right;
    }
    int less_equal(int left, int right)
    {
        string message = "比較 " + to_string(left) + " <= " + to_string(right);
        struct ProcessAnalysis pr = {message};
        process_result->push_back(pr);
        return left <= right;
    }
    int greater(int left, int right)
    {
        string message = "比較 " + to_string(left) + " > " + to_string(right);
        struct ProcessAnalysis pr = {message};
        process_result->push_back(pr);
        return left > right;
    }
    int greater_equal(int left, int right)
    {
        string message = "比較 " + to_string(left) + " >= " + to_string(right);
        struct ProcessAnalysis pr = {message};
        process_result->push_back(pr);
        return left >= right;
    }
    int calc(int node_index)
    {
        SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];

        if (current_node.parent_token == "<value_name>")
        {
            printf("cal get %s\n", current_node.token.c_str());
            int val;
            vpc->get(current_node.token, val);
            printf("cal get2 %d\n", val);

            return val;
        }

        if (current_node.parent_token == "<number>")
        {
            return stoi(current_node.token);
        }
        printf("calc %d -> %d %d\n", node_index, current_node.children[0], current_node.children[1]);

        SyntacticTreeNode child_left = (*syntactic_analysis_tree)[current_node.children[0]];
        SyntacticTreeNode child_right = (*syntactic_analysis_tree)[current_node.children[1]];

        int left;
        int right;

        left = calc(current_node.children[0]);
        right = calc(current_node.children[1]);

        int ans;

        string token = current_node.token;
        const char *token_c = token.c_str();

        if (token == "+")
        {
            ans = addition(left, right);
        }
        if (token == "-")
        {
            ans = subtraction(left, right);
        }
        if (token == "*")
        {
            ans = multiplication(left, right);
        }
        if (token == "/")
        {
            ans = division(left, right);
        }
        if (token == "<")
        {
            ans = less(left, right);
        }
        if (token == "<=")
        {
            ans = less_equal(left, right);
        }
        if (token == ">")
        {
            ans = greater(left, right);
        }
        if (token == ">=")
        {
            ans = greater_equal(left, right);
        }
        printf("calcSoftjTree %d : %d %s %d\n", ans, left, token.c_str(), right);

        return ans;
    }

    void recursion(int node_index)
    {

        SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];

        // char *text = current_node.token.c_str();
        string token = current_node.token;
        const char *token_c = token.c_str();

        printf("recursion %s\n", token_c);

        if (token == "<if>")
        {
            ifCalc(node_index);
            return;
        }
        if (token == "<while>")
        {
            whileCalc(node_index);
            return;
        }
        if (token == "=")
        {
            equal(node_index);
            return;
        }
        if (token == "+" || token == "-" || token == "*" || token == "/" || token == "<" || token == "<=" || token == ">" || token == ">=")
        {
            calc(node_index);
            return;
        }

        for (int i = 0; i < current_node.children.size(); i++)
        {
            recursion(current_node.children[i]);
        }
    }

public:
    SoftjTree(vSyntacticTree &syntactic_analysis_tree, vProcessAnalysis &process_result, VariablePossessionUnion &vpc)
    {

        this->syntactic_analysis_tree = &syntactic_analysis_tree;
        this->process_result = &process_result;
        this->vpc = &vpc;

        recursion(0);
    }
};

#endif