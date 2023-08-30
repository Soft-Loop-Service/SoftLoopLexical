
#ifndef __LRITEM
#define __LRITEM
#include "./../definition.hpp"
#include "./../symbol.hpp"
#include "./../BNF/bnf_struct.hpp"
#include "./../BNF/bnf_right.hpp"
#include "./../BNF/bnf_deployment.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

struct LRItemStruct;
struct DFANode;
struct LRItemFormulaStruct;
struct LRItemFormulaExpansionStruct;
typedef std::vector<LRItemStruct> vLRItemStruct;
typedef std::vector<DFANode> vDFANode;
typedef std::vector<LRItemFormulaStruct> vLRItemFormulaStruct;
typedef std::vector<LRItemFormulaExpansionStruct> vLRItemFormulaExpansionStruct;
typedef std::map<string, LRItemFormulaStruct> mapLRItemFormulaStruct;

struct LRItemStruct // LRItemStructは自分のこと(自身node)の事しか考えることができない
{
    mapLRItemFormulaStruct LR_formula_map;
};

struct DFANode : LRItemStruct // DFANodeはLRItemStructの機能に加えて他nodeの事も考えることで基ある
{

    mp_s_i children_nodes;            // 子要素のindex
    vint has_formula_expansion_label; // 高速計算用。子ノードが何を持っているかを保有
    string node_label;                // 受理記号
    /* data */
};

// 構造体 式
struct LRItemFormulaStruct
{

    vLRItemFormulaExpansionStruct LR_formula_expansion_vector;
};

/*構造体 展開した式
lookAhead : 先読み記号
*/
struct LRItemFormulaExpansionStruct : DeploymentFormulaExpansionStruct
{
    vstring lookAhead;
};

class ClosureExpansionLRItem
{
private:
    mapDeploymentFormulaStruct formula_map;
    // LRItemStruct lr_set;
    struct LRItemStruct lr_item;
    vstring already_explored;
    int dot;
    string node_label;

public:
    string temporary_start_symbol = "<_S>";

    ClosureExpansionLRItem(LRItemStruct lr_item, mapDeploymentFormulaStruct formula_map, int dot)
    {
        this->lr_item = lr_item;
        this->formula_map = formula_map;
        this->dot = dot;
    }

    ClosureExpansionLRItem(mapDeploymentFormulaStruct formula_map, int dot)
    {
        this->formula_map = formula_map;
        this->dot = dot;
    }

    void debug()
    {
        vstring formula_map_keys_after = getMapKeyString(lr_item.LR_formula_map);
        for (int i = 0; i < formula_map_keys_after.size(); i++)
        {

            LRItemFormulaStruct t = lr_item.LR_formula_map[formula_map_keys_after[i]];
            for (int j = 0; j < t.LR_formula_expansion_vector.size(); j++)
            {
                vDeploymentTokenStruct token_vector = t.LR_formula_expansion_vector[j].token_vector;
                for (int k = 0; k < token_vector.size(); k++)
                {
                    string ts = token_vector[k].token_str;

                    printf("%s ", ts.c_str());
                }
                printf(" - ");
            }
            printf("\n");
        }
    }

    void addRoot()
    {
        struct DeploymentTokenStruct new_token = {"<S>", is_id_NonterminalSymbolRight};
        struct LRItemFormulaExpansionStruct new_lr_formula_expansion;
        new_lr_formula_expansion.token_vector.push_back(new_token);
        new_lr_formula_expansion.lookAhead.push_back("$");
        new_lr_formula_expansion.formula_expansion_label = -1;
        LRItemFormulaStruct new_lr_formula;
        new_lr_formula.LR_formula_expansion_vector.push_back(new_lr_formula_expansion);
        lr_item.LR_formula_map[temporary_start_symbol] = new_lr_formula;
    }

    // LRItemStruct nodeClosureExpansion()
    // {
    //     int pls_LR_f_size = lr_set.LR_formula_map.size();
    //     vstring pls_LR_f_keys = getMapKeyString(lr_set.LR_formula_map);
    //     for (int i = 0; i < pls_LR_f_size; i++)
    //     {
    //         string key = pls_LR_f_keys[i];

