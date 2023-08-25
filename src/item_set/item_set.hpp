
#ifndef __AUTOMATONIS
#define __AUTOMATONIS
#include "./item_set_calc.hpp"
#include "./../definition.hpp"
#include "./../symbol.hpp"
#include "./../BNF/bnf_struct.hpp"
#include "./../BNF/bnf_right.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

int findFollowsSet()
{
}

/// @brief
/// @param bnf_token_p
/// @param bnf_symbol_p
/// @param nonterminal_symbol_left
/// @param nonterminal_symbol_right
/// @param terminal_symbol
/// @return
int generateItemSet(BNFToken &bnf_token_p, BNFSymbol &bnf_symbol_p, RetrieveSymbol &nonterminal_symbol_left, RetrieveSymbol &symbols)
{
    for (int i = 0; i < symbols.len; i++)
    {
        printf("symbols %d\n", symbols.array[i]);
    }

    int **LR0Automaton;
    bool arr_bool = getTwoDimensionalArray(LR0Automaton, 100, bnf_symbol_p.unique_symbol_len);
    if (!arr_bool)
    {
        printf("generateItemSet 配列確保に失敗");
    }

    struct DeploymentStruct deployment_syntax;

    // 3次元配列 上から順に すべての式：式単体：式を構成するtoken
    for (int i = 0; i < nonterminal_symbol_left.len; i++)
    {
        struct DeploymentFormulaStruct formula;
        v2string bnf_right_tokens;
        mp_s_i bnf_right_map;
        generateBNFRight(bnf_token_p, bnf_symbol_p, nonterminal_symbol_left, i, bnf_right_tokens, bnf_right_map);

        string key = string(bnf_token_p.token_string_array[nonterminal_symbol_left.array[i]]);

        for (int j = 0; j < bnf_right_tokens.size(); j++)
        {
            struct DeploymentFormulaExpansionStruct formula_expansion;

            for (int k = 0; k < bnf_right_tokens[j].size(); k++)
            {
                // printf("pusha %s %d\n", bnf_right_tokens[j][k].c_str(), bnf_right_map[bnf_right_tokens[j][k]]);
                printf("bnf_right_temp size %d %d %d %ld %ld %s %d\n", i, j, k, bnf_right_tokens.size(), bnf_right_tokens[j].size(), bnf_right_tokens[j][k].c_str(), bnf_right_map[bnf_right_tokens[j][k]]);

                struct DeploymentTokenStruct token;
                token.token_str = bnf_right_tokens[j][k];
                token.label = bnf_right_map[token.token_str];

                formula_expansion.token_vector.push_back(token);
            }
            // if (bnf_right_tokens[j].size() > 0)
            // {
            formula.formula_expansion_vector.push_back(formula_expansion);
            // }
        }
        // deployment_syntax.formula_vector.push_back(formula);

        deployment_syntax.formula_map[key] = formula;
    }
    printf("再帰探索 a\n");
    NullSetClass null_set = NullSetClass(deployment_syntax);
    vstring null_set_data = null_set.findNullsSet();

    FirstSetClass first_set = FirstSetClass(deployment_syntax, null_set_data);
    mp_s_vstring first_set_data = first_set.findFirstSet();

    FollowSetClass folllow_set = FollowSetClass(deployment_syntax, null_set_data, first_set_data);
    folllow_set.findFolllowSet();

    printf("再帰探索 b\n");
    // recursionItemSet(item_set, bnf_token_p, symbols, 1);
}

#endif