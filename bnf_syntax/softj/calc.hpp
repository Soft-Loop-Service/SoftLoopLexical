
#ifndef __SOFTJ_INLINE_CALC
#define __SOFTJ_INLINE_CALC

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

            inline int Softj::equal(int node_index)
            {

                SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];

                int left = current_node.children[0];
                int right = current_node.children.size() >= 2 ? current_node.children[1] : -1;
                assExpr(left, right);
            }
            inline string Softj::text_join(string left, string right, int node_index)
            {
                string message = "文字列連結";
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, vpu->getDepth()};
                process_result->push_back(pr);

                return left + right;
            }

            inline int Softj::addition(int left, int right, int node_index)
            {
                string message = "加算";
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, vpu->getDepth(), node_index};
                process_result->push_back(pr);

                return left + right;
            }
            inline int Softj::subtraction(int left, int right, int node_index)
            {
                string message = "減算";
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, vpu->getDepth(), node_index};
                process_result->push_back(pr);
                return left - right;
            }
            inline int Softj::multiplication(int left, int right, int node_index)
            {
                string message = "乗算";
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, vpu->getDepth(), node_index};
                process_result->push_back(pr);
                return left * right;
            }
            inline int Softj::division(int left, int right, int node_index)
            {
                string message = "割算";
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, vpu->getDepth(), node_index};
                process_result->push_back(pr);
                return left / right;
            }
            inline int Softj::less(int left, int right, int node_index)
            {
                string message = "比較";
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, vpu->getDepth(), node_index};
                process_result->push_back(pr);
                return left < right;
            }
            inline int Softj::less_equal(int left, int right, int node_index)

            {
                string message = "比較";
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, vpu->getDepth(), node_index};
                process_result->push_back(pr);
                return left <= right;
            }
            inline int Softj::greater(int left, int right, int node_index)
            {
                string message = "比較";
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, vpu->getDepth(), node_index};
                process_result->push_back(pr);
                return left > right;
            }
            inline int Softj::greater_equal(int left, int right, int node_index)
            {
                string message = "比較";
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, vpu->getDepth(), node_index};
                process_result->push_back(pr);
                return left >= right;
            }
            inline int Softj::equality(int left, int right, int node_index)
            {
                string message = "比較";
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, vpu->getDepth(), node_index};
                process_result->push_back(pr);
                return left == right;
            }
            inline int Softj::equality(string left, string right, int node_index)
            {
                string message = "比較";
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, vpu->getDepth(), node_index};
                process_result->push_back(pr);
                return left == right;
            }

    }
};
#endif