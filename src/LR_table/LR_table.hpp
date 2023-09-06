
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

struct LRTableMultilayer
{
    LRTableMakeGoto<LRTableGotoCell> LR_table_goto;
    LRTableMakeShift<LRTableShiftCell> LR_table_shift;
    LRTableMakeReduce<LRTableReduceCell> LR_table_reduce;
    LRTableMakeAccept<LRTableAcceptCell> LR_table_accept;
};

int generateLRtable(vDFANode dfa_node_graph, BNFToken &bnf_token_p, RetrieveSymbol terminal_symbol, RetrieveSymbol nonterminal_symbol,
                    LRTableMultilayer &LR_table_multilayer)
{
    LR_table_multilayer = LRTableMultilayer{
        LRTableMakeGoto<LRTableGotoCell>(dfa_node_graph, bnf_token_p, nonterminal_symbol),
        LRTableMakeShift<LRTableShiftCell>(dfa_node_graph, bnf_token_p, terminal_symbol),
        LRTableMakeReduce<LRTableReduceCell>(dfa_node_graph, bnf_token_p, terminal_symbol),
        LRTableMakeAccept<LRTableAcceptCell>(dfa_node_graph, bnf_token_p, terminal_symbol)};

    // LR_table_goto.addSymbol(ROOT_DFA_SYMBOL);
    LR_table_multilayer.LR_table_shift.addSymbol(DOLLAR);
    LR_table_multilayer.LR_table_reduce.addSymbol(DOLLAR);
    LR_table_multilayer.LR_table_accept.addSymbol(DOLLAR);

    LR_table_multilayer.LR_table_goto.makeTable();
    LR_table_multilayer.LR_table_goto.debug();

    LR_table_multilayer.LR_table_shift.makeTable();
    LR_table_multilayer.LR_table_shift.debug();

    LR_table_multilayer.LR_table_reduce.makeTable();
    LR_table_multilayer.LR_table_reduce.debug();

    LR_table_multilayer.LR_table_accept.makeTable();
    LR_table_multilayer.LR_table_accept.debug();
    // LRTableMakeShift LR_table_shift = LRTableMakeShift<LRTableGotoCell>(dfa_node_graph, bnf_token_p, terminal_symbol);
}

#endif