
#ifndef __SOFTJ_INLINE_REC
#define __SOFTJ_INLINE_REC

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

        void Softj::recursion(int node_index)
        {
            SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
            string token = current_node.token;

            if (is_action_return)
            {
                return;
            }

            if (token == "+" || token == "-" || token == "*" || token == "/" || token == "<" || token == "<=" || token == ">" || token == ">=" || token == "==")
            {
                resolutionTreeCalcInt(node_index);
                return;
            }
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
            if (token == "<new_array>" || token == "<array_name>")
            {
                resolutionTreeCalcArray(node_index);
                return;
            }
            // 単独でvalue_nameが存在する場合は、関数呼び出し等である
            if (current_node.parent_token == "<value_name>")
            {
                resolutionCalcFunction(node_index);
                return;
            }

            // 関数は前処理ですでに解析されている
            if (token == "<function>")
            {
                return;
            }

            if (token == "=")
            {
                equal(node_index);
                return;
            }
            for (int i = 0; i < current_node.children.size(); i++)
            {
                recursion(current_node.children[i]);
            }
            return;
        }

    }
};
#endif