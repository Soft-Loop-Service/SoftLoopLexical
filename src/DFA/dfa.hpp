
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
}

#endif