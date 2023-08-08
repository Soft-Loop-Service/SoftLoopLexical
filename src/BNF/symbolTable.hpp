

#ifndef __BNFGST
#define __BNFGST

#include "./../definition.hpp"
#include "./BNFdefinition.hpp"
#include "./BNFstruct.hpp"

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

symbol_stringに存在しなければ、末尾に挿入する。戻り値として挿入した場所を伝える
symbol_stringにすでに存在すれば、存在する場所を戻り値として伝える。

新規挿入する。
*/
int insertSymbolTable(char *current_token_string, char **symbol_string, int symbol_len)
{
    // 格納されていないところを探す

    int index = -1;

    for (int i = 0; i < symbol_len; i++)
    {
        if ((symbol_string[i]) == NULL)
        {
            index = i;
            break;
        }

        if (strncmp(symbol_string[i], current_token_string, bnf_token_len) == 0)
        {
            return i;
        }
    }

    if (index < 0)
    {
        return -1;
    }


    symbol_string[index] = (char *)calloc(bnf_token_len, 1);
    strncpy(symbol_string[index], current_token_string, bnf_token_len);

    return index;
}


/*
generateSymbolTable
非終端記号と終端記号の関係をまとめる。ユニークな非終端記号と終端記号の合計値を返す
token_string    : 入力token
symbol_string   : 出力symbol
symbol_table    : token_string と symbol_stringの関連付け。 index番号(token_string) : 要素(symbol_string)の格納位置
token_label     : 入力token 役割
token_len       : 読み込む入力tokenの量
symbol_len      : 非末端記号と末端記号の合計
*/
int generateSymbolTable(BNFToken &bnf_token_p , BNFSymbol &bnf_symbol_p)
{

    int csi = 0; // symbol_stringで次に挿入する場所
    for (int si = 0; si < bnf_token_p.token_len; si++)
    {
        int ctl = bnf_token_p.token_label[si];
        switch (ctl)
        {
        case is_id_NonterminalSymbolLeft:  // 111  左辺定義 非末端記号
        case is_id_NonterminalSymbolRight: // 112  右辺定義 非末端記号
        case is_id_TerminalSymbol:         // 140 末端記号(TerminalSymbol)

        {
            int n = insertSymbolTable(bnf_token_p.token_string[si], bnf_symbol_p.symbol_string, bnf_symbol_p.symbol_len);
            if (n > 0)
            {
                bnf_symbol_p.symbol_table[si] = n;
            }
        }

        break;

        case is_id_ParenthesisLeft:
        case is_id_BracketLeft:
        case is_id_CurlyBracketLeft:{
            char *temp_name = new char[bnf_token_len];
            snprintf(temp_name,bnf_token_len,"%s_%d","temp",si);
            int n = insertSymbolTable(temp_name, bnf_symbol_p.symbol_string, bnf_symbol_p.symbol_len);
            bnf_symbol_p.symbol_table[si] = n;
            break;
        }

        default:
            bnf_symbol_p.symbol_table[si] = -1;
            break;
        }
    }

    bnf_symbol_p.symbol_len = resizeCharNull(bnf_symbol_p.symbol_string , bnf_symbol_p.symbol_len);
    return bnf_symbol_p.symbol_len;
}

#endif
