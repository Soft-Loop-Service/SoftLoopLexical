

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
新規挿入する。
*/
void insertSymbolTable(char *current_token_string, char *current_symbol_string)
{
    strncpy(current_symbol_string, current_token_string ,bnf_token_len);
}

/*
searchSymbolTable
すでに探索済みではないかどうかを調べる。
線形探索を用いる。
*/
bool searchSymbolTable(char *current_token_string,  char **symbol_string,int symbol_len)
{

    for (int i = 0 ; i < symbol_len ; i ++){
        strncmp(current_token_string, symbol_string[i], bnf_token_len) == 0;
    }
    
}

/*
generateSymbolTable
非終端記号と終端記号の関係をまとめる
token_string    : 入力token
symbol_table    : token_string と symbol_stringの関連付け。 index番号(token_string) : 要素(symbol_string)の格納位置
symbol_string   : 出力symbol
token_label     : 役割探索結果
token_len       : 読み込む入力tokenの量
nonterminal_symbol_len  : 非末端記号の数
terminal_symbol_len     : 末端記号の数
symbol_len      : 非末端記号と末端記号の合計
*/
void generateSymbolTable(char **token_string, int *symbol_table, char **symbol_string, int token_len, int *token_label, int *nonterminal_symbol_len, int *terminal_symbol_len, int symbol_len)
{

    int csi = 0; // symbol_stringで次に挿入する場所
    for (int si = 0; si < token_len; si++)
    {
        int ctl = token_label[si];
        switch (ctl)
        {
        case is_id_NonterminalSymbolLeft: // 111  左辺定義 非末端記号
        case is_id_NonterminalSymbolRight: // 112  右辺定義 非末端記号
        case is_id_TerminalSymbol: // 140 末端記号(TerminalSymbol)

            if (!(searchSymbolTable(token_string[si] , symbol_string,symbol_len))){
                insertSymbolTable(token_string[si] , symbol_string[si]);
            }

            
            break;

        default:
            break;
        }
    }
}

#endif
