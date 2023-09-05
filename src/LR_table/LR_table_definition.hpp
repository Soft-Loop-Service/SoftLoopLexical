
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

#define LR_table_operation_None 'n'
#define LR_table_operation_shift 's'
#define LR_table_operation_reduce 'r'
#define LR_table_operation_accept 'a'

#define LR_table_section_action 11
#define LR_table_section_goto 12

class LRTableCell;
class LRTableColumn;
class LRTable;
typedef std::vector<LRTableCell> vLRTableCell;
typedef std::vector<LRTableColumn> vLRTableColumn;
typedef std::map<std::string, LRTableColumn> mapLRTableColumn;

class LRTableCell
{
private:
public:
    char operation_type;
    int operation_number;
    LRTableCell()
    {
        this->operation_type = LR_table_operation_None;
        this->operation_number = -1;
    }
    void setCell(char operation_type, int operation_number)
    {
        this->operation_type = operation_type;
        this->operation_number = operation_number;
    }
    void setCell(int operation_number)
    {

        this->operation_type = LR_table_operation_None;
        this->operation_number = operation_number;
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
    LRTableColumn(){};
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
    void outputTitle()
    {
        printf("%5s ", symbol.c_str());
    }
    void outputCell(int index)
    {
        if (column_cells[index].operation_number != -1)
        {
            string temp1 = to_string(column_cells[index].operation_number);
            string temp2 = {column_cells[index].operation_type};
            printf("%5s ", (temp2 + temp1).c_str());
        }
        else
        {
            printf("%5s ", "");
        }
    }

    int getTableSection()
    {
        return table_section;
    }

    void setColumnCell(int index, int next_state)
    {

        column_cells[index].setCell(next_state);
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

    void output()
    {
        vstring keys = getMapKeyString(LR_table_column_map);
        printf("%3s : ", "");
        for (int j = 0; j < keys.size(); j++)
        {
            if (LR_table_column_map[keys[j]].getTableSection() == LR_table_section_action)
            {
                LR_table_column_map[keys[j]].outputTitle();
            }
        }
        for (int j = 0; j < keys.size(); j++)
        {
            if (LR_table_column_map[keys[j]].getTableSection() == LR_table_section_goto)
            {
                LR_table_column_map[keys[j]].outputTitle();
            }
        }
        printf("\n");

        for (int i = 0; i < this->column_length; i++)
        {
            printf("%3d : ", i);
            for (int j = 0; j < keys.size(); j++)
            {
                if (LR_table_column_map[keys[j]].getTableSection() == LR_table_section_action)
                {
                    LR_table_column_map[keys[j]].outputCell(i);
                }
            }
            for (int j = 0; j < keys.size(); j++)
            {
                if (LR_table_column_map[keys[j]].getTableSection() == LR_table_section_goto)
                {
                    LR_table_column_map[keys[j]].outputCell(i);
                }
            }
            printf("\n");
        }
    }

    void generateLRTable()
    {
        for (int i = 0; i < column_length; i++)
        {
            mp_s_i children_nodes = dfa_node_graph[i].children_nodes;
            for (int j = 0; j < children_nodes.size(); j++)
            {
                vstring keys = getMapKeyString(children_nodes);
                for (int k = 0; k < keys.size(); k++)
                {
                    string key = keys[k];
                    int child_node = children_nodes[key];
                    printf("operation_number %s %d %d\n", key.c_str(), i, child_node);
                    LR_table_column_map[key].setColumnCell(i, child_node);
                }
            }
        }
    }

    void initActionTable(BNFToken &bnf_token_p, RetrieveSymbol terminal_symbol)
    {
        for (int i = 0; i < terminal_symbol.len; i++)
        {
            string cstr = string(bnf_token_p.token_string_array[terminal_symbol.array[i]]);
            LRTableColumn new_column = LRTableColumn(cstr, LR_table_section_action, column_length);
            LR_table_column_map[cstr] = new_column;
        }
    }
    void initGotoTable(BNFToken &bnf_token_p, RetrieveSymbol nonterminal_symbol)
    {
        for (int i = 0; i < nonterminal_symbol.len; i++)
        {
            string cstr = string(bnf_token_p.token_string_array[nonterminal_symbol.array[i]]);
            LRTableColumn new_column = LRTableColumn(cstr, LR_table_section_goto, column_length);
            LR_table_column_map[cstr] = new_column;
        }
    }

private:
};

#endif