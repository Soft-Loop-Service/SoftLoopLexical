
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

    for (int i = 0; i < bnf_que.size(); i++)
    {
        int e = bnf_que.back();
        ans.push_back(e);
        bnf_que.pop();
    }
    bnf_right.push_back(ans);
    printf("dequeueBNFRight %ld\n", bnf_right.size());
}

v2int generateBNFRight(BNFToken &bnf_token_p, BNFSymbol &bnf_symbol_p, RetrieveSymbol &nonterminal_symbol_left, int current_left)
{
    quint bnf_que;
    v2int bnf_right;

    int begin = nonterminal_symbol_left.array[current_left];
    int end = current_left == nonterminal_symbol_left.len - 1 ? bnf_symbol_p.symbol_len : nonterminal_symbol_left.array[current_left + 1];

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
            break;

        default:
        {
        }
            bnf_que.push(current);
            break;
        }
    }
    dequeueBNFRight(bnf_que, bnf_right);

    for (int i = 0; i < bnf_right.size(); i++)
    {
        printf("generateBNFRight %ld %ld ", bnf_right.size(), bnf_right[i].size());
        for (int j = 0; j < bnf_right[i].size(); j++)
        {
            printf("%s ", get_bnf_arr(bnf_token_p, bnf_right[i][j]));
        }
        printf("\n");
    }
}

#endif