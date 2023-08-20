
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

int addItemSet(vItemSetTree &item_set_vector_tree, BNFToken &bnf_token_p, RetrieveSymbol &symbols, int dot)
{
    int index = dot - 1;

    struct ItemSetStruct new_item_set = item_set_vector_tree.back();

    printf("test %4s %4s %4s %4s %4s %4s %30s children : %s\n", "i", "j", "k", "ctc", "cs", "cb", "", "ts");
    for (int i = 0; i < symbols.len; i++)
    {
        vint childlen_temp = {};

        // struct ItemSetStruct ct = item_set_vector_tree.back();
        // Current Tree

        for (int j = 0; j < new_item_set.bnf_right.size(); j++)
        {
            for (int k = 0; k < new_item_set.bnf_right[j].size(); k++)
            {
                vint ctc = new_item_set.bnf_right[j][k];
                if (index >= ctc.size())
                {
                    continue;
                }
                int current_symbol = symbols.array[i];
                int current_bnf = ctc[index];
                char *current_symbol_text = get_bnf_arr(bnf_token_p, current_symbol);
                char *current_bnf_text = get_bnf_arr(bnf_token_p, current_bnf);

                if (strncmp(current_symbol_text, current_bnf_text, bnf_token_len) == 0)
                {
                    childlen_temp.push_back(current_symbol);
                    printf("test %4d %4d %4d %4ld %4d %4d %30s children : %ld\n", i, j, k, ctc.size(), current_symbol, current_bnf, get_bnf_arr(bnf_token_p, current_bnf), new_item_set.children.size());
                }
            }
        }

        if (childlen_temp.size() > 0)
        {
            new_item_set.children.push_back(childlen_temp);
        }
    }
    // item_set_vector_tree.push_back(new_item_set);
}

int modifyItemSetChildren(vItemSetTree &item_set_vector_tree, BNFToken &bnf_token_p, RetrieveSymbol &symbols)
{
}

/*
再帰的に木構造を構築する
*/
int recursionItemSet(vItemSetTree &item_set_vector_tree, BNFToken &bnf_token_p, RetrieveSymbol &symbols, int dot)
{
    addItemSet(item_set_vector_tree, bnf_token_p, symbols, dot);
    // recursionItemSet(item_set_vector_tree, symbols, dot);
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
    int **LR0Automaton;
    bool arr_bool = getTwoDimensionalArray(LR0Automaton, 100, bnf_symbol_p.unique_symbol_len);
    if (!arr_bool)
    {
        printf("generateItemSet 配列確保に失敗");
    }

    v3int bnf_right_vector = {};
    // 3次元配列 上から順に すべての式：式単体：式を構成するtoken
    for (int i = 0; i < nonterminal_symbol_left.len; i++)
    {
        bnf_right_vector.push_back(generateBNFRight(bnf_token_p, bnf_symbol_p, nonterminal_symbol_left, i));
    }

    vItemSetTree item_set_vector_tree = {};
    // 木構造。上位がitem集合 下位がそれを構成する要素

    // rootの登録
    struct ItemSetStruct item_set_temp = {bnf_right_vector, {{}}};
    item_set_vector_tree.push_back(item_set_temp);

    printf("再帰探索\n");
    recursionItemSet(item_set_vector_tree, bnf_token_p, symbols, 1);

    // for (int i = 0; i < nonterminal_symbol_left.len; i++)
    // {

    //     // ループカウンタがLR構文解析表を作るにあたって必要なdotの位置
    //     for (int dot = 0; dot < bnf_right_vector.size(); dot++)
    //     {

    //         if (dot == 0) // 先端にいる時(読み込み済みが存在しないとき)
    //         {
    //             // rootとして追加する
    //         }
    //         else if (dot == bnf_right_vector.size()) // 末端にいるとき
    //         {
    //             int index = dot - 1;
    //         }
    //         else // それ以外
    //         {
    //             int index = dot - 1;

    //             item_set_temp.dot = dot;
    //         }
    //     }

    //     item_set_vector_tree.push_back(item_set_temp);
    // }

    // item_set.push_back(bnf_right_vector);
}

#endif