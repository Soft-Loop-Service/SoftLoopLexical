
#ifndef __SOFTJDE
#define __SOFTJDE

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

namespace LanguageSpecifications
{
    namespace SoftjLanguage
    {
        struct ValueEnumeration
        {
            string type;

            int node_index;
            string token;
        };
        typedef vector<ValueEnumeration> vValueEnumeration;

        struct FunctionMessagePassing
        {
            string function_name;
            int node_index;
            vValueEnumeration argument;
        };
        typedef vector<FunctionMessagePassing> vFunctionMessagePassing;
        typedef map<int, FunctionMessagePassing> m_i_FunctionMessagePassing;

    }
}
#endif