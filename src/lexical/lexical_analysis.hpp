// 字句解析定義ファイル

#ifndef __LexicalAnalysis
#define __LexicalAnalysis

#include "./../definition.hpp"
#include "./../debug.hpp"
#include "./../symbol.hpp"

// vstring getTokenString(char **token_string, int *token_progression)
// {
//     vstring token_string_vector;
//     for (int i = 0; i < token_progression_arr_size; i++)
//     {
//         int p = token_progression[i];

//         if (p == -1)
//         {
//             break;
//         }

//         char *token = token_string[p];
//         string token_string = string(token);
//         token_string_vector.push_back(token_string);
//     }
//     token_string_vector.push_back(DOLLAR);
//     return token_string_vector;
// }

string getToken(char *source_text, int token_search_len)
{

    // printf("%s", source_code_current);

    // ここから登録
    char *new_token = (char *)calloc(code_token_len, sizeof(char));
    strncpy(new_token, source_text, token_search_len);
    string token_string = string(new_token);

    return token_string;
}
// スキャナ
vector<string> lexSyntax(char *source_code)
{
    // source_codeとtokenのポインタを得る
    vector<string> tokens;
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
        if (strchr("(){}[]{};,", source_code[i_s]) != 0)
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
        string current_token = getToken(&source_code[i_s], token_search_len);
        tokens.push_back(current_token);
        // printf("current_token_id : %d", current_token_id);
        i_s += token_search_len;
    }
    tokens.push_back(DOLLAR);
    return tokens;

    // output_token_string(token_string, token_string_arr_size);
    // output_token_progression(token_string, token_progression, token_progression_endline);
}

#endif