
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

// プロトタイプ宣言
// int addItemSet(vItemSetTree &item_set_vector_tree, BNFToken &bnf_token_p, RetrieveSymbol &symbols, int dot);
// int modifyItemSetChildren(vItemSetTree &item_set_vector_tree, BNFToken &bnf_token_p, RetrieveSymbol &symbols, int dot);
// int recursionItemSet(vItemSetTree &item_set_vector_tree, BNFToken &bnf_token_p, RetrieveSymbol &symbols, int dot);

int constructionItemSetTree(ItemSetStruct &item_set, BNFToken &bnf_token_p, RetrieveSymbol &symbols, int dot)
{
    int index = dot - 1;

    for (int i = 0; i < symbols.len; i++)
    {
        struct ItemSetStruct new_item_set;
        int count = 0;
        // j : bnf_right 式取得番号
        for (int j = 0; j < item_set.formula_vector.size(); j++)
        {
            struct ItemSetFormulaStruct new_item_set_formula;
            // k : bnf_right 展開式取得番号
            for (int k = 0; k < item_set.formula_vector[j].formula_expansion_vector.size(); k++)
            {
                // ctc token取得番号一覧
                vItemSetTokenStruct token_vector = item_set.formula_vector[j].formula_expansion_vector[k].token_vector;
                if (index >= token_vector.size())
                {
                    continue;
                }
                int current_symbol = symbols.array[i];
                int current_bnf = token_vector[index].token_number;
                char *current_symbol_text = get_bnf_arr(bnf_token_p, current_symbol);
                char *current_bnf_text = get_bnf_arr(bnf_token_p, current_bnf);
                if (strncmp(current_symbol_text, current_bnf_text, bnf_token_len) == 0)
                {
                    // int child_index = item_set_vector.size();
                    ItemSetFormulaExpansionStruct current_formula_expansion = item_set.formula_vector[j].formula_expansion_vector[k];
                    struct ItemSetFormulaExpansionStruct copy_formula_expansion;
                    copy_formula_expansion = current_formula_expansion;
                    new_item_set_formula.formula_expansion_vector.push_back(copy_formula_expansion);
                    count++;
                }
            }
            new_item_set.formula_vector.push_back(new_item_set_formula);
        }
        if (count > 0)
        {
            item_set.children.push_back(new_item_set);
            // printf("item_set.children.push_back %ld %ld\n", new_item_set.formula_vector.size(), item_set.children.size());
        }
    }
}

/*
再帰的に木構造を構築する
*/
int recursionItemSet(ItemSetStruct &item_set, BNFToken &bnf_token_p, RetrieveSymbol &symbols, int dot)
{

    printf("現在 %3s %3s %3s %3s %3s %s\n", "dot", "j", "k", "a", "n", "get_bnf_arr");
    int bsize = item_set.formula_vector.size();
    for (int j = 0; j < bsize; j++)
    {
        for (int k = 0; k < item_set.formula_vector[j].formula_expansion_vector.size(); k++)
        {
            int asize = item_set.formula_vector[j].formula_expansion_vector[k].token_vector.size();
            for (int a = 0; a < asize; a++)
            {
                int n = item_set.formula_vector[j].formula_expansion_vector[k].token_vector[a].token_number;
                // get_bnf_arr(bnf_token_p, n)
                printf("現在 %3d %3d %3d %3d %3d %3d %s\n", dot, j, k, a, n, asize, get_bnf_arr(bnf_token_p, n));
            }
        }
        // printf("\n");
    }
    constructionItemSetTree(item_set, bnf_token_p, symbols, dot);
    int isize = item_set.children.size();

    // printf("再帰 %3s %3s %3s %3s %3s %3s %s\n", "dot", "i", "j", "k", "a", "n", "get_bnf_arr");
    // for (int i = 0; i < isize; i++)
    // {
    //     int jsize = item_set.children[i].formula_vector.size();
    //     for (int j = 0; j < jsize; j++)
    //     {
    //         for (int k = 0; k < item_set.children[i].formula_vector[j].formula_expansion_vector.size(); k++)
    //         {
    //             for (int a = 0; a < item_set.children[i].formula_vector[j].formula_expansion_vector[k].token_vector.size(); a++)
    //             {
    //                 int n = item_set.children[i].formula_vector[j].formula_expansion_vector[k].token_vector[a].token_number;
    //                 // get_bnf_arr(bnf_token_p, n)
    //                 printf("再帰 %3d %3d %3d %3d %3d %3d %s\n", dot, i, j, k, a, n, get_bnf_arr(bnf_token_p, n));
    //             }
    //         }
    //         // printf("\n");
    //     }
    // }

    for (int i = 0; i < item_set.children.size(); i++)
    {
        recursionItemSet(item_set.children[i], bnf_token_p, symbols, dot + 1);
    }
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

    struct ItemSetStruct item_set;

    // 3次元配列 上から順に すべての式：式単体：式を構成するtoken
    for (int i = 0; i < nonterminal_symbol_left.len; i++)
    {
        struct ItemSetFormulaStruct formula;
        v2int bnf_right_temp = generateBNFRight(bnf_token_p, bnf_symbol_p, nonterminal_symbol_left, i);

        for (int j = 0; j < bnf_right_temp.size(); j++)
        {
            struct ItemSetFormulaExpansionStruct formula_expansion;

            for (int k = 0; k < bnf_right_temp[j].size(); k++)
            {
                printf("bnf_right_temp size %d %d %d %ld %ld %d %s\n", i, j, k, bnf_right_temp.size(), bnf_right_temp[j].size(), bnf_right_temp[j][k], get_bnf_arr(bnf_token_p, bnf_right_temp[j][k]));

                struct ItemSetTokenStruct token;
                token.token_number = bnf_right_temp[j][k];
                formula_expansion.token_vector.push_back(token);
            }
            formula.formula_expansion_vector.push_back(formula_expansion);
        }
        item_set.formula_vector.push_back(formula);
    }

    printf("再帰探索\n");
    recursionItemSet(item_set, bnf_token_p, symbols, 1);
}

#endif