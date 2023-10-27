#ifndef __SOFTJD
#define __SOFTJD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include "./../../src/syntactic/syntactic_analysis_tree.hpp"

int softjDefinitionTerminal(vSyntacticTree &syntactic_analysis_tree, int current_node_index)
{
    SyntacticTreeNode current_node = syntactic_analysis_tree[current_node_index];
}

int softjDefinitionNonTerminal(vSyntacticTree &syntactic_analysis_tree, int current_node_index)
{
    SyntacticTreeNode current_node = syntactic_analysis_tree[current_node_index];
    vint children = current_node.children;
}

int softjDefinition(vSyntacticTree &syntactic_analysis_tree, vSyntacticTree &progress, vint parent_stack, int current_node_index)
{
    SyntacticTreeNode current_node = syntactic_analysis_tree[current_node_index];

    if (current_node.token_label == is_id_NonterminalSymbol)
    {
        softjDefinitionNonTerminal(syntactic_analysis_tree, current_node_index);
    }

    else
    {
        softjDefinitionTerminal(syntactic_analysis_tree, current_node_index);
    }
}

#endif