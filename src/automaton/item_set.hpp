
#ifndef __AUTOMATONIS
#define __AUTOMATONIS

#include "./../definition.hpp"
#include "./automaton_definition.hpp"
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
        mapstrint bnf_right_map;
        generateBNFRight(bnf_token_p, bnf_symbol_p, nonterminal_symbol_left, i, bnf_right_tokens, bnf_right_map);
        string key = string(bnf_token_p.token_string_array[nonterminal_symbol_left.array[i]]);

        for (int j = 0; j < bnf_right_map.size(); j++)
        {
            struct DeploymentFormulaExpansionStruct formula_expansion;

            for (int k = 0; k < bnf_right_tokens[j].size(); k++)
            {
                printf("bnf_right_temp size %d %d %d %ld %ld %d %s\n", i, j, k, bnf_right_tokens.size(), bnf_right_tokens[j].size(), bnf_right_tokens[j][k], bnf_right_tokens[j][k]);

                struct DeploymentTokenStruct token;
                token.token_str = bnf_right_tokens[j][k];
                token.label = bnf_right_map[token.token_str];
                formula_expansion.token_vector.push_back(token);
            }
            formula.formula_expansion_vector.push_back(formula_expansion);
        }
        // deployment_syntax.formula_vector.push_back(formula);
        deployment_syntax.formula_map[key] = formula;
    }

    FollowsSetClass follow_set = FollowsSetClass(deployment_syntax);

    printf("再帰探索\n");
    // recursionItemSet(item_set, bnf_token_p, symbols, 1);
}

#endif