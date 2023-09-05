
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
#include "./LR_table_cell.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <map>

template <typename T>
class LRTable
{
protected:
    vDFANode dfa_node_graph;
    int column_length;
    map<string, vector<T>> LR_table_column_map;

public:
    LRTable(vDFANode dfa_node_graph, BNFToken &bnf_token_p, RetrieveSymbol symbol)
    {
        this->dfa_node_graph = dfa_node_graph;
        this->column_length = dfa_node_graph.size();

        for (int i = 0; i < symbol.len; i++)
        {
            string cstr = string(bnf_token_p.token_string_array[symbol.array[i]]);

            vector<T> new_column = {};
            for (int j = 0; j < column_length; j++)
            {
                T new_cell = T();
                new_column.push_back(new_cell);
            }
            LR_table_column_map[cstr] = new_column;
        }
    }

    virtual void makeTable() const = 0;
};

template <typename U>
class LRTableMakeShift : LRTable<U>
{

public:
    using LRTable<U>::LRTable;

    void makeTable() const override
    {
        for (int i = 0; i < this->column_length; i++)
        {
            mp_s_i children_nodes = this->dfa_node_graph[i].children_nodes;
            for (int j = 0; j < children_nodes.size(); j++)
            {
                vstring keys = getMapKeyString(children_nodes);
                for (int k = 0; k < keys.size(); k++)
                {
                    string key = keys[k];
                    int child_node = children_nodes[key];

                    // LR_table_column_map[key].getTableSection() == LR_table_section_action ? LR_table_column_map[key].setColumnCell(i, LR_table_operation_shift, child_node) : LR_table_column_map[key].setColumnCell(i, child_node);
                }
            }
        }
    }
};

#endif