
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

        int Softj::whileCalc(int node_index)
        {
            Syntactic::SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
            int child0_node_index = current_node.children[0];
            Syntactic::SyntacticTreeNode child0 = (*syntactic_analysis_tree)[child0_node_index];
            // Syntactic::SyntacticTreeNode child1 = (*syntactic_analysis_tree)[current_node.children[1]];
            // Syntactic::SyntacticTreeNode child2 = (*syntactic_analysis_tree)[current_node.children[2]];

            int calc_ans = resolutionTreeCalcInt(current_node.children[1]);
            bool ifbool = getBool(calc_ans);

            while (ifbool)
            {
                ProcessVisualization::ProcessAnalysis pr(ProcessVisualization::is_id_process_type_true, "while 条件分岐", vpu->getDepth(), child0_node_index);
                process_timeline->pushProcessAnalysis(pr);

                vpu->deep();

                recursion(current_node.children[2]);
                calc_ans = resolutionTreeCalcInt(current_node.children[1]);
                ifbool = getBool(calc_ans);

                vpu->shallow();
            }

            ProcessVisualization::ProcessAnalysis pr(ProcessVisualization::is_id_process_type_false, "while 条件分岐", vpu->getDepth(), child0_node_index);
            process_timeline->pushProcessAnalysis(pr);
        }

        int Softj::ifCalc(int node_index)
        {
            printf("ifCalc\n");
            Syntactic::SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
            int child0_node_index = current_node.children[0];
            Syntactic::SyntacticTreeNode child0 = (*syntactic_analysis_tree)[child0_node_index];
            // Syntactic::SyntacticTreeNode child1 = (*syntactic_analysis_tree)[current_node.children[1]];
            // Syntactic::SyntacticTreeNode child2 = (*syntactic_analysis_tree)[current_node.children[2]];
            int calc_ans = resolutionTreeCalcInt(current_node.children[1]);

            bool ifbool = getBool(calc_ans);

            if (ifbool)
            {

                if (current_node.children.size() >= 3)
                {
                    string message = "if 条件分岐";

                    ProcessVisualization::ProcessAnalysis pr(ProcessVisualization::is_id_process_type_true, message, vpu->getDepth(), child0_node_index);
                    process_timeline->pushProcessAnalysis(pr);

                    vpu->deep();

                    recursion(current_node.children[2]);

                    vpu->shallow();
                }
            }
            else
            {
                string message = "if条件分岐";

                ProcessVisualization::ProcessAnalysis pr(ProcessVisualization::is_id_process_type_false, message, vpu->getDepth(), child0_node_index);
                process_timeline->pushProcessAnalysis(pr);
            }
        }

    }
};
