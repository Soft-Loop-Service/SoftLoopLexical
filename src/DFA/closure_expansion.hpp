
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
    vstring already_explored;
    vint already_explored_formula_expansion = {};
    int dot;

public:
    ClosureExpansion(DeploymentStruct deployment_syntax, int dot)
    {
        this->deployment_syntax = deployment_syntax;
        this->dot = dot;
    }
    void nodeClosureExpansion(LRItemStruct &lr_item, string search_key)
    {
        already_explored = {};
        already_explored_formula_expansion = {};
        recursionNodeClosureExpansion(lr_item, search_key);
    }

private:
    // search_key : 展開したいkey(左辺key)
    void recursionNodeClosureExpansion(LRItemStruct &lr_item, string search_key)
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

                    lr_item.LR_formula_map[token.token_str].LR_formula_expansion_vector.push_back(new_lrf_exp);
                    already_explored_formula_expansion.push_back(new_lrf_exp.formula_expansion_label);
                }
            }

            if (token.label == is_id_TerminalSymbol)
            {
                continue;
            }
            // 展開した先でも非末端記号であれば再帰的に展開する
            recursionNodeClosureExpansion(lr_item, token.token_str);
            // for (int k = 0; k < toke)
        }
        // }
    }
};

#endif
