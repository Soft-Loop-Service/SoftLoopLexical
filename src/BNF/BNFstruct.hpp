
#ifndef __BNFSTRUCT
#define __BNFSTRUCT

#include "./../definition.hpp"
#include "./BNFdefinition.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

struct stest{
    int test;
};


/*
BNFToken
token_string    : tokenの一覧
token_label     : tokenの役割
token_len       : tokenの数
nonterminal_symbol_len : 非末端記号の数
terminal_symbol_len    : 末端記号の数
*/
struct BNFToken
{
    char **token_string_array;
    int *token_label_array;
    int token_len;
    int nonterminal_symbol_len;
    int terminal_symbol_len;
};

/*
symbol_table        : token_string と symbol_stringの関連付け。 index番号(token_string) : 要素(symbol_string)の格納位置
symbol_string       : ユニークなシンボル一覧
unique_symbol_len   : ユニークなシンボルの数
symbol_len          : 述べシンボルの数
*/
struct BNFSymbol
{
    int *symbol_table_array;
    char **symbol_string_array;
    int *nonterminal_symbol_array;
    int unique_symbol_len;
    int symbol_len;
};

#endif