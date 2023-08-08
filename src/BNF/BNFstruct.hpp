
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
    int token_label;
};

struct BNFToken
{
    char **token_string;
    int *token_label;
    int token_len;
    int nonterminal_symbol_len;
    int terminal_symbol_len;
};

struct BNFSymbol
{
    int *symbol_table;
    char **symbol_string;
    int unique_symbol_len;
    int symbol_len;
};

#endif