
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

            inline string Softj::resolutionCalcString(int node_index)
            {
                SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
                if (current_node.children.size() == 1)
                {
                    string r = resolutionCalcString(current_node.children[0]);
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
                    // input_layer_queue.enqueueLayerQueue(ProcessVisualization::is_id_timeline_magic_number_layer);
                    return current_node.token;
                }
                string left;
                string right;
                string ans;

                left = resolutionCalcString(current_node.children[0]);
                right = resolutionCalcString(current_node.children[1]);
                string token = current_node.token;

                if (token == "+")
                {
                    ans = text_join(left, right);
                }

                return ans;
            }
            inline void Softj::resolutionFunctionMessagePassing(ProcessVisualization::FunctionUnit function_unit, FunctionMessagePassing fmp)
            {
                ProcessVisualization::vArgument function_argument_vector = function_unit.getArgumentValue();

                input_layer_queue.enqueueLayerQueue(0);
                string message = "関数実行 " + function_unit.getFunctionName() + "";
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_function, message, input_layer_queue.useClearLayerQueue(), function_unit.getFunctionNode()};
                process_result->push_back(pr);

                vpu->deep(); // 引数解決層
                for (int i = 0; i < fmp.argument.size(); i++)
                {
                    ValueEnumeration passing_argument = fmp.argument[i];
                    ProcessVisualization::Argument function_argument = function_argument_vector[i];

                    printf("オーバーライドの解決 %s : %s %s\n", passing_argument.type.c_str(), function_argument.type.c_str(), function_argument.name.c_str());

                    string value_type = passing_argument.type;

                    if (passing_argument.type == "unsettled")
                    {
                        string new_type = vpu->getType(passing_argument.token);
                        printf("引数型の書き換え unsettled -> %s\n", new_type.c_str());
                        value_type = new_type;
                    }

                    string value_ans;
                    if (value_type == "string")
                    {
                        string value_string = resolutionCalcString(passing_argument.node_index);
                        vpu->newValue(function_argument.name, value_string, passing_argument.node_index);
                        value_ans = value_string;
                    }

                    if (value_type == "int")
                    {
                        int value_int = resolutionCalcInt(passing_argument.node_index);
                        vpu->newValue(function_argument.name, value_int, passing_argument.node_index);
                        value_ans = to_string(value_int);
                    }
                }

                vpu->deep(); // 関数実行層

                int recursion_node = function_unit.getFunctionNode();

                string return_type = function_unit.getReturnType();

                is_action_return = false;
                recursion(recursion_node);
                is_action_return = false;

                vpu->shallow();
                vpu->shallow();

                input_layer_queue.enqueueLayerQueue(0);
                message = "関数収束 " + function_unit.getFunctionName() + "";
                pr = {ProcessVisualization::is_id_process_type_function, message, input_layer_queue.useClearLayerQueue(), function_unit.getFunctionNode()};
                process_result->push_back(pr);

            }

            inline void Softj::resolutionCalcFunction(int node_index)
            {
                SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];

                printf("変数の解決(引数) %s %d\n", current_node.token.c_str(), node_index);
                if (!hasMapKey(function_message_passing_map, node_index))
                {
                    return;
                }

                printf("関数呼び出し要求 %d\n", node_index);
                FunctionMessagePassing fmp = function_message_passing_map[node_index];
                ProcessVisualization::FunctionUnit function_unit = searchFunctionMessagePassing(node_index);

                if (function_unit.getFunctionNode() == -1)
                {
                    printf("存在しない関数\n");
                    return;
                }

                if (function_unit.getFunctionNode() == -2)
                {
                    printf("空関数\n");
                    return;
                }
                string message = "関数呼び出し " + function_unit.getFunctionName() + "";
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_function, message, input_layer_queue.useClearLayerQueue(), node_index};
                process_result->push_back(pr);
                printf("関数取得 %s %d %s %d\n", function_unit.getFunctionName().c_str(), function_unit.getFunctionNode(), fmp.function_name.c_str(), fmp.argument.size());
                resolutionFunctionMessagePassing(function_unit, fmp);
            }

            inline int Softj::resolutionCalcInt(int node_index)
            {

                SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
                if (current_node.children.size() == 1)
                {
                    int r = resolutionCalcInt(current_node.children[0]);
                    return r;
                }

                if (current_node.parent_token == "<value_name>")
                {
                    int rv_val;
                    resolutionCalcValue(node_index, rv_val);

                    int layer = vpu->getLayer(current_node.token);
                    input_layer_queue.enqueueLayerQueue(layer, rv_val);
                    printf("ログ格納enqueueLayerQueue %d %d\n",layer,rv_val);

                    return rv_val;
                }

                if (current_node.parent_token == "<number>")
                {
                    input_layer_queue.enqueueLayerQueue(ProcessVisualization::is_id_timeline_magic_number_layer);
                    return stoi(current_node.token);
                }

                printf("calc %d -> %d %d\n", node_index, current_node.children[0], current_node.children[1]);

                SyntacticTreeNode child_left = (*syntactic_analysis_tree)[current_node.children[0]];
                SyntacticTreeNode child_right = (*syntactic_analysis_tree)[current_node.children[1]];

                int left;
                int right;

                left = resolutionCalcInt(current_node.children[0]);
                right = resolutionCalcInt(current_node.children[1]);
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