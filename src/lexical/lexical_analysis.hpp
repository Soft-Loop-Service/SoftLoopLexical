// 字句解析定義ファイル

#ifndef __LexicalAnalysis
#define __LexicalAnalysis

#include "./../definition.hpp"
#include "./../debug.hpp"

int getToken(char *source_code_current, char **token_string, int *token_progression, int token_search_len)
{

    for (int i = 0; i < token_string_endline; i++)
    {
        printf("token_search_len : %s %d\n", token_string[i], token_search_len);
        bool result = strncmp(source_code_current, token_string[i], token_search_len) == 0;
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
    strncpy(new_token, source_code_current, token_search_len);
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

    token_string_endline = 0;
    token_progression_endline = 0;

    int i_s = 0; // 現在地点
    for (;;)
    { // 終了コードまで
        printf("current_text : %d , %c\n", i_s, source_code[i_s]);
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
            printf("アルファベット\n");
            while (isAlphabetOrNumber(source_code[i_s + token_search_len]))
            {
                printf("アルファベット while : %c\n", source_code[i_s + token_search_len]);
                token_search_len++;
            }
        }
        else if (strchr("=+-*/!%&~|<>?:.#", source_code[i_s]) != 0)
        { // 現在文字が普通の記号.
            printf("記号\n");
            while (strchr("=+-*/!%&~|<>?:.#", source_code[i_s + token_search_len]) != 0 && source_code[i_s + token_search_len] != 0)
                token_search_len++;
        }
        else
        {
            printf("syntax error : %.10s\n", &source_code[i_s]);
            exit(1);
        }

        printf("sc * * * \n%s\n * * * \n", &source_code[i_s]);

        int current_token_id = getToken(&source_code[i_s], token_string, token_progression, token_search_len);
        // printf("current_token_id : %d", current_token_id);
        i_s += token_search_len;
    }

    output_token_string(token_string, token_progression_arr_size);
    output_token_progression(token_string, token_progression, token_progression_endline);
}

#endif