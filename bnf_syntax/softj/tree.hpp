
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
#include "./definition.hpp"

namespace LanguageSpecifications
{
    namespace SoftjLanguage
    {

        namespace SoftjTree
        {
        private:
            vSyntacticTree *syntactic_analysis_tree;

            vint stack_node = {};

        public:
            void recursion(int node_index)
            {
                SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
                string token = current_node.token;

                if (is_action_return)
                {
                    return;
                }

                // 関数は前処理ですでに解析されている
                if (token == "<function>")
                {
                    return;
                }

                //if実行
                if (token == "<if>")
                {
                    ifCalc(node_index);
                    return;
                }
                //while実行
                if (token == "<while>")
                {
                    whileCalc(node_index);
                    return;
                }
                //関数実行
                // 単独でvalue_nameが存在する場合は、関数呼び出しである
                if (current_node.parent_token == "<value_name>")
                {
                    resolutionCalcFunction(node_index);
                    return;
                }
                
                //四則演算実行
                if (token == "+" || token == "-" || token == "*" || token == "/" || token == "<" || token == "<=" || token == ">" || token == ">=" || token == "==")
                {
                    resolutionCalcInt(node_index);
                    return;
                }

                //代入実行
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
        };

    };
};

#endif