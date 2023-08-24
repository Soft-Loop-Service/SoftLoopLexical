
#ifndef __BNFRIGHT
#define __BNFRIGHT

#include "./../definition.hpp"
#include "./../symbol.hpp"
#include "./bnf_struct.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

void dequeueBNFRight(qustr &bnf_que, v2string &bnf_right)
{
    vstring ans = {};
    // printf("dequeueBNFRight que %ld\n", bnf_que.size());
    int size = bnf_que.size();

    for (int i = 0; i < size; i++)
    {
        string e = bnf_que.front();
        ans.push_back(e);
        bnf_que.pop();
    }

    // printf("dequeueBNFRight ans %ld\n", ans.size());

    bnf_right.push_back(ans);
}

void generateBNFRight(BNFToken &bnf_token_p, BNFSymbol &bnf_symbol_p, RetrieveSymbol &nonterminal_symbol_left, int current_left, v2string &bnf_right_tokens, mp_s_i &bnf_right_map)
{
    qustr bnf_que;

    int begin = nonterminal_symbol_left.array[current_left];
    int end = current_left == nonterminal_symbol_left.len - 1 ? bnf_token_p.token_len : nonterminal_symbol_left.array[current_left + 1];

    for (int current = begin + 1; current < end; current++)
    {
        switch (bnf_token_p.token_label_array[current])
        {
        case is_id_VerticalLine:
        {
            dequeueBNFRight(bnf_que, bnf_right_tokens);

            break;
        }

        case is_id_DefinitionSymbol:
        case is_id_SingleQuotation:
        case is_id_SingleQuotationLeft:
        case is_id_SingleQuotationRight:
        case is_id_DoubleQuotation:
        case is_id_DoubleQuotationLeft:
        case is_id_DoubleQuotationRight:
        {
            break;
        }

        default:
        {
            std::string str = std::string(bnf_symbol_p.symbol_string_array[current]);
            bnf_que.push(str);
            bnf_right_map[str] = bnf_token_p.token_label_array[current];
            break;
        }
        }
    }
    dequeueBNFRight(bnf_que, bnf_right_tokens);
}

#endif