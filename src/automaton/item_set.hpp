
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

int addItemSet(ItemSetStruct &item_set, BNFToken &bnf_token_p, RetrieveSymbol &symbols, int dot)
{
    int index = dot - 1;

    // printf("test %4s %4s %4s %4s %4s %4s %30s children : %s\n", "i", "j", "k", "ctc", "cs", "cb", "", "ts");

    // printf("addItemSet %d %ld\n", symbols.len, item_set.formula_vector.size());

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
                    new_item_set_formula.formula_expansion_vector.push_back(item_set.formula_vector[j].formula_expansion_vector[k]);
                    printf("strncmp 一致 %2d %2ld %2d %2d %2d %30s\n", dot, token_vector.size(), i, j, k, get_bnf_arr(bnf_token_p, current_bnf));
                    count++;

                    // printf("addItemSet %4d %4d %4d %4ld %4d %4d %30s %ld children : %ld\n", i, j, k, ctc.size(), current_symbol, current_bnf, get_bnf_arr(bnf_token_p, current_bnf), back_item_set.bnf_right[j].size(), back_item_set.children.size());
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

    // return count;
    // 最後の要素に再代入する
}

// int modifyItemSetChildren(vItemSetTree &item_set_vector_tree, BNFToken &bnf_token_p, RetrieveSymbol &symbols, int dot)
// {
//     struct ItemSetStruct back_item_set = item_set_vector_tree.back();

//     int s = item_set_vector_tree.size();

//     for (int i = 0; i < back_item_set.children.size(); i++)
//     {
//         // printf("back_item_set.children.size %d %ld\n", i, back_item_set.children[i].size());
//         struct ItemSetStruct new_item_set;

//         // new_item_set.bnf_right.push_back(back_item_set.children[i]);

//         new_item_set.bnf_right = back_item_set.children[i];

//         // for (int j = 0; j < back_item_set.children[i].size(); j++)
//         // {
//         //     // int k = back_item_set.children[i][j];
//         //     new_item_set.bnf_right.push_back(back_item_set.bnf_right[k]);
//         //     printf("modifyItemSetChildren %d %d %d %ld\n", i, j, k, back_item_set.bnf_right.size());
//         // }

//         item_set_vector_tree.push_back(new_item_set);
//         recursionItemSet(item_set_vector_tree, bnf_token_p, symbols, dot + 1);
//     }

//     int e = item_set_vector_tree.size();
//     printf("modifyItemSetChildren %d %d %ld %ld\n", s, e, back_item_set.children.size(), item_set_vector_tree.size());
//     return s; // どこから挿入したかという情報を返す
// }

/*
再帰的に木構造を構築する
*/
int recursionItemSet(ItemSetStruct &item_set, BNFToken &bnf_token_p, RetrieveSymbol &symbols, int dot)
{
    // int count = addItemSet(item_set, bnf_token_p, symbols, dot);

    // printf("現在 %3s %3s %3s %3s %3s %s\n", "dot", "j", "k", "a", "n", "get_bnf_arr");
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
    addItemSet(item_set, bnf_token_p, symbols, dot);
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
        // printf("再帰 %d\n", item_set.children[i], dot);
        recursionItemSet(item_set.children[i], bnf_token_p, symbols, dot + 1);
    }
    // printf("recursionItemSet %ld %d\n", item_set.children.size(), dot);
    // for (int i = 0; i < item_set.children.size(); i++)
    // {
    //     printf("再帰 %d\n", item_set.children[i], dot);
    //     recursionItemSet(item_set.children[i], bnf_token_p, symbols, dot + 1);
    // }

    // int current = modifyItemSetChildren(item_set_vector_tree, bnf_token_p, symbols, dot);

    // printf("recursionItemSet %d\n", count);

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

    // vItemSetStruct item_set_vector = {};
    struct ItemSetStruct item_set;

    // 3次元配列 上から順に すべての式：式単体：式を構成するtoken
    for (int i = 0; i < nonterminal_symbol_left.len; i++)
    {
        struct ItemSetFormulaStruct formula;
        v2int bnf_right_temp = generateBNFRight(bnf_token_p, bnf_symbol_p, nonterminal_symbol_left, i);

        for (int j = 0; j < bnf_right_temp.size(); j++)
        {
            struct ItemSetFormulaExpansionStruct formula_expansion;
            printf("bnf_right_temp size %ld %ld\n", bnf_right_temp.size(), bnf_right_temp[j].size());
            for (int k = 0; k < bnf_right_temp[j].size(); k++)
            {
                struct ItemSetTokenStruct token;
                token.token_number = bnf_right_temp[j][k];
                formula_expansion.token_vector.push_back(token);
            }
            formula.formula_expansion_vector.push_back(formula_expansion);
        }
        item_set.formula_vector.push_back(formula);
    }
    // item_set_vector.push_back(item_set);
    // 木構造。上位がitem集合 下位がそれを構成する要素

    // rootの登録
    // struct ItemSetStruct item_set_temp = {bnf_right_vector, {{}}};
    // item_set_vector_tree.push_back(item_set_temp);

    printf("再帰探索\n");
    recursionItemSet(item_set, bnf_token_p, symbols, 1);

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