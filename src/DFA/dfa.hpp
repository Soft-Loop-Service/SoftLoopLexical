
#ifndef __DFA
#define __DFA

#include "./../definition.hpp"
#include "./../symbol.hpp"
#include "./../BNF/bnf_struct.hpp"
#include "./../BNF/bnf_right.hpp"

#include "./../item_set/item_set.hpp"
#include "./dfa_calc.hpp"
#include "./lr_item.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

int generateDFA(DeploymentStruct deployment_syntax)
{
    vDfaNode dfa_node_array = {};
    int dot = 0;

    DfaNode root_dfa_node = DfaNode(deployment_syntax.formula_map,dot);
    root_dfa_node.addRoot();
    root_dfa_node.nodeClosureExpansion("<S>",root_dfa_node.temporary_start_symbol);
}

#endif