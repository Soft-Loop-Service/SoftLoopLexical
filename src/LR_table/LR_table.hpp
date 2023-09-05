
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
#include "./LR_table_cell.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

int generateLRtable(vDFANode dfa_node_graph, BNFToken &bnf_token_p, RetrieveSymbol terminal_symbol, RetrieveSymbol nonterminal_symbol)
{
    LRTableMakeGoto LR_table_goto = LRTableMakeGoto<LRTableGotoCell>(dfa_node_graph, bnf_token_p, nonterminal_symbol);
    LRTableMakeShift LR_table_accept = LRTableMakeShift<LRTableShiftCell>(dfa_node_graph, bnf_token_p, terminal_symbol);
    LR_table_goto.makeTable();
    LR_table_goto.debug();

    LR_table_accept.debug();

    // LRTableReduceCell LR_table_reduce = LRTableReduceCell<LRTableReduceCell>(dfa_node_graph, bnf_token_p, terminal_symbol);
    // LRTableMakeShift LR_table_shift = LRTableMakeShift<LRTableGotoCell>(dfa_node_graph, bnf_token_p, terminal_symbol);
}

#endif