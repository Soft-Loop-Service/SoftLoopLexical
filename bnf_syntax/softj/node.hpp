
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

// 解析中の非末端記号と末端記号から、葉ノードの定義を行う．これは文法定義に依存する
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
    if (token_left == "<type_name>")
    {
        return syntactic_tree_node_type_valuetype;
    }
    if (token_left == "<value_name>")
    {
        return syntactic_tree_node_type_valuename;
    }

    return syntactic_tree_node_type_string;
}

#endif