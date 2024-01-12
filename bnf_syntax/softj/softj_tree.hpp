
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
#include "./../../src/process/process_analysis_function.hpp"
#include "./../../src/process/process_analysis_value.hpp"
namespace LanguageSpecifications
{
    namespace Softj
    {
        struct ValueEnumeration
        {
            string type;

            int node_index;
            string token;
        };
        typedef vector<ValueEnumeration> vValueEnumeration;

        struct FunctionMessagePassing
        {
            string function_name;
            int node_index;
            vValueEnumeration argument;
        };
        typedef vector<FunctionMessagePassing> vFunctionMessagePassing;
        typedef map<int, FunctionMessagePassing> m_i_FunctionMessagePassing;

        class SoftjTree
        {

        private:
            vSyntacticTree *syntactic_analysis_tree;
            ProcessVisualization::vProcessAnalysis *process_result;
            ProcessVisualization::VariablePossessionUnion *vpu;
            ProcessVisualization::FunctionPossessionUnion *fpu;

            ProcessVisualization::LayerQueue input_layer_queue;
            ProcessVisualization::LayerQueue output_layer_queue;
            m_i_FunctionMessagePassing function_message_passing_map;

            void assExpr(int left_index, int right_index)
            {

                SyntacticTreeNode current_node = (*syntactic_analysis_tree)[left_index];

                if (current_node.token == "<value_definition>")
                {
                    printf("assExpr %d %d %d %s\n", left_index, current_node.children[0], current_node.children[1], current_node.token.c_str());

                    SyntacticTreeNode child_left = (*syntactic_analysis_tree)[current_node.children[0]];
                    SyntacticTreeNode child_right = (*syntactic_analysis_tree)[current_node.children[1]];

                    string value_type = child_left.token;
                    string value_name = child_right.token;

                    if (vpu->hasLayer(value_name))
                    {
                        int layer = vpu->getLayer(value_name);
                        struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_error, "定義済み変数名の再宣言", {layer}, left_index};
                        process_result->push_back(pr);
                        return;
                    }

                    string value_ans = "";

                    if (value_type == "string")
                    {
                        string value_string = resolutionCalcString(right_index);
                        vpu->newValue(value_name, value_string, left_index);
                        value_ans = value_string;
                    }

                    if (value_type == "int")
                    {
                        int value_int = resolutionCalcInt(right_index);
                        vpu->newValue(value_name, value_int, left_index);
                        value_ans = to_string(value_int);
                    }

                    printf("d\n");

                    string message = "変数定義代入 " + child_right.token + " " + value_ans;

                    int layer = vpu->getLayer(value_name);
                    output_layer_queue.enqueueLayerQueue(layer);
                    struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_ouput, message, output_layer_queue.useClearLayerQueue(), left_index};
                    process_result->push_back(pr);

                    return;
                }

                if (current_node.parent_token == "<value_name>")
                {

                    string value_name = current_node.token;

                    if (!(vpu->hasLayer(value_name)))
                    {
                        int layer = vpu->getLayer(value_name);
                        struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_error, "未定義変数への代入", {layer}, left_index};
                        process_result->push_back(pr);
                        return;
                    }

                    string value_type = vpu->getType(value_name);
                    string value_ans = "";

                    if (value_type == "string")
                    {
                        string value_string = resolutionCalcString(right_index);
                        vpu->updateValue(value_name, value_string);
                        value_ans = value_string;
                    }

                    if (value_type == "int")
                    {
                        int value_int = resolutionCalcInt(right_index);
                        vpu->updateValue(value_name, value_int);
                        value_ans = to_string(value_int);
                    }

