
#ifndef __BNFV
#define __BNFV

#include "./../definition.hpp"
#include "./../symbol.hpp"
#include "./../BNF/bnf_struct.hpp"
#include "./../BNF/bnf_right.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

// typedef std::vector<DeploymentGroupStruct> vDeploymentGroupStruct;
struct DeploymentStruct;
struct DeploymentFormulaStruct;
struct DeploymentFormulaExpansionStruct;
struct DeploymentTokenStruct;
typedef std::vector<DeploymentStruct> vDeploymentStruct;
typedef std::vector<DeploymentFormulaStruct> vDeploymentFormulaStruct;
typedef std::vector<DeploymentFormulaExpansionStruct> vDeploymentFormulaExpansionStruct;
typedef std::vector<DeploymentTokenStruct> vDeploymentTokenStruct;
typedef std::map<string, DeploymentFormulaStruct> mapDeploymentFormulaStruct;

struct DeploymentStruct
{
    mapDeploymentFormulaStruct formula_map;
    // vDeploymentStruct children;
};

// 構造体 式
struct DeploymentFormulaStruct
{
    vDeploymentFormulaExpansionStruct formula_expansion_vector;
};

// 構造体 展開した式
struct DeploymentFormulaExpansionStruct
{
    vDeploymentTokenStruct token_vector;
};

// 構造体 token
struct DeploymentTokenStruct
{
    string token_str;
    int label;
};

DeploymentStruct expansionDeployment(BNFToken &bnf_token_p, BNFSymbol &bnf_symbol_p, RetrieveSymbol &nonterminal_symbol_left, RetrieveSymbol &symbols)
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

    return deployment_syntax;
}

#endif