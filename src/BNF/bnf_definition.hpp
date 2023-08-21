
#ifndef __BNFDE
#define __BNFDE

#include "./../definition.hpp"
#include "./bnf_struct.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

// 記号の読み方
// https://www602.math.ryukoku.ac.jp/Prog1/charnames.html

#define bnf_token_len 50 // BNFトークンの最大長
#define bnf_token_arr_len 500

void concatenateArrayRetrieveSymbol(RetrieveSymbol &newdata, RetrieveSymbol &data1, RetrieveSymbol &data2)
{
    printf("concatenateArrayRetrieveSymbol a : %d %d\n", data1.len, data2.len);
    for (int i = 0; i < data1.len; i++)
    {
        printf(" %d", data1.array[i]);
    }
    for (int i = 0; i < data2.len; i++)
    {
        printf(" %d", data2.array[i]);
    }
    printf("\n");

    newdata.array = (int *)calloc(data1.len + data2.len,sizeof(int));
    
    newdata.len = data1.len + data2.len;
    memcpy(newdata.array, data1.array, data1.len * sizeof(int));
    memcpy(newdata.array + data1.len, data2.array, data2.len * sizeof(int));

    for (int i = 0; i < data1.len + data2.len; i++)
    {
        printf(" %d", newdata.array[i]);
    }
    printf("\n");
}

char *get_bnf_arr(BNFToken &bnf_token_p, int number)
{
    return bnf_token_p.token_string_array[number];
}

#endif
