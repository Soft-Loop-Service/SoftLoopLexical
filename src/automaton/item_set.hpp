
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

int generateItemSet(BNFToken &bnf_token_p, BNFSymbol &bnf_symbol_p, RetrieveSymbol &nonterminal_symbol_left)
{
    int **LR0Automaton;
    bool arr_bool = getTwoDimensionalArray(LR0Automaton, 100, bnf_symbol_p.unique_symbol_len);
    if (!arr_bool)
    {
        printf("generateItemSet 配列確保に失敗");
    }

    for (int i = 0; i < nonterminal_symbol_left.len; i++)
    {
        v2int bnf_right = generateBNFRight(bnf_token_p, bnf_symbol_p, nonterminal_symbol_left, i);
        // ループカウンタがLR構文解析表を作るにあたって必要なdotの位置
        for (int dot = 0; dot < bnf_right.size(); dot++)
        {
            if (dot == 0) // 先端にいる時(読み込み済みが存在しないとき)
            {
            }
            else if (dot == bnf_right.size()) // 末端にいるとき
            {
                int index = dot - 1;
            }
            else // それ以外
            {
            }
        }
    }
}

#endif