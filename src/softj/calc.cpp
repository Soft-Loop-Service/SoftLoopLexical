
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

             int Softj::equal(int node_index)
            {
                Syntactic::SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];

                int left = current_node.children[0];
                int right = current_node.children.size() >= 2 ? current_node.children[1] : -1;
                assExpr(left, right);
            }
             string Softj::text_join(string left, string right, int node_index)
            {
                string message = "文字列連結";
                 ProcessVisualization::ProcessAnalysis pr(ProcessVisualization::is_id_process_type_input, message, vpu->getDepth(),node_index);
                process_timeline->pushProcessAnalysis(pr);

                return left + right;
            }

             int Softj::addition(int left, int right, int node_index)
            {
                string message = "加算";
                 ProcessVisualization::ProcessAnalysis pr(ProcessVisualization::is_id_process_type_input, message, vpu->getDepth(), node_index);
                process_timeline->pushProcessAnalysis(pr);

                return left + right;
            }
             int Softj::subtraction(int left, int right, int node_index)
            {
                string message = "減算";
                 ProcessVisualization::ProcessAnalysis pr(ProcessVisualization::is_id_process_type_input, message, vpu->getDepth(), node_index);
                process_timeline->pushProcessAnalysis(pr);
                return left - right;
            }
             int Softj::multiplication(int left, int right, int node_index)
            {
                string message = "乗算";
                 ProcessVisualization::ProcessAnalysis pr(ProcessVisualization::is_id_process_type_input, message, vpu->getDepth(), node_index);
                process_timeline->pushProcessAnalysis(pr);
                return left * right;
            }
             int Softj::division(int left, int right, int node_index)
            {
                string message = "割算";
                 ProcessVisualization::ProcessAnalysis pr(ProcessVisualization::is_id_process_type_input, message, vpu->getDepth(), node_index);
                process_timeline->pushProcessAnalysis(pr);
                return left / right;
            }
             int Softj::less(int left, int right, int node_index)
            {
                string message = "比較";
                 ProcessVisualization::ProcessAnalysis pr(ProcessVisualization::is_id_process_type_input, message, vpu->getDepth(), node_index);
                process_timeline->pushProcessAnalysis(pr);
                return left < right;
            }
             int Softj::less_equal(int left, int right, int node_index)

            {
                string message = "比較";
                 ProcessVisualization::ProcessAnalysis pr(ProcessVisualization::is_id_process_type_input, message, vpu->getDepth(), node_index);
                process_timeline->pushProcessAnalysis(pr);
                return left <= right;
            }
             int Softj::greater(int left, int right, int node_index)
            {
                string message = "比較";
                 ProcessVisualization::ProcessAnalysis pr(ProcessVisualization::is_id_process_type_input, message, vpu->getDepth(), node_index);
                process_timeline->pushProcessAnalysis(pr);
                return left > right;
            }
             int Softj::greater_equal(int left, int right, int node_index)
            {
                string message = "比較";
                 ProcessVisualization::ProcessAnalysis pr(ProcessVisualization::is_id_process_type_input, message, vpu->getDepth(), node_index);
                process_timeline->pushProcessAnalysis(pr);
                return left >= right;
            }
             int Softj::equality(int left, int right, int node_index)
            {
                string message = "比較";
                 ProcessVisualization::ProcessAnalysis pr(ProcessVisualization::is_id_process_type_input, message, vpu->getDepth(), node_index);
                process_timeline->pushProcessAnalysis(pr);
                return left == right;
            }
             int Softj::equality(string left, string right, int node_index)
            {
                string message = "比較";
                 ProcessVisualization::ProcessAnalysis pr(ProcessVisualization::is_id_process_type_input, message, vpu->getDepth(), node_index);
                process_timeline->pushProcessAnalysis(pr);
                return left == right;
            }

    }
};
