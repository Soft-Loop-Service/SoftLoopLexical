
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

char *get_bnf_arr(BNFToken &bnf_token_p, int number)
{
    return bnf_token_p.token_string_array[number];
}

#endif
