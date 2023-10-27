#ifndef __SOFTJ
#define __SOFTJ

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>

#include "./softj_definition.hpp"
#include "./../../src/syntactic/syntactic_analysis_tree.hpp"

int softj(vSyntacticTree &syntactic_analysis_tree, vSyntacticTree &progress, vint parent_stack, int current_node_index)
{
    softjDefinition(syntactic_analysis_tree, progress, parent_stack, current_node_index);
}

#endif