    //         recursionNodeClosureExpansion(key);
    //         printf("クロージャー展開 内終了\n");

    //         // LRItemFormulaStruct current_pls_LR_f = parent_lr_set.LR_formula_map[pls_LR_f_keys[i]];
    //         // current_pls_LR_f.
    //     }
    //     printf("クロージャー展開 終了\n");
    //     std::sort(lr_set.has_formula_expansion_label.begin(), lr_set.has_formula_expansion_label.end());

    //     return lr_set;
    // }
    // 特定のキーをもとに再帰的にクロージャー展開を行う
    LRItemStruct nodeClosureExpansion()
    {
        vstring formula_map_keys = getMapKeyString(lr_item.LR_formula_map);
        // struct LRItemStruct lr_set;

        for (int i = 0; i < formula_map_keys.size(); i++)
        {
            LRItemFormulaStruct LR_formula = lr_item.LR_formula_map[formula_map_keys[i]];

            for (int j = 0; j < LR_formula.LR_formula_expansion_vector.size(); j++)
            {
                LRItemFormulaExpansionStruct LR_formula_expansion = LR_formula.LR_formula_expansion_vector[j];

                int k = dot;

                if (k >= LR_formula_expansion.token_vector.size())
                {
                    continue;
                }

                DeploymentTokenStruct token = LR_formula_expansion.token_vector[k];
                printf("クロージャー展開による拡張 %s\n", token.token_str.c_str());
                recursionNodeClosureExpansion(token.token_str);
            }

            // recursionNodeClosureExpansion(search_key);
        }

        // std::sort(lr_item.has_formula_expansion_label.begin(), lr_item.has_formula_expansion_label.end());

        return lr_item;
    }
    // 特定のキーをもとに再帰的にクロージャー展開を行う
    LRItemStruct nodeClosureExpansion(string search_key)
    {
        // vstring formula_map_keys = getMapKeyString(lr_set.LR_formula_map);
        // struct LRItemStruct lr_set;
        recursionNodeClosureExpansion(search_key);
        // std::sort(lr_item.has_formula_expansion_label.begin(), lr_item.has_formula_expansion_label.end());

        return lr_item;
    }

private:
    void getFirstCandidate(LRItemFormulaExpansionStruct lr_s)
    {
        vDeploymentTokenStruct first_candidate = {};

        for (int j = dot; j < lr_s.token_vector.size(); j++)
        {
            DeploymentTokenStruct token = lr_s.token_vector[j];
            first_candidate.push_back(token);
            if (token.label == is_id_TerminalSymbol)
            {
                return;
            }
        }
    }

    /// @brief
    /// @param search_key  展開したいキー
    /// @param parent_key  展開元
    void recursionNodeClosureExpansion(string search_key)
    {
        if (hasKeyMap(this->already_explored, search_key))
        {
            return;
        }
        printf("クロージャー展開 %s\n", search_key.c_str());
        already_explored.push_back(search_key);
        vDeploymentFormulaExpansionStruct current_formula_expansion_vector = formula_map[search_key].formula_expansion_vector;

        // printf("current_formula_expansion_vector %ld\n",current_formula_expansion_vector.size());
        for (int i = 0; i < current_formula_expansion_vector.size(); i++)
        {
            // Deployment から LRitemへの引き継ぎ
            struct LRItemFormulaExpansionStruct lr_s;
            lr_s.formula_expansion_label = current_formula_expansion_vector[i].formula_expansion_label;
            lr_s.token_vector = current_formula_expansion_vector[i].token_vector;

            lr_item.LR_formula_map[search_key].LR_formula_expansion_vector.push_back(lr_s);

            if (dot >= lr_s.token_vector.size())
            {
                continue;
            }

            DeploymentTokenStruct token = lr_s.token_vector[dot];
            if (token.label != is_id_TerminalSymbol)
            {
                recursionNodeClosureExpansion(token.token_str);
            }

            // }
        }
    }
};

#endif