                    string message = "変数代入 " + current_node.token + " " + value_ans;
                    int layer = vpu->getLayer(value_name);
                    output_layer_queue.enqueueLayerQueue(layer);
                    struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_ouput, message, output_layer_queue.useClearLayerQueue(), left_index};
                    process_result->push_back(pr);
                    return;
                }
            }

            bool getBool(int val)
            {
                return val > 0;
            }

            int whileCalc(int node_index)
            {
                SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
                SyntacticTreeNode child0 = (*syntactic_analysis_tree)[current_node.children[0]];
                // SyntacticTreeNode child1 = (*syntactic_analysis_tree)[current_node.children[1]];
                // SyntacticTreeNode child2 = (*syntactic_analysis_tree)[current_node.children[2]];

                int calc_ans = resolutionCalcInt(current_node.children[1]);
                bool ifbool = getBool(calc_ans);

                while (ifbool)
                {
                    output_layer_queue.enqueueLayerQueue(0);
                    string message = "ループ条件式 true";
                    struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_logic, message, output_layer_queue.useClearLayerQueue(), node_index};
                    process_result->push_back(pr);

                    vpu->deep();

                    recursion(current_node.children[2]);
                    calc_ans = resolutionCalcInt(current_node.children[1]);
                    ifbool = getBool(calc_ans);

                    vpu->shallow();
                }

                string message = "ループ条件式 false";
                output_layer_queue.enqueueLayerQueue(0);
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_logic, message, output_layer_queue.useClearLayerQueue(), node_index};
                process_result->push_back(pr);
            }

            int ifCalc(int node_index)
            {
                printf("ifCalc\n");
                SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
                SyntacticTreeNode child0 = (*syntactic_analysis_tree)[current_node.children[0]];
                // SyntacticTreeNode child1 = (*syntactic_analysis_tree)[current_node.children[1]];
                // SyntacticTreeNode child2 = (*syntactic_analysis_tree)[current_node.children[2]];
                int calc_ans = resolutionCalcInt(current_node.children[1]);

                bool ifbool = getBool(calc_ans);
                output_layer_queue.enqueueLayerQueue(0);

                if (ifbool)
                {
                    string message = "条件式 true";
                    struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_logic, message, output_layer_queue.useClearLayerQueue(), node_index};
                    process_result->push_back(pr);

                    if (current_node.children.size() >= 3)
                    {
                        vpu->deep();

                        recursion(current_node.children[2]);

                        vpu->shallow();
                    }
                }
                else
                {
                    string message = "条件式 false";
                    struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_logic, message, output_layer_queue.useClearLayerQueue(), node_index};
                    process_result->push_back(pr);
                }
            }

            int equal(int node_index)
            {

                SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
                SyntacticTreeNode child_left = (*syntactic_analysis_tree)[current_node.children[0]];
                SyntacticTreeNode child_right = (*syntactic_analysis_tree)[current_node.children[1]];
                assExpr(current_node.children[0], current_node.children[1]);
            }
            string text_join(string left, string right)
            {
                string message = "文字列連結 " + left + " + " + right;
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, input_layer_queue.useClearLayerQueue()};
                process_result->push_back(pr);

                return left + right;
            }

            int addition(int left, int right, int node_index)
            {
                string message = "加算 " + to_string(left) + " + " + to_string(right);
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, input_layer_queue.useClearLayerQueue(), node_index};
                process_result->push_back(pr);

                return left + right;
            }
            int subtraction(int left, int right, int node_index)
            {
                string message = "減算 " + to_string(left) + " - " + to_string(right);
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, input_layer_queue.useClearLayerQueue(), node_index};
                process_result->push_back(pr);
                return left - right;
            }
            int multiplication(int left, int right, int node_index)
            {
                string message = "乗算 " + to_string(left) + " * " + to_string(right);
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, input_layer_queue.useClearLayerQueue(), node_index};
                process_result->push_back(pr);
                return left * right;
            }
            int division(int left, int right, int node_index)
            {
                string message = "割算 " + to_string(left) + " / " + to_string(right);
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, input_layer_queue.useClearLayerQueue(), node_index};
                process_result->push_back(pr);
                return left / right;
            }
            int less(int left, int right, int node_index)
            {
                string message = "比較 " + to_string(left) + " < " + to_string(right);
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, input_layer_queue.useClearLayerQueue(), node_index};
                process_result->push_back(pr);
                return left < right;
            }
            int less_equal(int left, int right, int node_index)

            {
                string message = "比較 " + to_string(left) + " <= " + to_string(right);
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, input_layer_queue.useClearLayerQueue(), node_index};
                process_result->push_back(pr);
                return left <= right;
            }
            int greater(int left, int right, int node_index)
            {
                string message = "比較 " + to_string(left) + " > " + to_string(right);
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, input_layer_queue.useClearLayerQueue(), node_index};
                process_result->push_back(pr);
                return left > right;
            }
            int greater_equal(int left, int right, int node_index)
            {
                string message = "比較 " + to_string(left) + " >= " + to_string(right);
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, input_layer_queue.useClearLayerQueue(), node_index};
                process_result->push_back(pr);
                return left >= right;
            }
            int equality(int left, int right, int node_index)
            {
                string message = "比較 " + to_string(left) + " == " + to_string(right);
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, input_layer_queue.useClearLayerQueue(), node_index};
                process_result->push_back(pr);
                return left == right;
            }
            int equality(string left, string right, int node_index)
            {
                string message = "比較 " + left + " == " + right;
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, input_layer_queue.useClearLayerQueue(), node_index};
                process_result->push_back(pr);
                return left == right;
            }

            string resolutionCalcString(int node_index)
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
                    input_layer_queue.enqueueLayerQueue(ProcessVisualization::is_id_timeline_magic_number_layer);
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

            // nodeを返す
            ProcessVisualization::FunctionUnit functionMessagePassing(int node_index)
            {

                FunctionMessagePassing fmp = function_message_passing_map[node_index];
                vValueEnumeration vve = fmp.argument;

                vstring types = {};

                for (int i = 0; i < vve.size(); i++)
                {
                    ValueEnumeration ve = vve[i];

                    if (ve.type == "unsettled")
                    {
                        string new_type = vpu->getType(ve.token);
                        printf("引数型の書き換え unsettled -> %s\n", new_type.c_str());
                        types.push_back(new_type);
                        continue;
                    }

                    types.push_back(ve.type);
                }
                ProcessVisualization::FunctionUnit function_unit = fpu->getFunction(fmp.function_name, types);

                printf("対象関数の特定 %s %d\n", function_unit.getFunctionName().c_str(), function_unit.getFunctionNode());

                return function_unit;
            }

            void resolutionFunctionMessagePassing(ProcessVisualization::FunctionUnit function_unit, FunctionMessagePassing fmp)
            {
                ProcessVisualization::vArgument function_argument_vector = function_unit.getArgumentValue();
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

                recursion(recursion_node);

                vpu->shallow();
                vpu->shallow();
            }

            void resolutionCalcFunction(int node_index)
            {
                SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];

                printf("変数の解決(引数) %s %d\n", current_node.token.c_str(), node_index);
                if (!hasMapKey(function_message_passing_map, node_index))
                {
                    return;
                }

                printf("関数呼び出し要求 %d\n", node_index);
                FunctionMessagePassing fmp = function_message_passing_map[node_index];
                ProcessVisualization::FunctionUnit function_unit = functionMessagePassing(node_index);

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

                printf("関数取得 %s %d %s %d\n", function_unit.getFunctionName().c_str(), function_unit.getFunctionNode(), fmp.function_name.c_str(), fmp.argument.size());
                resolutionFunctionMessagePassing(function_unit, fmp);
            }

            template <typename T>
            bool resolutionCalcValue(int node_index, T &rv_value)
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

                int layer = vpu->getLayer(value_name);
                input_layer_queue.enqueueLayerQueue(layer);

                rv_value = val;
                return true;
            }

            int resolutionCalcInt(int node_index)
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
            void recursionString(int node_index)
            {

                SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
                string token = current_node.token;
                if (token == "+" || token == "==")
                {
                    resolutionCalcString(node_index);
                    return;
                }
                if (token == "<return>")
                {
                    return;
                }
                for (int i = 0; i < current_node.children.size(); i++)
                {
                    syntaxBranch(current_node.children[i]);
                }
                return;
            }
            void recursion(int node_index)
            {
                SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
                string token = current_node.token;

                if (token == "return")
                {
                    return;
                }
                if (token == "+" || token == "-" || token == "*" || token == "/" || token == "<" || token == "<=" || token == ">" || token == ">=" || token == "==")
                {
                    resolutionCalcInt(node_index);
                    return;
                }

                syntaxBranch(node_index);

                for (int i = 0; i < current_node.children.size(); i++)
                {
                    recursion(current_node.children[i]);
                }
                return;
            }

            bool syntaxBranch(int node_index)
            {
                SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
                string token = current_node.token;
                printf("recursion %s\n", token.c_str());

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

                if (current_node.parent_token == "<value_name>")
                {
                    resolutionCalcFunction(node_index);
                    return;
                }

                if (token == "<function>")
                {
                    return;
                }

                if (token == "=")
                {
                    equal(node_index);
                    return;
                }

                return;
            }

            ProcessVisualization::Argument extractValueDefinition(int node_index)
            {
                SyntacticTreeNode node = (*syntactic_analysis_tree)[node_index];
                SyntacticTreeNode node_left = (*syntactic_analysis_tree)[node.children[0]];
                SyntacticTreeNode node_right = (*syntactic_analysis_tree)[node.children[1]];
                printf("extractValueDefinition %s %s %d\n", node_left.token.c_str(), node_right.token.c_str(), node_index);

                struct ProcessVisualization::Argument rvarg = {node_left.token, node_right.token};

                return rvarg;
            }

            void extractArgument(int node_index, ProcessVisualization::vArgument &extract_args)
            {
                SyntacticTreeNode node = (*syntactic_analysis_tree)[node_index];

                if (node.token == "<value_definition>")
                {
                    ProcessVisualization::Argument rvarg = extractValueDefinition(node_index);
                    extract_args.push_back(rvarg);
                    return;
                }

                for (int i = 0; i < node.children.size(); i++)
                {
                    int child_node_index = node.children[i];
                    SyntacticTreeNode child_node = (*syntactic_analysis_tree)[child_node_index];

                    if (child_node.token_label == is_id_NonterminalSymbol)
                    {
                        extractArgument(child_node_index, extract_args);
                    }
                }
            }

            void preparationValueEnumeration(int node_index, vValueEnumeration &args_type)
            {
                SyntacticTreeNode node = (*syntactic_analysis_tree)[node_index];

                if (node.parent_token == "<value_name>")
                {
                    struct ValueEnumeration ve = {"unsettled", node_index, node.token};
                    args_type.push_back(ve);
                    printf("preparationValueEnumeration %s %d\n", ve.type.c_str(), node_index);
                    return;
                }

                if (node.parent_token == "<number>")
                {
                    struct ValueEnumeration ve = {"int", node_index, node.token};

                    args_type.push_back(ve);
                    printf("preparationValueEnumeration %s %d\n", ve.type.c_str(), node_index);
                    return;
                }

                if (node.parent_token == "<text>")
                {
                    struct ValueEnumeration ve = {"string", node_index, node.token};
                    args_type.push_back(ve);
                    printf("preparationValueEnumeration %s %d\n", ve.type.c_str(), node_index);
                    return;
                }

                for (int i = 0; i < node.children.size(); i++)
                {
                    int child_node_index = node.children[i];
                    SyntacticTreeNode child_node = (*syntactic_analysis_tree)[child_node_index];

                    preparationValueEnumeration(child_node_index, args_type);
                }
            }

            void preparationFunctionMessagePassing(int node_index)
            {
                SyntacticTreeNode node = (*syntactic_analysis_tree)[node_index];
                int child_node_left_index = node.children[0];

                SyntacticTreeNode node_left = (*syntactic_analysis_tree)[child_node_left_index];

                vValueEnumeration args_type = {};

                int child_node_right_index = -1;
                if (node.children.size() == 2)
                {
                    child_node_right_index = node.children[1];
                    preparationValueEnumeration(child_node_right_index, args_type);
                }

                struct FunctionMessagePassing fmp = {node_left.token, child_node_left_index, args_type};

                printf("preparationFunctionMessagePassing %d %d %s %d\n", child_node_left_index, child_node_right_index, node_left.token.c_str(), args_type.size());

                function_message_passing_map[child_node_left_index] = fmp;
            }

            // 関数定義について、予め軽く解析しておく
            void preparationFunction(int node_index)
            {
                SyntacticTreeNode node = (*syntactic_analysis_tree)[node_index];
                ProcessVisualization::vArgument extract_args = {};

                // 変数の名前と戻り地の定義
                ProcessVisualization::Argument function_definition = extractValueDefinition(node.children[0]);

                if (node.children.size() == 1)
                {
                    return;
                }

                if (node.children.size() == 2)
                {
                    if ((*syntactic_analysis_tree)[node.children[1]].token == "<value_definition>")
                    {
                        extractArgument(node.children[1], extract_args);
                        ProcessVisualization::FunctionUnit function_unit(function_definition.name, function_definition.type, extract_args, -2);
                        fpu->addFunction(function_unit);
                    }
                    else
                    {
                        ProcessVisualization::FunctionUnit function_unit(function_definition.name, function_definition.type, extract_args, node.children[1]);
                        fpu->addFunction(function_unit);
                    }
                    return;
                }

                int arg_node = node.children[1];
                int block_node = node.children[2];

                // 引数一覧
                extractArgument(arg_node, extract_args);
                printf("preparationFunction %s %s %d\n", function_definition.name.c_str(), function_definition.type.c_str(), node_index);
                ProcessVisualization::FunctionUnit function_unit(function_definition.name, function_definition.type, extract_args, block_node);
                fpu->addFunction(function_unit);
            }

            // 予め軽く木構造を走査しておく
            void preparationTree()
            {
                for (int i = 0; i < syntactic_analysis_tree->size(); i++)
                {
                    SyntacticTreeNode node = (*syntactic_analysis_tree)[i];

                    if (node.token == "<function>")
                    {
                        preparationFunction(i);
                    }
                    if (node.token == "<function_message_passing>")
                    {
                        preparationFunctionMessagePassing(i);
                    }
                }
            }

        public:
            SoftjTree(vSyntacticTree &syntactic_analysis_tree, ProcessVisualization::vProcessAnalysis &process_result, ProcessVisualization::VariablePossessionUnion &vpu, ProcessVisualization::FunctionPossessionUnion &fpu)
            {
                this->function_message_passing_map = {};
                this->syntactic_analysis_tree = &syntactic_analysis_tree;
                this->process_result = &process_result;
                this->vpu = &vpu;
                this->fpu = &fpu;
                preparationTree();
                recursion(0);
            }
        };
    };
};

#endif