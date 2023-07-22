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
typedef std::vector<std::string> vstring;
using namespace std;

const int token_string_arr_size = 10000;      // tokenの最大数
const int token_progression_arr_size = 10000; // 変数の最大数
// const int token_size = 50;           // tokenの最大文字数
// const int variable_size = 50;        // variableの最大文字数

int token_string_endline = 0;
int token_progression_endline = 0;

int source_code_size = 1000000;
// 最大ソースコード容量 1MBまで対応

/* プログラム・ファイルを読み込むための関数 text / filename / size(読み込むサイズ)*/
void loadText(char *text, const char *file_name, int size)
{
    FILE *fp = fopen(file_name, "rb");
    int read_size = fread(text, 1, size - 1, fp);
    printf("read_size : %s %d\n", file_name, read_size);

    fclose(fp);
    text[read_size] = 0; // 終端マーク 別に配列終端でなくてよい
}

// アルファベットであるか探索
int isAlphabetOrNumber(char ch)
{
    if ('A' <= ch && ch <= 'Z')
    {
        return 1;
    }
    if ('a' <= ch && ch <= 'z')
    {
        return 1;
    }
    if ('0' <= ch && ch <= '9')
    {
        return 1;
    }
    return 0;
}
#endif