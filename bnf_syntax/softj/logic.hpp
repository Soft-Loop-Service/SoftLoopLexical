
#ifndef __SOFTJCALC
#define __SOFTJCALC

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
#include "./definition.hpp"

namespace LanguageSpecifications
{
    namespace SoftjLanguage
    {
        namespace SoftjLogic
        {
            vSyntacticTree *syntactic_analysis_tree;
            ProcessVisualization::vProcessAnalysis *process_result;

            int whileLogic(int node_index)
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

            int ifLogic(int node_index)
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
        }
    }
};

#endif