
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

    LayerQueue input_layer_queue;
    LayerQueue output_layer_queue;

    template <class T>
    void assExpr(T value, int node_index)
    {

        SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];

        if (current_node.token == "<value_definition>")
        {
            printf("assExpr %d %d %d %s\n", node_index, current_node.children[0], current_node.children[1], current_node.token.c_str());

            SyntacticTreeNode child_left = (*syntactic_analysis_tree)[current_node.children[0]];
            SyntacticTreeNode child_right = (*syntactic_analysis_tree)[current_node.children[1]];

            string value_name = child_right.token;
            vpc->newValue(value_name, value);

            // vpc[0]->add(value, address, size);
            printf("d\n");

            string message = "変数定義代入 " + child_right.token + " " + to_string(value);

            int layer = vpc->getLayer(value_name);
            output_layer_queue.enqueueLayerQueue(layer);
            struct ProcessAnalysis pr = {2,message, output_layer_queue.useClearLayerQueue()};
            process_result->push_back(pr);

            return;
        }

        if (current_node.parent_token == "<value_name>")
        {
            string value_name = current_node.token;
            vpc->updateValue(value_name, value);
            string message = "変数代入 " + current_node.token + " " + to_string(value);
            int layer = vpc->getLayer(value_name);
            output_layer_queue.enqueueLayerQueue(layer);
            struct ProcessAnalysis pr = {2,message, output_layer_queue.useClearLayerQueue()};
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

        int calc_ans = resolution_calc_int(current_node.children[1]);
        bool ifbool = getBool(calc_ans);

        

        while (ifbool)
        {
            output_layer_queue.enqueueLayerQueue(0);
            string message = "ループ条件式 true";
            struct ProcessAnalysis pr = {4,message, output_layer_queue.useClearLayerQueue()};
            process_result->push_back(pr);
            recursion(current_node.children[2]);
            calc_ans = resolution_calc_int(current_node.children[1]);
            ifbool = getBool(calc_ans);
        }

        string message = "ループ条件式 false";
        output_layer_queue.enqueueLayerQueue(0);
        struct ProcessAnalysis pr = {4,message, output_layer_queue.useClearLayerQueue()};
        process_result->push_back(pr);
    }

    int ifCalc(int node_index)
    {
        printf("ifCalc\n");
        SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
        SyntacticTreeNode child0 = (*syntactic_analysis_tree)[current_node.children[0]];
        // SyntacticTreeNode child1 = (*syntactic_analysis_tree)[current_node.children[1]];
        // SyntacticTreeNode child2 = (*syntactic_analysis_tree)[current_node.children[2]];
        int calc_ans = resolution_calc_int(current_node.children[1]);

        bool ifbool = getBool(calc_ans);
        output_layer_queue.enqueueLayerQueue(0);

        if (ifbool)
        {
            string message = "条件式 true";
            struct ProcessAnalysis pr = {4,message, output_layer_queue.useClearLayerQueue()};
            process_result->push_back(pr);

            if (current_node.children.size() >= 3)
            {
                recursion(current_node.children[2]);
            }
        }
        else
        {
            string message = "条件式 false";
            struct ProcessAnalysis pr = {4,message, output_layer_queue.useClearLayerQueue()};
            process_result->push_back(pr);
        }
    }

    int equal(int node_index)
    {

        SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
        SyntacticTreeNode child_left = (*syntactic_analysis_tree)[current_node.children[0]];
        SyntacticTreeNode child_right = (*syntactic_analysis_tree)[current_node.children[1]];

        int right;
        right = resolution_calc_int(current_node.children[1]);
        assExpr(right, current_node.children[0]);
    }
    string text_join(string left, string right)
    {
        string message = "文字列連結 " + left + " + " + right;
        struct ProcessAnalysis pr = {1,message,input_layer_queue.useClearLayerQueue()};
        process_result->push_back(pr);

        return left + right;
    }

    int addition(int left, int right)
    {
        string message = "加算 " + to_string(left) + " + " + to_string(right);
        struct ProcessAnalysis pr = {1,message,input_layer_queue.useClearLayerQueue()};
        process_result->push_back(pr);

        return left + right;
    }
    int subtraction(int left, int right)
    {
        string message = "減算 " + to_string(left) + " - " + to_string(right);
        struct ProcessAnalysis pr = {1,message,input_layer_queue.useClearLayerQueue()};
        process_result->push_back(pr);
        return left - right;
    }
    int multiplication(int left, int right)
    {
        string message = "乗算 " + to_string(left) + " * " + to_string(right);
        struct ProcessAnalysis pr = {1,message,input_layer_queue.useClearLayerQueue()};
        process_result->push_back(pr);
        return left * right;
    }
    int division(int left, int right)
    {
        string message = "割算 " + to_string(left) + " / " + to_string(right);
        struct ProcessAnalysis pr = {1,message,input_layer_queue.useClearLayerQueue()};
        process_result->push_back(pr);
        return left / right;
    }
    int less(int left, int right)
    {
        string message = "比較 " + to_string(left) + " < " + to_string(right);
        struct ProcessAnalysis pr = {1,message,input_layer_queue.useClearLayerQueue()};
        process_result->push_back(pr);
        return left < right;
    }
    int less_equal(int left, int right)
    {
        string message = "比較 " + to_string(left) + " <= " + to_string(right);
        struct ProcessAnalysis pr = {1,message,input_layer_queue.useClearLayerQueue()};
        process_result->push_back(pr);
        return left <= right;
    }
    int greater(int left, int right)
    {
        string message = "比較 " + to_string(left) + " > " + to_string(right);
        struct ProcessAnalysis pr = {1,message,input_layer_queue.useClearLayerQueue()};
        process_result->push_back(pr);
        return left > right;
    }
    int greater_equal(int left, int right)
    {
        string message = "比較 " + to_string(left) + " >= " + to_string(right);
        struct ProcessAnalysis pr = {1,message,input_layer_queue.useClearLayerQueue()};
        process_result->push_back(pr);
        return left >= right;
    }
    int equality(int left, int right)
    {
        string message = "比較 " + to_string(left) + " == " + to_string(right);
        struct ProcessAnalysis pr = {1,message,input_layer_queue.useClearLayerQueue()};
        process_result->push_back(pr);
        return left == right;
    }
    int equality(string left, string right)
    {
        string message = "比較 " + left + " == " + right;
        struct ProcessAnalysis pr = {1,message,input_layer_queue.useClearLayerQueue()};
        process_result->push_back(pr);
        return left == right;
    }

    
    string resolution_calc_string(int node_index){
        SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
        if (current_node.children.size() == 1)
        {
            string r = resolution_calc_string(current_node.children[0]);
            return r;
        }
        if (current_node.parent_token == "<text>")
        {
            input_layer_queue.enqueueLayerQueue(timeline_magic_number_layer);
            return current_node.token;
        }


        SyntacticTreeNode child_left = (*syntactic_analysis_tree)[current_node.children[0]];
        SyntacticTreeNode child_right = (*syntactic_analysis_tree)[current_node.children[1]];

        string left;
        string right;
        string ans;

        left = resolution_calc_string(current_node.children[0]);
        right = resolution_calc_string(current_node.children[1]);
        string token = current_node.token;

        if (token == "+")
        {
            ans = text_join(left, right);
        }

        return ans;
    }
    int resolution_calc_int(int node_index)
    {

        SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
        if (current_node.children.size() == 1)
        {
            int r = resolution_calc_int(current_node.children[0]);
            return r;
        }
        if (current_node.parent_token == "<value_name>")
        {
            string value_name = current_node.token;
            printf("cal get %s\n", value_name.c_str());
            int val;
            vpc->getValue(value_name, val);
            printf("cal get2 %d\n", val);

            int layer = vpc->getLayer(value_name.c_str());
            input_layer_queue.enqueueLayerQueue(layer);

            return val;
        }

        if (current_node.parent_token == "<number>")
        {
            input_layer_queue.enqueueLayerQueue(timeline_magic_number_layer);
            return stoi(current_node.token);
        }

        
        printf("calc %d -> %d %d\n", node_index, current_node.children[0], current_node.children[1]);

        SyntacticTreeNode child_left = (*syntactic_analysis_tree)[current_node.children[0]];
        SyntacticTreeNode child_right = (*syntactic_analysis_tree)[current_node.children[1]];

        int left;
        int right;

        left = resolution_calc_int(current_node.children[0]);
        right = resolution_calc_int(current_node.children[1]);
        string token = current_node.token;

        int ans;


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
        if (token == "==")
        {
            ans = equality(left, right);
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
        if (token == "+" || token == "-" || token == "*" || token == "/" || token == "<" || token == "<=" || token == ">" || token == ">=" || token == "==")
        {
            resolution_calc_int(node_index);
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