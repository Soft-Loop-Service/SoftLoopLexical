
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

            printf("node_index %d\n", node_index);

            if (return_baton.size() > 0)
            {
                return;
            }

            if (current_node.parent_token == "<return>")
            {

                return_baton.push_back({});
                return;
            }
            if (current_node.token == "<return>")
            {
                int rv_index = current_node.children[1];
                Syntactic::SyntacticTreeNode c_node = (*syntactic_analysis_tree)[rv_index];
                printf("リターン解析(戻り値あり) %d : %d %d\n", node_index, rv_index, function_bation.size());
                if (function_bation.size() > 0)
                {
                    string rv_type = function_bation[function_bation.size() - 1].return_type;

                    if (rv_type == "string")
                    {
                        string rv_str = resolutionTreeCalcString(rv_index);
                        ReturnBaton rb;
                        rb.setValue(rv_str);
                        return_baton.push_back({rb});
                        return;
                    }
                    if (rv_type == "int")
                    {
                        int rv_int = resolutionTreeCalcInt(rv_index);
                        ReturnBaton rb;
                        rb.setValue(rv_int);
                        return_baton.push_back({rb});
                        return;
                    }
                }

                return_baton.push_back({});
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
                if (return_baton.size() > 0)
                {
                    return;
                }
            }
            return;
        }

    }
};
