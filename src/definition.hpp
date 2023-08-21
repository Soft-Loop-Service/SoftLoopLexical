#ifndef __Definition
#define __Definition

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <map>

typedef unsigned char uchar;
typedef std::vector<char> vchar;
typedef std::vector<unsigned char> vuchar;
typedef std::vector<std::string> vstring;
typedef std::vector<int> vint;
typedef std::vector<std::vector<int>> v2int;
typedef std::vector<std::vector<std::vector<int>>> v3int;
typedef std::vector<std::vector<std::vector<std::vector<int>>>> v4int;
typedef std::stack<int> sint;
typedef std::queue<int> quint;
typedef std::vector<std::queue<int>> vquint;
typedef std::map<std::string, int> mp_s_i;       // ローカル変数として、mp を生成
typedef std::map<std::string, v2int> mp_s_v2int; // ローカル変数として、mp を生成

using namespace std;

const int token_string_arr_size = 10000;      // tokenの最大数
const int token_progression_arr_size = 10000; // 変数の最大数
// const int token_size = 50;           // tokenの最大文字数
// const int variable_size = 50;        // variableの最大文字数

#define code_token_len 50 // BNFトークンの最大長
#define code_token_arr_len 500

// 最大ソースコード容量 1MBまで対応

const int source_code_size = 1000000;

bool getTwoDimensionalArray(int **data, int one, int two)
{
    data = (int **)calloc(one, sizeof(int *));
    if (data == NULL)
    {
        return false;
    }

    for (int i = 0; i < one; i++)
    {
        data[i] = (int *)calloc(two, sizeof(int));
        if (data[i] == NULL)
        {
            return false;
        }
    }

    for (int h = 0; h < one; h++)
    {
        for (int w = 0; w < two; w++)
        {
            data[h][w] = 0;
        }
    }

    return true;
}

/*
resizeCharNull
第一引数    : 対象となる配列
第二引数    : 変更したい長さ
*/
int resizeArray(int *data, int len)
{
    int size = len * sizeof(int);

    // int *newdata = (int *)realloc(data, size);
    // printf("resizeArray %d\n", newdata[0]);
    // if (newdata == NULL)
    // {
    //     printf("resize int null error : 再配置できません 再配置要求 %d -> %d\n", len, size);
    //     return len;
    // }

    int *newdata = (int *)calloc(len, sizeof(int));
    memcpy(newdata, data, size);
    data = newdata;
    printf("resizeArray %d\n", data[0]);

    printf("resize int null ok : resize %d -> %d sizeof %ld\n", len, size, sizeof(int));
    return size;
}

int resizeArray(char **str, int len)
{

    int size = len * sizeof(char *);

    for (int i = 0; i < len; i++)
    {

        if ((str[i][0]) == '\0')
        {
            size = i;
            break;
        }
    }

    char **newstr = (char **)realloc(str, size);

    if (newstr == NULL)
    {
        printf("resize char null error : 再配置できません 再配置要求 %d -> %d\n", len, size);
        return len;
    }

    str = newstr;

    printf("resize char null ok : resize %d -> %d sizeof %ld\n", len, size, sizeof(char **));

    return size;
}

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

int getToken(char *source_text, char **token_string, int *token_progression, int token_search_len, int &token_string_endline, int &token_progression_endline)
{

    for (int i = 0; i < token_string_endline; i++)
    {
        printf("token_search_len : %s %d\n", token_string[i], token_search_len);
        bool result = strncmp(source_text, token_string[i], token_search_len) == 0;
        // 存在するか否か

        if (result)
        {
            token_progression[token_progression_endline] = i;
            token_progression_endline++;
            return i;
        }
    }

    // printf("%s", source_code_current);

    // ここから登録
    char *new_token = (char *)calloc(code_token_len, sizeof(char));
    // strncpy(new_token, source_text, token_search_len);
    token_string[token_string_endline] = new_token;

    token_progression[token_progression_endline] = token_string_endline;
    token_string_endline++;
    token_progression_endline++;
    return token_string_endline;
}
#endif