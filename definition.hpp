#ifndef __Definition
#define __Definition

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

typedef unsigned char uchar;
typedef std::vector<char> vchar;
typedef std::vector<unsigned char> vuchar;
using namespace std;

const int token_string_arr_size = 10000;      // tokenの最大数
const int token_progression_arr_size = 10000; // 変数の最大数
// const int token_size = 50;           // tokenの最大文字数
// const int variable_size = 50;        // variableの最大文字数
const int source_code_size = 100000; // 読み込むソースコードの最大文字数

int token_string_endline = 0;
int token_progression_endline = 0;

#endif