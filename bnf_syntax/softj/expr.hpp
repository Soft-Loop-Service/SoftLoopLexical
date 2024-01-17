
#ifndef __SOFTJ_INLINE_EXPR
#define __SOFTJ_INLINE_EXPR

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

        inline void Softj::assExpr(int left_index, int right_index)
        {

            SyntacticTreeNode current_left_node = (*syntactic_analysis_tree)[left_index];

            if (current_left_node.token == "<array_definition>")
            {
                SyntacticTreeNode child_left = (*syntactic_analysis_tree)[current_left_node.children[0]];
                SyntacticTreeNode child_right = (*syntactic_analysis_tree)[current_left_node.children[1]];

                string value_type = child_left.token;
                string value_name = child_right.token;

                if (right_index >= 0)
                {
                    SyntacticTreeNode current_right_node = (*syntactic_analysis_tree)[right_index];
                    int pointer = resolutionTreeCalcArray(right_index);
                    vpu->newPointerValue(value_name, pointer, left_index);
                }


                ProcessVisualization::ProcessAnalysis pr(ProcessVisualization::is_id_process_type_ouput, "配列配置", vpu->getDepth(), left_index);
                process_timeline->pushProcessAnalysis(pr);
            }

            if (current_left_node.token == "<value_definition>")
            {
                printf("assExpr %d %d %d %s\n", left_index, current_left_node.children[0], current_left_node.children[1], current_left_node.token.c_str());

                SyntacticTreeNode child_left = (*syntactic_analysis_tree)[current_left_node.children[0]];
                SyntacticTreeNode child_right = (*syntactic_analysis_tree)[current_left_node.children[1]];

                string value_type = child_left.token;
                string value_name = child_right.token;

                if (vpu->hasLayer(value_name))
                {
                    return;
                }

                string value_ans = "";

                if (value_type == "string" && right_index >= 0)
                {
                    string value_string = resolutionTreeCalcString(right_index);
                    vpu->newValue(value_name, value_string, left_index);
                    value_ans = value_string;
                }

                if (value_type == "int" && right_index >= 0)
                {
                    int value_int = resolutionTreeCalcInt(right_index);
                    vpu->newValue(value_name, value_int, left_index);
                    value_ans = to_string(value_int);
                    printf("value_ans %d\n", value_int);
                }


                ProcessVisualization::ProcessAnalysis pr(ProcessVisualization::is_id_process_type_ouput, "配列定義", vpu->getDepth(), left_index);
                process_timeline->pushProcessAnalysis(pr);

                return;
            }

            if (current_left_node.token == "<array_name>")
            {
                int pointer = resolutionTreeCalcArray(left_index);
                string value_type = vpu->getType(pointer);
                string value_ans = "";
                printf("array_name value_ans %d %s\n", pointer, value_type.c_str());

                if (value_type == "string")
                {
                    string value_string = resolutionTreeCalcString(right_index);
                    vpu->updateValue(pointer, value_string);
                    value_ans = value_string;
                }

                if (value_type == "int" || value_type == "pointer")
                {
                    int value_int = resolutionTreeCalcInt(right_index);
                    vpu->updateValue(pointer, value_int);
                    value_ans = to_string(value_int);
                }


                ProcessVisualization::ProcessAnalysis pr(ProcessVisualization::is_id_process_type_ouput, "配列代入", vpu->getDepth(), left_index);
                process_timeline->pushProcessAnalysis(pr);
            }

            if (current_left_node.parent_token == "<value_name>")
            {
                if (right_index < 0)
                {
                    return;
                }

                string value_name = current_left_node.token;

                if (!(vpu->hasLayer(value_name)))
                {
                    return;
                }

                string value_type = vpu->getType(value_name);
                string value_ans = "";

                if (value_type == "string")
                {
                    string value_string = resolutionTreeCalcString(right_index);
                    vpu->updateValue(value_name, value_string);
                    value_ans = value_string;
                }

                if (value_type == "int" || value_type == "pointer")
                {
                    int value_int = resolutionTreeCalcInt(right_index);
                    vpu->updateValue(value_name, value_int);
                    value_ans = to_string(value_int);
                }

                ProcessVisualization::ProcessAnalysis pr(ProcessVisualization::is_id_process_type_ouput, "変数代入", vpu->getDepth(), left_index);
                process_timeline->pushProcessAnalysis(pr);

                return;
            }
        }

    }
};
#endif