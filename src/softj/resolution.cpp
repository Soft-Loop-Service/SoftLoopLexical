
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "./softj.hpp"

namespace LanguageSpecifications
{
    namespace SoftjLanguage
    {

        string Softj::resolutionCalcString(int node_index)
        {
            Syntactic::SyntacticTreeNode current_node = getTreeNode(node_index);

            if (current_node.token == "<array_name>")
            {
                int pointer = resolutionTreeCalcArray(node_index);
                string rv_val;
                vpu->getValue(pointer, rv_val);
                return rv_val;
            }

            if (current_node.parent_token == "<value_name>")
            {
                string rv_val;
                resolutionCalcValue(node_index, rv_val);
                return rv_val;
            }

            if (current_node.token_label == is_id_TerminalSymbol)
            {
                return current_node.token;
            }
        }

        string Softj::resolutionTreeCalcString(int node_index)
        {
            Syntactic::SyntacticTreeNode current_node = getTreeNode(node_index);
            if (current_node.children.size() == 1)
            {
                string r = resolutionTreeCalcString(current_node.children[0]);
                return r;
            }

            if (hasMapKey(function_message_passing_map, node_index))
            {
                resolutionCalcFunction(node_index);
                string rv_val;
                if (return_baton.size() > 0)
                {
                    ReturnBaton return_baton_unit = return_baton[return_baton.size() - 1];
                    return_baton.pop_back();
                    rv_val = return_baton_unit.getValueString();
                }
                printf("関数解析 戻り値解析(string) %s\n", rv_val.c_str());

                return rv_val;
            }

            if (current_node.token == "<function_message_passing>")
            {
                return resolutionTreeCalcString(current_node.children[0]);
            }

            if (current_node.parent_token == "<value_name>" || current_node.token_label == is_id_TerminalSymbol || current_node.token == "<array_name>")
            {
                return resolutionCalcString(node_index);
            }

            string left;
            string right;
            string ans;

            left = resolutionTreeCalcString(current_node.children[0]);
            right = resolutionTreeCalcString(current_node.children[1]);
            string token = current_node.token;

            if (token == "+")
            {
                ans = text_join(left, right, node_index);
            }

            return ans;
        }
        int Softj::resolutionCalcInt(int node_index)
        {
            Syntactic::SyntacticTreeNode current_node = getTreeNode(node_index);

            if (current_node.token == "<array_name>")
            {
                int pointer = resolutionTreeCalcArray(node_index);
                int rv_val;
                vpu->getValue(pointer, rv_val);
                return rv_val;
            }

            if (current_node.parent_token == "<value_name>")
            {
                int rv_val;
                resolutionCalcValue(node_index, rv_val);
                return rv_val;
            }

            if (current_node.parent_token == "<number>")
            {
                return stoi(current_node.token);
            }
        }
        int Softj::resolutionTreeCalcInt(int node_index)
        {

            Syntactic::SyntacticTreeNode current_node = getTreeNode(node_index);
            if (current_node.children.size() == 1)
            {
                int r = resolutionTreeCalcInt(current_node.children[0]);
                return r;
            }

            if (hasMapKey(function_message_passing_map, node_index))
            {
                resolutionCalcFunction(node_index);

                printf("関数解析 戻り値解析開始(int) %d\n", return_baton.size());

                int rv_val;
                if (return_baton.size() > 0)
                {
                    ReturnBaton return_baton_unit = return_baton[return_baton.size() - 1];
                    return_baton.pop_back();
                    rv_val = return_baton_unit.getValueInt();
                }

                printf("関数解析 戻り値解析(int) %d\n", rv_val);

                return rv_val;
            }

            if (current_node.token == "<function_message_passing>")
            {
                return resolutionTreeCalcInt(current_node.children[0]);
            }

            if (current_node.parent_token == "<value_name>" || current_node.parent_token == "<number>" || current_node.token == "<array_name>")
            {
                printf("変数解析要求 %s %d\n", current_node.parent_token.c_str(), node_index);
                return resolutionCalcInt(node_index);
            }

            printf("calc %d -> %d %d\n", node_index, current_node.children[0], current_node.children[1]);

            Syntactic::SyntacticTreeNode child_left = getTreeNode(current_node.children[0]);
            Syntactic::SyntacticTreeNode child_right = getTreeNode(current_node.children[1]);

            int left;
            int right;

            left = resolutionTreeCalcInt(current_node.children[0]);
            right = resolutionTreeCalcInt(current_node.children[1]);
            string token = current_node.token;

            int ans;

            int bulletin_node_index = node_index;

            if (token == "+")
            {
                ans = addition(left, right, bulletin_node_index);
            }
            if (token == "-")
            {
                ans = subtraction(left, right, bulletin_node_index);
            }
            if (token == "*")
            {
                ans = multiplication(left, right, bulletin_node_index);
            }
            if (token == "/")
            {
                ans = division(left, right, bulletin_node_index);
            }
            if (token == "<")
            {
                ans = less(left, right, bulletin_node_index);
            }
            if (token == "<=")
            {
                ans = less_equal(left, right, bulletin_node_index);
            }
            if (token == ">")
            {
                ans = greater(left, right, bulletin_node_index);
            }
            if (token == ">=")
            {
                ans = greater_equal(left, right, bulletin_node_index);
            }
            if (token == "==")
            {
                ans = equality(left, right, bulletin_node_index);
            }
            if (token == "!=")
            {
                ans = inequality(left, right, bulletin_node_index);
            }
            if (token == "%")
            {
                ans = remainder(left, right, bulletin_node_index);
            }
            else
            {
            }
            printf("calcSoftjTree %d : %d %s %d\n", ans, left, token.c_str(), right);

            return ans;
        }

    }
};
