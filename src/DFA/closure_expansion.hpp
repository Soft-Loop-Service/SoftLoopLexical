
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
    int dot = -1;

public:
    ClosureExpansion(DeploymentStruct deployment_syntax, int dot)
    {
        this->deployment_syntax = deployment_syntax;
        this->dot = dot;
    }
    void nodeClosureExpansion(LRItemStruct &lr_item)
    {
        already_explored = {};
        already_explored_formula_expansion = {};

        vstring LR_formula_map_keys = getMapKeyString(lr_item.LR_formula_map);

        for (int i = 0; i < LR_formula_map_keys.size(); i++)
        {
            string key = LR_formula_map_keys[i];

            for (int j = 0; j < lr_item.LR_formula_map[key].LR_formula_expansion_vector.size(); j++)
            {
                vDeploymentTokenStruct first_set = getLatterFirstSet(lr_item.LR_formula_map[key].LR_formula_expansion_vector[j]);
                recursionNodeClosureExpansion(lr_item, key, j,first_set);
            }
        }
    }

    void nodeClosureExpansion(LRItemStruct &lr_item, string search_key)
    {
        already_explored = {};
        already_explored_formula_expansion = {};
        for (int j = 0; j < lr_item.LR_formula_map[search_key].LR_formula_expansion_vector.size(); j++)
        {
            vDeploymentTokenStruct first_set = getLatterFirstSet(lr_item.LR_formula_map[search_key].LR_formula_expansion_vector[j]);
            recursionNodeClosureExpansion(lr_item, search_key, j,first_set);
        }
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
            // findFirstSetVectorに対してはvDeploymentTokenStructの形で渡さねばならぬが、これが阻んでいる
        }

        return latter_token;
    }

    vDeploymentTokenStruct getLatterFirstSet(LRItemFormulaExpansionStruct LR_formula_expansion)
    {
        NullSetClass cnull_set_class = NullSetClass(deployment_syntax);
        FirstSetClass cfirst_set_class = FirstSetClass(deployment_syntax, cnull_set_class.findNullsSet());

        vDeploymentTokenStruct latter_token = getLatterToken(LR_formula_expansion);
        vDeploymentTokenStruct first_set = cfirst_set_class.findFirstSetVector(latter_token);

        printf("latter_token , getLatterFirstSet %d %d\n",latter_token.size(),first_set.size());
        for (int la = 0; la < latter_token.size();la++){
            printf("latter_token %s\n",latter_token[la].token_str.c_str());
        }
        for (int la = 0; la < first_set.size();la++){
            printf("getLatterFirstSet %s\n",first_set[la].token_str.c_str());
        }

        return first_set;
    }

    // search_key : 展開したいkey(左辺key)
    // 展開した式ごとに関数を実行する
    void recursionNodeClosureExpansion(LRItemStruct &lr_item, string search_key, int LR_formula_expansion_vector_index,vDeploymentTokenStruct first_set)
    {

        printf("recursionNodeClosureExpansion 展開 : %s %d\n", search_key.c_str(), LR_formula_expansion_vector_index);

        LRItemFormulaStruct lr_item_formula = lr_item.LR_formula_map[search_key];
        vLRItemFormulaExpansionStruct LR_formula_expansion_vector = lr_item_formula.LR_formula_expansion_vector;

        LRItemFormulaExpansionStruct LR_formula_expansion = LR_formula_expansion_vector[LR_formula_expansion_vector_index];
        vDeploymentTokenStruct token_vector = LR_formula_expansion.token_vector;

        if (dot >= token_vector.size())
        {
            return;
        }

        DeploymentTokenStruct token = token_vector[dot];
        // 展開しなければならないkey(右辺)
        // これをもとに、左辺を呼び出して展開する

        if (token.label == is_id_TerminalSymbol)
        {
            return;
        }
        
        // データの移譲
        vDeploymentFormulaExpansionStruct dfexp = deployment_syntax.formula_map[token.token_str].formula_expansion_vector;

        for (int k = 0; k < dfexp.size(); k++)
        {

            if (!hasKeyMap(already_explored_formula_expansion, dfexp[k].formula_expansion_label))
            {
                struct LRItemFormulaExpansionStruct new_lrf_exp;
                new_lrf_exp.token_vector = dfexp[k].token_vector;
                new_lrf_exp.formula_expansion_label = dfexp[k].formula_expansion_label;
                new_lrf_exp.lookAhead = first_set;

                printf("クロージャー展開新規追加 %s %d\n",token.token_str.c_str(),new_lrf_exp.lookAhead.size());

                for (int la = 0; la < new_lrf_exp.lookAhead.size();la++){
                    printf("先読み記号 %s\n",new_lrf_exp.lookAhead[la].token_str.c_str());
                }

                lr_item.LR_formula_map[token.token_str].LR_formula_expansion_vector.push_back(new_lrf_exp);
                already_explored_formula_expansion.push_back(new_lrf_exp.formula_expansion_label);
            }
        }


        if (hasKeyMap(this->already_explored, search_key))
        {
            printf("拒否 %s\n", search_key.c_str());
            return;
        }
        already_explored.push_back(search_key);

        // 展開した先でも非末端記号であれば再帰的に展開する
        int nfx_size = lr_item.LR_formula_map[token.token_str].LR_formula_expansion_vector.size();
        printf("再帰展開 %d\n", nfx_size);
        for (int j = 0; j < nfx_size; j++)
        {
            vDeploymentTokenStruct new_first_set = getLatterFirstSet(lr_item.LR_formula_map[token.token_str].LR_formula_expansion_vector[j]);
            recursionNodeClosureExpansion(lr_item, token.token_str, j,new_first_set);
        }

        // for (int k = 0; k < toke)

        // }
    }
};

#endif
