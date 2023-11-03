
#ifndef __SOFTJNODE
#define __SOFTJNODE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include "./../../src/syntactic/syntactic_analysis_tree.hpp"
#include "./../../src/symbol.hpp"

int getSyntacticAnalysisTreeNodeType(string token_left, string bnf_token)
{
    int node_type;
    if (bnf_token == "=" || bnf_token == "+" || bnf_token == "-" || bnf_token == "*" || bnf_token == "/")
    {
        return syntactic_tree_node_type_operation_formula;
    }
    if (token_left == "<number>")
    {
        return syntactic_tree_node_type_number;
    }

    return syntactic_tree_node_type_string;
}

#endif