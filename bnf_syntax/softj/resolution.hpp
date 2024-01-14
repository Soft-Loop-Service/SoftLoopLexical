
#ifndef __SOFTJ_INLINE_RES
#define __SOFTJ_INLINE_RES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "./../../src/syntactic/syntactic_analysis_tree.hpp"
#include "./../../src/process/process_analysis_definition.hpp"
#include "./../../src/process/process_analysis_function.hpp"
#include "./../../src/process/process_analysis_value.hpp"
#include "./softj_tree.hpp"

namespace LanguageSpecifications
{
    namespace SoftjLanguage
    {

            template <typename T>
            inline bool Softj::resolutionCalcValue(int node_index, T &rv_value)
            {
                SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];

                printf("変数の解決 %s %d\n", current_node.token.c_str(), node_index);

                string value_name = current_node.token;
                printf("cal get %s\n", value_name.c_str());
                T val;
                vpu->getValue(value_name, val);

                bool hasLayer = vpu->hasLayer(value_name);

                if (!hasLayer)
                {
                    struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_error, "未定義変数のアクセス", {}, node_index};
                    process_result->push_back(pr);
                    return false;
                }

                rv_value = val;
                return true;
            }

            
            inline string Softj::resolutionCalcString(int node_index){
                SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
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

            inline string Softj::resolutionTreeCalcString(int node_index)
            {
                SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
                if (current_node.children.size() == 1)
                {
                    string r = resolutionTreeCalcString(current_node.children[0]);
                    return r;
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
                string left;
                string right;
                string ans;

                left = resolutionTreeCalcString(current_node.children[0]);
                right = resolutionTreeCalcString(current_node.children[1]);
                string token = current_node.token;

                if (token == "+")
                {
                    ans = text_join(left, right);
                }

                return ans;
            }
            inline int Softj::resolutionCalcInt(int node_index){
                SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
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
            inline int Softj::resolutionTreeCalcInt(int node_index)
            {

                SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
                if (current_node.children.size() == 1)
                {
                    int r = resolutionTreeCalcInt(current_node.children[0]);
                    return r;
                }

                if (current_node.parent_token == "<value_name>")
                {
                    int rv_val;
                    resolutionCalcValue(node_index, rv_val);

                    int layer = vpu->getLayer(current_node.token);
                    input_layer_queue.enqueueLayerQueue(layer, rv_val);

                    return rv_val;
                }

                if (current_node.parent_token == "<number>")
                {
                    // input_layer_queue.enqueueLayerQueue(ProcessVisualization::is_id_timeline_magic_number_layer);
                    return stoi(current_node.token);
                }

                printf("calc %d -> %d %d\n", node_index, current_node.children[0], current_node.children[1]);

                SyntacticTreeNode child_left = (*syntactic_analysis_tree)[current_node.children[0]];
                SyntacticTreeNode child_right = (*syntactic_analysis_tree)[current_node.children[1]];

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
                printf("calcSoftjTree %d : %d %s %d\n", ans, left, token.c_str(), right);

                return ans;
            }


    }
};
#endif