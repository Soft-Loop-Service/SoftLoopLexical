// 字句解析定義ファイル

#ifndef __LexicalAnalysis
#define __LexicalAnalysis

#include "./../definition.hpp"
#include "./../debug.hpp"

vstring getTokenString(char **token_string, int *token_progression)
{
    vstring token_string_vector;
    for (int i = 0; i < token_progression_arr_size; i++)
    {
        int p = token_progression[i];

        if (p == -1)
        {
            break;
        }

        char *token = token_string[p];
        string token_string = string(token);
        token_string_vector.push_back(token_string);
    }
    return token_string_vector;
}

int getToken(char *source_text, char **token_string, int *token_progression, int token_search_len, int &token_string_endline, int &token_progression_endline)
{

    for (int i = 0; i < token_string_endline; i++)
    {
        // printf("token_search_len : %s %d\n", token_string[i], token_search_len);
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
    strncpy(new_token, source_text, token_search_len);
    token_string[token_string_endline] = new_token;

    token_progression[token_progression_endline] = token_string_endline;
    token_string_endline++;
    token_progression_endline++;
    return token_string_endline;
}
// スキャナ
void lexSyntax(char *source_code, char **token_string, int *token_progression)
{
    // source_codeとtokenのポインタを得る

    int token_string_endline = 0;
    int token_progression_endline = 0;

    for (int i = 0; i < token_progression_arr_size; i++)
    {
        token_progression[i] = -1;
    }

    int i_s = 0; // 現在地点
    for (;;)
    { // 終了コードまで
        // return;
        int token_search_len = 0;

        if (source_code[i_s] == 0) // ファイル終端
        {
            break;
        }

        if (source_code[i_s] == ' ' || source_code[i_s] == '\t' || source_code[i_s] == '\n' || source_code[i_s] == '\r')
        { // スペース、タブ、改行.
            i_s++;
            continue;
        }
        if (strchr("(){}[];,", source_code[i_s]) != 0)
        { // 1文字記号.
            token_search_len = 1;
        }
        else if (isAlphabetOrNumber(source_code[i_s]))
        {
            while (isAlphabetOrNumber(source_code[i_s + token_search_len]))
            {
                token_search_len++;
            }
        }
        else if (strchr("=+-*/!%&~|<>?:.#_", source_code[i_s]) != 0)
        { // 現在文字が普通の記号.
            while (strchr("=+-*/!%&~|<>?:.#_", source_code[i_s + token_search_len]) != 0 && source_code[i_s + token_search_len] != 0)
                token_search_len++;
        }
        else if (strchr("\'\"\\", source_code[i_s]) != 0)
        { // 特殊1文字記号
            token_search_len = 1;
        }
        else
        {
            printf("syntax error : %.10s\n", &source_code[i_s]);
            exit(1);
        }
        printf("token_search_len %d\n", token_search_len);
        int current_token_id = getToken(&source_code[i_s], token_string, token_progression, token_search_len, token_string_endline, token_progression_endline);
        // printf("current_token_id : %d", current_token_id);
        i_s += token_search_len;
    }

    // output_token_string(token_string, token_string_arr_size);
    // output_token_progression(token_string, token_progression, token_progression_endline);
}

#endif