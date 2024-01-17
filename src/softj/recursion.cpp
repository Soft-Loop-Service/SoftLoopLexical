
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

        void Softj::recursion(int node_index)
        {
            Syntactic::SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
            string token = current_node.token;

            printf("node_index %d\n",node_index);

            if (is_action_return)
            {
                return;
            }

            if (token == "=")
            {
                equal(node_index);
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

            for (int i = 0; i < current_node.children.size(); i++)
            {
                recursion(current_node.children[i]);
            }
            return;
        }

    }
};
