
#ifndef __BNFRST
#define __BNFRST

#include "./../definition.hpp"
#include "./bnf_definition.hpp"
#include "./bnf_struct.hpp"
#include "./../symbol.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
/// retrieveSymbolTable
/// SymbolTableから欲しい種別だけ抽出する
/// @param target_id       抽出対象
/// @param retrieve_label  抽出したラベル
/// @return                抽出したラベルデータの長さ　
int retrieveSymbolTable(BNFToken &bnf_token_p, BNFSymbol &bnf_symbol_p, RetrieveSymbol &retrieve_symbol, int target_id)
{
    printf("retrieveSymbolTable B %d\n", bnf_symbol_p.unique_symbol_len);
    int count = 0;
    for (int i = 0; i < bnf_token_p.token_len; i++)
    {
        int c_sta = bnf_symbol_p.symbol_table_array[i];
        if (c_sta < 0)
        {
            continue;
        }

        int ctl = bnf_token_p.token_label_array[i];
        printf("%d %d %d %s\n", ctl, target_id, i, get_bnf_arr(bnf_token_p, i));

        if (ctl == target_id)
        {
            count++;
        }
    }

    retrieve_symbol.array = (int *)calloc(count, sizeof(int));
    int len = 0;

    for (int i = 0; i < bnf_token_p.token_len; i++)
    {
        int c_sta = bnf_symbol_p.symbol_table_array[i];
        if (c_sta < 0)
        {
            continue;
        }

        int ctl = bnf_token_p.token_label_array[i];
        if (ctl == target_id)
        {
            retrieve_symbol.array[len] = i;
            printf("retrieveSymbolTable B : %d %d %d %d %d %s\n", retrieve_symbol.array[len], i, target_id, len, count, get_bnf_arr(bnf_token_p, i));
            len++;
        }
    }
    // resizeNull(retrieve_label , len);
    retrieve_symbol.len = len;
    return len;
}

/// retrieveSymbolTable
/// SymbolTableから欲しい種別だけ抽出する
/// @param target_id       抽出対象
/// @param retrieve_label  抽出したラベル
/// @return                抽出したラベルデータの長さ　
int retrieveSymbolTable(BNFToken &bnf_token_p, RetrieveSymbol &retrieve_symbol, int target_id)
{

    int count = 0;

    for (int i = 0; i < bnf_token_p.token_len; i++)
    {
        int ctl = bnf_token_p.token_label_array[i];

        if (ctl == target_id)
        {
            count++;
        }
    }

    retrieve_symbol.array = (int *)calloc(count, sizeof(int));
    int len = 0;

    for (int i = 0; i < bnf_token_p.token_len; i++)
    {
        int ctl = bnf_token_p.token_label_array[i];

        if (ctl == target_id)
        {
            retrieve_symbol.array[len] = i;
            printf("retrieveSymbolTable A : %d %d %d\n", retrieve_symbol.array[len], i, bnf_token_p.token_len);
            len++;
        }
    }
    // resizeNull(retrieve_label , len);
    retrieve_symbol.len = len;
    return len;
}

#endif