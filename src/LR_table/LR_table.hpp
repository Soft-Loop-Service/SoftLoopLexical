
#ifndef __LRTABLE
#define __LRTABLE

#include "./../definition.hpp"
#include "./../symbol.hpp"
#include "./../BNF/bnf_struct.hpp"
#include "./../BNF/bnf_right.hpp"

#include "./../item_set/item_set.hpp"
#include "./../DFA/dfa_calc.hpp"
#include "./../DFA/lr_item.hpp"
#include "./../DFA/closure_expansion.hpp"
#include "./../DFA/dfa.hpp"
#include "./LR_table_definition.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

int generateLRtable(vDFANode dfa_node_graph, BNFToken &bnf_token_p, RetrieveSymbol nonterminal_symbol, RetrieveSymbol terminal_symbol)
{
    LRTable LR_table = LRTable(dfa_node_graph);
    LR_table.initActionTable(bnf_token_p, nonterminal_symbol);
    LR_table.initGotoTalbe(bnf_token_p, terminal_symbol);
}

#endif