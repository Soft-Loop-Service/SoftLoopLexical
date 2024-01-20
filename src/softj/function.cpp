
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

        // nodeを返す
        ProcessVisualization::FunctionUnit Softj::searchFunctionMessagePassing(int node_index)
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

        // 戻り値変数レイヤーを返す
        void Softj::resolutionFunctionMessagePassing(ProcessVisualization::FunctionUnit function_unit, FunctionMessagePassing fmp)
        {
            ProcessVisualization::vArgument function_argument_vector = function_unit.getArgumentValue();

            int depth = vpu->getDepth();

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

            // vpu->deep(); // 関数実行層

            int recursion_node = function_unit.getFunctionNode();
            string return_type = function_unit.getReturnType();

            int function_node_index = function_unit.getFunctionNode();
            Syntactic::SyntacticTreeNode function_node = (*syntactic_analysis_tree)[function_node_index];
            int function_name_node_index = function_node.children[0];

            ProcessVisualization::ProcessAnalysis pr(ProcessVisualization::is_id_process_type_logic, "関数実行", depth, function_name_node_index);
            process_timeline->pushProcessAnalysis(pr);

            function_bation.push_back({return_type});

            recursion(recursion_node);

            ProcessVisualization::ProcessAnalysis pr2(ProcessVisualization::is_id_process_type_logic, "関数終了", depth, function_name_node_index);
            process_timeline->pushProcessAnalysis(pr2);

            // vpu->shallow();
            vpu->shallow();
            return;
        }
        // 戻り値変数レイヤーを返す
        void Softj::resolutionCalcFunction(int node_index)
        {
            Syntactic::SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];

            ProcessVisualization::ProcessAnalysis pr(ProcessVisualization::is_id_process_type_true, "関数呼び出し", vpu->getDepth(), node_index);
            process_timeline->pushProcessAnalysis(pr);
            printf("変数の解決(引数) %s %d\n", current_node.token.c_str(), node_index);

            if (!hasMapKey(function_message_passing_map, node_index))
            {
                ProcessVisualization::ProcessAnalysis pr(ProcessVisualization::is_id_process_type_error, "未定義関数への呼び出し", vpu->getDepth(), node_index);
                process_timeline->pushProcessAnalysis(pr);
                return;
            }

            printf("関数呼び出し要求 %d\n", node_index);
            FunctionMessagePassing fmp = function_message_passing_map[node_index];
            ProcessVisualization::FunctionUnit function_unit = searchFunctionMessagePassing(node_index);

            if (function_unit.getFunctionNode() == -1)
            {
                ProcessVisualization::ProcessAnalysis pr(ProcessVisualization::is_id_process_type_error, "オーバーロードの失敗", vpu->getDepth(), node_index);
                process_timeline->pushProcessAnalysis(pr);
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
            return;
        }
    }
};
