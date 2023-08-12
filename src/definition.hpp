#ifndef __Definition
#define __Definition

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>

typedef unsigned char uchar;
typedef std::vector<char> vchar;
typedef std::vector<unsigned char> vuchar;
typedef std::vector<std::string> vstring;
typedef std::vector<int> vint;
typedef std::vector<std::vector<int> > v2int;
typedef std::stack<int> sint;
typedef std::queue<int> quint;
using namespace std;

const int token_string_arr_size = 10000;      // tokenの最大数
const int token_progression_arr_size = 10000; // 変数の最大数
// const int token_size = 50;           // tokenの最大文字数
// const int variable_size = 50;        // variableの最大文字数


#define code_token_len 50 //BNFトークンの最大長
#define code_token_arr_len 500


// 最大ソースコード容量 1MBまで対応

const int source_code_size = 1000000;

/*
resizeCharNull 
第一引数    : 対象となる配列
第二引数    : 変更したい長さ
*/
int resizeNull(int *data , int len){
    int size = -1;

    for (int i = 0 ; i < len;i++){
        
        if((data[i]) ==  0){
            size = i;
            break;
        }
    }

    int* newdata = (int *)realloc(data,size);

    if (newdata == NULL){
        printf("resize int null error : 再配置できません 再配置要求 %d -> %d\n",len,size);
        return len;
    }
    data = newdata;

    printf("resize int null ok : resize %d -> %d sizeof %ld\n",len,size,sizeof(char**));
    return size;

}

int resizeNull(char ** str, int len){

    int size = -1;

    for (int i = 0 ; i < len;i++){
        
        if((str[i][0]) ==  '\0'){
            size = i;
            break;
        }
    }

    char** newstr = (char **)realloc(str,size);

    if (newstr == NULL){
        printf("resize char null error : 再配置できません 再配置要求 %d -> %d\n",len,size);
        return len;
    }

    str = newstr;

    printf("resize char null ok : resize %d -> %d sizeof %ld\n",len,size,sizeof(char**));


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
    char *new_token = new char[100];
    // strncpy(new_token, source_text, token_search_len);
    token_string[token_string_endline] = new_token;

    token_progression[token_progression_endline] = token_string_endline;
    token_string_endline++;
    token_progression_endline++;
    return token_string_endline;
}
#endif