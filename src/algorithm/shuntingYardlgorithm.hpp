
#ifndef __BNFPARSER
#define __BNFPARSER

#include "./../definition.hpp"
#include "./BNFdefinition.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

// Shunting-yard algorithm

// 構文に対して操車場アルゴリズムを適応する
// 出力は逆ポーランド記法となる

int shuntingYardAlgorithm(char **token_string, int *token_label, int token_len)
{
}
#endif
