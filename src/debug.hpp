
#ifndef __Debug
#define __Debug
#include "definition.hpp"

void output_token_string(char **token_string, int line)
{
    for (int i = 0; i < line; i++)
    {
        printf("output_token_string :%d %s\n", i, *&token_string[i]);
    }
}
void output_token_progression(char **token_string, int *token_progression, int line)
{
    for (int i = 0; i < line; i++)
    {
        // printf("%s\n", &token[variable[i]]);
        printf("output_token_progression a : %d\n", token_progression[i]);
    }
    for (int i = 0; i < line; i++)
    {
        // printf("%s\n", &token[variable[i]]);
        printf("output_token_progression b : %s\n", *&token_string[token_progression[i]]);
    }
}

int output_labeling_bnf(char **token_string, int *token_label, int token_len)
{
    for (int i = 0; i < token_len; i++)
    {
        // printf("%s\n", &token[variable[i]]);
        printf("olb %d: %25s %d\n", token_len, token_string[i], token_label[i]);
    }
}

/*
token_string    : 入力token
symbol_string   : 出力symbol
symbol_table    : token_string と symbol_stringの関連付け。 index番号(token_string) : 要素(symbol_string)の格納位置
token_label     : 入力token 役割
token_len       : 読み込む入力tokenの量
symbol_len      : 非末端記号と末端記号の合計
*/
int output_bnf_tablef(char **token_string, char **symbol_string, int *symbol_table, int token_len, int *token_label, int symbol_len)
{
    for (int i = 0; i < token_len; i++)
    {
        // printf("%s\n", &token[variable[i]]);
        printf("obt %3d: %25s %10s %d\n", i, token_string[i], symbol_string[i] , symbol_table[i]);
    }

    // for (int i = 0; i < symbol_len; i++){
    //     printf("obt - 2 : ")
    // }
}

#endif