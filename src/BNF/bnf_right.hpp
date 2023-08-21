
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

void dequeueBNFRight(quint &bnf_que, v2int &bnf_right)
{
    vint ans = {};
    // printf("dequeueBNFRight que %ld\n", bnf_que.size());
    int size = bnf_que.size();

    for (int i = 0; i < size; i++)
    {
        int e = bnf_que.front();
        ans.push_back(e);
        bnf_que.pop();
    }

    // printf("dequeueBNFRight ans %ld\n", ans.size());

    bnf_right.push_back(ans);
}

v2int generateBNFRight(BNFToken &bnf_token_p, BNFSymbol &bnf_symbol_p, RetrieveSymbol &nonterminal_symbol_left, int current_left)
{
    quint bnf_que;
    v2int bnf_right;

    int begin = nonterminal_symbol_left.array[current_left];
    int end = current_left == nonterminal_symbol_left.len - 1 ? bnf_token_p.token_len : nonterminal_symbol_left.array[current_left + 1];

    for (int current = begin + 1; current < end; current++)
    {
        switch (bnf_token_p.token_label_array[current])
        {
        case is_id_VerticalLine:
        {
            dequeueBNFRight(bnf_que, bnf_right);

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
            bnf_que.push(current);
            break;
        }
        }
    }
    dequeueBNFRight(bnf_que, bnf_right);
    return bnf_right;
}

#endif