

#include "./../definition.hpp"
#include "./../symbol.hpp"
#include "./../BNF/BNF.hpp"

#include "./../item_set/item_set.hpp"

#include "./../DFA/dfa.hpp"
#include "./LR_table.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

namespace LRTable
{

    int generateLRtable(DFAParse::vDFANode dfa_node_graph, BNFParse::BNFToken &bnf_token_p, BNFParse::RetrieveSymbol terminal_symbol, BNFParse::RetrieveSymbol nonterminal_symbol,
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

};