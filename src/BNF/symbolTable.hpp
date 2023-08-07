

#ifndef __BNFGST
#define __BNFGST

#include "./../definition.hpp"
#include "./BNFdefinition.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

/*
SymbolTable
非末端記号と末端記号を整理したもの
*/

/*
insertSymbolTable
token_stringとsymbol_stringの紐付け。1次元配列(=string)のポインタをもらう
新規挿入する。
*/
int insertSymbolTable(char *current_token_string, char **symbol_string, int symbol_len)
{
    // 格納されていないところを探す

    int index = 0;

    for (int i = 0; i < symbol_len; i++)
    {
        printf("istl : %s\n" , (&symbol_string[i])[0]);
        if ((&symbol_string[i])[0] == 0)
        {
            break;
        }

        return -1;
    }

    symbol_string[index] = (char *)calloc(bnf_token_len, 1);
    // printf("isto  a: %d %s %s %ld\n" , index,symbol_string[index],current_token_string);
    strncpy(symbol_string[index], current_token_string, bnf_token_len);
    // printf("isto b: %d %s %s %ld\n" , index,symbol_string[index],current_token_string);
}

/*
applySymbolTable
symbol_tableに登録する
*/
void applySymbolTable(int *current_symbol_table, int search)
{
    *current_symbol_table = search;
}

/*
searchSymbolTable
すでに探索済みではないかどうかを調べる。
線形探索を用いる。
*/
int searchSymbolTable(char *current_token_string, char **symbol_string, int symbol_len)
{
    for (int i = 0; i < symbol_len; i++)
    {
        printf("sst %d: %s %10s\n", i,current_token_string ,symbol_string[i] );
        // if (strncmp(current_token_string, symbol_string[i], bnf_token_len) == 0)
        // {
        //     return i;
        // }
    }

    return -1;
}

/*
generateSymbolTable
非終端記号と終端記号の関係をまとめる
token_string    : 入力token
symbol_string   : 出力symbol
symbol_table    : token_string と symbol_stringの関連付け。 index番号(token_string) : 要素(symbol_string)の格納位置
token_label     : 入力token 役割
token_len       : 読み込む入力tokenの量
symbol_len      : 非末端記号と末端記号の合計
*/
void generateSymbolTable(char **token_string, char **symbol_string, int *symbol_table, int token_len, int *token_label, int symbol_len)
{

    int csi = 0; // symbol_stringで次に挿入する場所
    for (int si = 0; si < token_len; si++)
    {
        int ctl = token_label[si];
        switch (ctl)
        {
        case is_id_NonterminalSymbolLeft:  // 111  左辺定義 非末端記号
        case is_id_NonterminalSymbolRight: // 112  右辺定義 非末端記号
        case is_id_TerminalSymbol:         // 140 末端記号(TerminalSymbol)

            int s = searchSymbolTable(token_string[si], symbol_string, symbol_len);

            if (s == -1)
            {
            int n = insertSymbolTable(token_string[si], symbol_string, symbol_len);
                if (n > 0)
                {
                    applySymbolTable(&symbol_table[si], n);
                }
            }
            else
            {
                applySymbolTable(&symbol_table[si], s);
            }

            break;

        // default:
        //     break;
        }
    }
}

#endif
