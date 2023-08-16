
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

/*
retrieveSymbolTable
SymbolTableから欲しい種別だけ抽出する

target_id       : 抽出対象
retrieve_label  : 抽出したラベル
戻り値          : 抽出したラベルデータの長さ　
*/
int retrieveSymbolTable(BNFToken &bnf_token_p, BNFSymbol &bnf_symbol_p, RetrieveSymbol &retrieve_symbol, int target_id)
{

    printf("retrieveSymbolTable %d\n", bnf_symbol_p.symbol_len);

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
            printf("%d %d %d\n", retrieve_symbol.array[len], i, bnf_token_p.token_len);
            len++;
        }
    }
    // resizeNull(retrieve_label , len);
    retrieve_symbol.len = len;
    return len;
}

#endif