
#ifndef __DFA
#define __DFA

#include "./../definition.hpp"
#include "./../symbol.hpp"
#include "./../BNF/bnf_struct.hpp"
#include "./../BNF/bnf_right.hpp"

#include "./../item_set/item_set.hpp"
#include "./dfa_calc.hpp"
#include "./lr_item.hpp"
#include "./closure_expansion.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

int generateDFARoot(DFANode &root_dfa_node)
{
    root_dfa_node.node_label = "root";
    struct DeploymentTokenStruct token = {"<S>", is_id_NonterminalSymbolRight};
    struct LRItemFormulaExpansionStruct formula_expansion;
    formula_expansion.token_vector.push_back(token);
    formula_expansion.formula_expansion_label = -1;
    struct LRItemFormulaStruct formula;
    formula.LR_formula_expansion_vector.push_back(formula_expansion);
    root_dfa_node.lr_item.LR_formula_map["<_S>"] = formula;
}

int generateDFA(DeploymentStruct deployment_syntax)
{
    int dot = 0;
    DFANode root_dfa_node = DFANode();
    generateDFARoot(root_dfa_node);

    ClosureExpansion closure_expansion = ClosureExpansion(deployment_syntax, dot);
    closure_expansion.nodeClosureExpansion(root_dfa_node.lr_item, "<_S>");

    vDFANode dfa_node_graph = {};
}

#endif