
#ifndef __CLS_EXP
#define __CLS_EXP

#include "./dfa_calc.hpp"
#include "./lr_item.hpp"

#include "./../definition.hpp"
#include "./../symbol.hpp"
#include "./../BNF/bnf_struct.hpp"
#include "./../BNF/bnf_right.hpp"
#include "./../BNF/bnf_deployment.hpp"

#include "./../item_set/item_set.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

/*
dot と tokenの関係は以下の通り
  token0 token1 token2 token3 ・・・
dot0   dot1  dot2   dot3・・・
*/

class ClosureExpansion
{
private:
    DeploymentStruct deployment_syntax;
    vstring already_explored = {};
    vint already_explored_formula_expansion = {};
    NullSetClass null_set_class;
    FirstSetClass first_set_class;
    int dot = -1;

public:
    ClosureExpansion(DeploymentStruct deployment_syntax, int dot)
    {
        this->deployment_syntax = deployment_syntax;
        this->dot = dot;
        null_set_class = NullSetClass(deployment_syntax);
        first_set_class = FirstSetClass(deployment_syntax, null_set_class.findNullsSet());
    }

    // ITEM集合内のすべての要素を展開する
    void nodeClosureExpansion(LRItemStruct &lr_item)
    {
        already_explored = {};
        already_explored_formula_expansion = {};

        vstring LR_formula_map_keys = getMapKeyString(lr_item.LR_formula_map);

        for (int i = 0; i < LR_formula_map_keys.size(); i++)
        {
            string key = LR_formula_map_keys[i];
            // lr_item.LR_formula_map[key].LR_formula_expansion_vector
            recursionNodeClosureExpansion(lr_item, key, {});
        }
    }

    // ITEM集合内の一部の要素を展開する
    void nodeClosureExpansion(LRItemStruct &lr_item, string search_key)
    {
        already_explored = {};
        already_explored_formula_expansion = {};
        recursionNodeClosureExpansion(lr_item, search_key, {});
    }

private:
    // dotの後ろにある末端記号・非末端記号と、先読み記号を合体させる
    vDeploymentTokenStruct getLatterToken(LRItemFormulaExpansionStruct LR_formula_expansion)
    {
        vDeploymentTokenStruct latter_token = {};
        for (int i = dot + 1; i < LR_formula_expansion.token_vector.size(); i++)
        {
            latter_token.push_back(LR_formula_expansion.token_vector[i]);
        }

        for (int i = 0; i < LR_formula_expansion.lookAhead.size(); i++)
        {
            latter_token.push_back(LR_formula_expansion.lookAhead[i]);
        }
        return latter_token;
    }

    vstring getLatterFirstSet(LRItemFormulaExpansionStruct LR_formula_expansion)
    {
        vDeploymentTokenStruct latter_token = getLatterToken(LR_formula_expansion);
        vstring first_set = first_set_class.findFirstSet(latter_token);
        return first_set;
    }

    /* search_key : 展開したいkey(左辺key)
    再帰において、作業階層となるのは、展開元となる
    parent_lookAheadの要素数
    ・0のとき：探索開始 個別探索においても探索する必要がない(一連のtoken列があって成り立つ)
     */
    void recursionNodeClosureExpansion(LRItemStruct &lr_item, string search_key, vDeploymentTokenStruct parent_lookAhead)
    {
        if (hasKeyMap(this->already_explored, search_key))
        {
            return;
        }
        already_explored.push_back(search_key);

        LRItemFormulaStruct lr_item_formula = lr_item.LR_formula_map[search_key];
        vLRItemFormulaExpansionStruct LR_formula_expansion_vector = lr_item_formula.LR_formula_expansion_vector;

        int LR_formula_expansion_vector_size = LR_formula_expansion_vector.size();
        for (int j = 0; j < LR_formula_expansion_vector_size; j++)
        {
            LRItemFormulaExpansionStruct LR_formula_expansion = LR_formula_expansion_vector[j];
            vDeploymentTokenStruct token_vector = LR_formula_expansion.token_vector;

            if (dot >= token_vector.size())
            {
                continue;
            }

            DeploymentTokenStruct token = token_vector[dot];
            // 展開しなければならないkey(右辺)
            // これをもとに、左辺を呼び出して展開する

            // データの移譲
            vDeploymentFormulaExpansionStruct dfexp = deployment_syntax.formula_map[token.token_str].formula_expansion_vector;

            for (int k = 0; k < dfexp.size(); k++)
            {

                if (!hasKeyMap(already_explored_formula_expansion, dfexp[k].formula_expansion_label))
                {
                    struct LRItemFormulaExpansionStruct new_lrf_exp;
                    new_lrf_exp.token_vector = dfexp[k].token_vector;
                    new_lrf_exp.formula_expansion_label = dfexp[k].formula_expansion_label;

                    for (int a = 0; a < parent_lookAhead.size(); a++)
                    {
                        new_lrf_exp.lookAhead.push_back(parent_lookAhead[a]);
                    }

                    // new_lrf_exp.lookAhead = lookAhead;

                    lr_item.LR_formula_map[token.token_str].LR_formula_expansion_vector.push_back(new_lrf_exp);
                    already_explored_formula_expansion.push_back(new_lrf_exp.formula_expansion_label);
                }
            }

            if (token.label == is_id_TerminalSymbol)
            {
                continue;
            }
            // 展開した先でも非末端記号であれば再帰的に展開する

            vstring next_lookAhead = getLatterFirstSet(LR_formula_expansion);
            recursionNodeClosureExpansion(lr_item, token.token_str, next_lookAhead);
            // for (int k = 0; k < toke)
        }
        // }
    }
};

#endif
