
#ifndef __SOFTJ_INLINE_FUNCTION
#define __SOFTJ_INLINE_FUNCTION

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

            // nodeを返す
            inline ProcessVisualization::FunctionUnit Softj::searchFunctionMessagePassing(int node_index)
            {

                FunctionMessagePassing fmp = function_message_passing_map[node_index];
                vValueEnumeration vve = fmp.argument;

                vstring types = {};

                for (int i = 0; i < vve.size(); i++)
                {
                    ValueEnumeration ve = vve[i];

                    if (ve.type == "unsettled")
                    {
                        string new_type = vpu->getType(ve.token);
                        printf("引数型の書き換え unsettled -> %s\n", new_type.c_str());
                        types.push_back(new_type);
                        continue;
                    }

                    types.push_back(ve.type);
                }
                ProcessVisualization::FunctionUnit function_unit = fpu->getFunction(fmp.function_name, types);

                printf("対象関数の特定 %s %d\n", function_unit.getFunctionName().c_str(), function_unit.getFunctionNode());

                return function_unit;
            }

    }};

    #endif