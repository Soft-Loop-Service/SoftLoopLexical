
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

public:
    map<string, vector<T>> LR_table_column_map;

    LRTable(string table_string)
    {

        LRTableLoad *loader = new LRTableLoad(table_string);

        int width = stoi(loader->road_token());
        // result.erase(result.begin());
        int height = stoi(loader->road_token());
        // result.erase(result.begin());
        int template_cell = stoi(loader->road_token());
        // result.erase(result.begin());
        column_length = height;

        printf("LRTable sta %d %d\n", width, height);

        vector<T> new_cells = {};

        for (int i = 0; i < template_cell; i++)
        {
            T new_cell;
            new_cell.parseStringCell(loader);
            new_cells.push_back(new_cell);
        }

        for (int x = 0; x < width; x++)
        {
            string key = loader->road_token();
            // result.erase(result.begin());
            LR_table_column_map[key] = {};

            for (int i = 0; i < height; i++)
            {
                string template_cell_index = loader->road_token();
                // result.erase(result.begin());
                int template_cell_index_int = stoi(template_cell_index);

                LR_table_column_map[key].push_back(new_cells[template_cell_index_int]);
            }

            printf("LRTable size %d %d \n", LR_table_column_map.size(), LR_table_column_map[key].size());
        }

        printf("LRTable end %d %d \n", width, height);
    }

    string outputTable()
    {
        vstring cell_que = {};

        string header_text = "";

        header_text += to_string(LR_table_column_map.size());
        header_text += " ";
        header_text += to_string(column_length);

        string main_text = "";

        auto begin = LR_table_column_map.begin(), end = LR_table_column_map.end();
        for (auto iter = begin; iter != end; iter++)
        {
            string key = iter->first;

            main_text += " ";
            main_text += key;

            for (int i = 0; i < column_length; i++)
            {
                main_text += " ";

                string cellt = LR_table_column_map[key][i].getCellString();

                int has_flag = -1;
                for (int c = 0; c < cell_que.size(); c++)
                {
                    if (cell_que[c] == cellt)
                    {
                        has_flag = c;
                        break;
                    }
                }
                if (has_flag > -1)
                {
                    main_text += to_string(has_flag);
                }
                else
                {
                    cell_que.push_back(cellt);
                    main_text += to_string(cell_que.size() - 1);
                }
            }
        }

        string template_text = "";
        template_text += to_string(cell_que.size());

        for (int i = 0; i < cell_que.size(); i++)
        {
            template_text += " ";
            template_text += cell_que[i];
        }

        return header_text + " " + template_text + main_text;
    }
    void inputTabke()
    {
    }

    void makeTable();
    void debug()
    {
        vstring keys = getMapKeyString(this->LR_table_column_map);
        printf("%2s: ", "");
        for (int j = 0; j < keys.size(); j++)
        {
            printf("%10s", keys[j].c_str());
        }
        printf("\n");
        for (int i = 0; i < column_length; i++)
        {
            printf("%2d : ", i);

            for (int j = 0; j < keys.size(); j++)
            {
                // printf("%d %d\n", LR_table_column_map.size(), LR_table_column_map[keys[j]][i].next_state);
                this->LR_table_column_map[keys[j]][i].debugCell();
            }
            printf("\n");
        }
    }

    void addSymbol(string cstr)
    {
        vector<T> new_column = {};
        for (int j = 0; j < column_length; j++)
        {
            T new_cell = T();
            new_column.push_back(new_cell);
        }
        this->LR_table_column_map[cstr] = new_column;
    }
    LRTable() {}
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
            this->LR_table_column_map[cstr] = new_column;
        }
    }

    // virtual void makeTable();
};

template <typename U>
class LRTableMakeGoto : public LRTable<U>
{

public:
    using LRTable<U>::LRTable;
    // LRTableMakeGoto() {}

    void makeTable()
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
                    if (!hasKeyMap(getMapKeyString(this->LR_table_column_map), key))
                    {
                        continue;
                    }

                    int child_node = children_nodes[key];

                    this->LR_table_column_map[key][i].setCell(child_node);
                }
            }
        }
    }
};

template <typename U>
class LRTableMakeShift : public LRTable<U>
{

public:
    using LRTable<U>::LRTable;
    // LRTableMakeShift(){};

    void makeTable()
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
                    if (!hasKeyMap(getMapKeyString(this->LR_table_column_map), key))
                    {
                        continue;
                    }

                    int child_node = children_nodes[key];
                    this->LR_table_column_map[key][i].setCell(child_node);
                }
            }
        }
    }
};

template <typename U>
class LRTableMakeReduce : public LRTable<U>
{

public:
    using LRTable<U>::LRTable;
    // LRTableMakeReduce(){};

    void makeTable()
    {
        for (int c = 0; c < this->column_length; c++)
        {
            LRItemStruct lr_item = this->dfa_node_graph[c].lr_item;
            mapLRItemFormulaStruct LR_formula_map = lr_item.LR_formula_map;

            vstring LR_formula_map_keys = getMapKeyString(LR_formula_map);

            for (int i = 0; i < LR_formula_map_keys.size(); i++)
            {
                string fm_key = LR_formula_map_keys[i];
                LRItemFormulaStruct LR_formula = LR_formula_map[fm_key];

                for (int j = 0; j < LR_formula.LR_formula_expansion_vector.size(); j++)
                {
                    LRItemFormulaExpansionStruct LR_formula_expansion = LR_formula.LR_formula_expansion_vector[j];
                    vDeploymentTokenStruct lookAhead = LR_formula_expansion.lookAhead;

                    if (LR_formula_expansion.dot != LR_formula_expansion.token_vector.size())
                    {
                        continue;
                    }

                    for (int k = 0; k < lookAhead.size(); k++)
                    {
                        string la_key = lookAhead[k].token_str;

                        this->LR_table_column_map[la_key][c].setCell(fm_key, LR_formula_expansion.token_vector);
                    }
                }
            }
        }
    }
};

template <typename U>
class LRTableMakeAccept : public LRTable<U>
{

public:
    using LRTable<U>::LRTable;
    // LRTableMakeAccept();

    void makeTable()
    {
        for (int c = 1; c < this->column_length; c++)
        {
            LRItemStruct lr_item = this->dfa_node_graph[c].lr_item;
            mapLRItemFormulaStruct LR_formula_map = lr_item.LR_formula_map;

            vstring LR_formula_map_keys = getMapKeyString(LR_formula_map);

            for (int i = 0; i < LR_formula_map_keys.size(); i++)
            {
                string fm_key = LR_formula_map_keys[i];
                LRItemFormulaStruct LR_formula = LR_formula_map[fm_key];

                if (fm_key == ROOT_DFA_SYMBOL)
                {
                    this->LR_table_column_map[DOLLAR][c].setCell(true);
                }
            }
        }
    }
};

#endif