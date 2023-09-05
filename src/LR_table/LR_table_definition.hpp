
#ifndef __LRTABLED
#define __LRTABLED

#include "./../definition.hpp"
#include "./../symbol.hpp"
#include "./../BNF/bnf_struct.hpp"
#include "./../BNF/bnf_right.hpp"

#include "./../item_set/item_set.hpp"
#include "./../DFA/dfa_calc.hpp"
#include "./../DFA/lr_item.hpp"
#include "./../DFA/closure_expansion.hpp"
#include "./../DFA/dfa.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <map>

#define LR_table_operation_None 0
#define LR_table_operation_shift 1
#define LR_table_operation_reduce 2
#define LR_table_operation_accept 3

const int LR_table_section_action = 11;
const int LR_table_section_goto = 12;

class LRTableCell;
class LRTableColumn;
class LRTable;
typedef std::vector<LRTableCell> vLRTableCell;
typedef std::vector<LRTableColumn> vLRTableColumn;
typedef std::map<std::string, LRTableColumn> mapLRTableColumn;

class LRTableCell
{
private:
    int operation_type;
    int operation_number;

public:
    LRTableCell()
    {
        this->operation_type = LR_table_operation_None;
        this->operation_number = -1;
    }
};

class LRTableColumn
{
private:
    vLRTableCell column_cells;
    string symbol;     // 紐づけられる非末端記号,末端記号
    int table_section; // goto表なのか、action表なのかを区別する
    int column_length; // 列の長さ（=高さ,行数）を管理する

public:
    // string symbol, int table_section, int column_length
    LRTableColumn()
    {
    }

    LRTableColumn(string symbol, int table_section, int column_length)
    {
        this->symbol = symbol;
        this->table_section = table_section;
        this->column_length = column_length;
        this->column_cells = {};

        for (int i = 0; i < column_length; i++)
        {
            column_cells.push_back(LRTableCell());
        }
    }
};

class LRTable
{
private:
    vDFANode dfa_node_graph;
    mapLRTableColumn LR_table_column_map;
    int column_length;

public:
    LRTable(vDFANode dfa_node_graph)
    {
        this->dfa_node_graph = dfa_node_graph;
        this->column_length = dfa_node_graph.size();
    }

    void initGotoTalbe(BNFToken &bnf_token_p, RetrieveSymbol nonterminal_symbol)
    {
        for (int i = 0; i < nonterminal_symbol.len; i++)
        {
            string cstr = string(bnf_token_p.token_string_array[nonterminal_symbol.array[i]]);
            LRTableColumn new_column(cstr, LR_table_section_goto, column_length);
            LR_table_column_map[cstr] = new_column;
        }
    }

    void initActionTable(BNFToken &bnf_token_p, RetrieveSymbol terminal_symbol)
    {
        for (int i = 0; i < terminal_symbol.len; i++)
        {
            string cstr = string(bnf_token_p.token_string_array[terminal_symbol.array[i]]);
            // LRTableColumn new_column = LRTableColumn();
            LRTableColumn new_column = LRTableColumn(cstr, LR_table_section_action, column_length);
            // LR_table_column_map[cstr] = new_column;
        }
    }

private:
};

#endif