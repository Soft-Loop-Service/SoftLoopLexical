
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
                        struct ProcessVisualization::LayerQueuePoint lq = {layer};
                        struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_error, "定義済み変数名の再宣言", {lq}, left_index};
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
                        struct ProcessVisualization::LayerQueuePoint lq = {layer};
                        struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_error, "未定義変数への代入", {lq}, left_index};
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

    }
};
#endif