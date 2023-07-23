// 字句解析定義ファイル

#ifndef __LexicalAnalysis
#define __LexicalAnalysis

#include "./../definition.hpp"
#include "./../debug.hpp"

// スキャナ
void lexSyntax(char *source_code, char **token_string, int *token_progression)
{
    // source_codeとtokenのポインタを得る

    int token_string_endline = 0;
    int token_progression_endline = 0;

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

        int current_token_id = getToken(&source_code[i_s], token_string, token_progression, token_search_len, token_string_endline, token_progression_endline);
        // printf("current_token_id : %d", current_token_id);
        i_s += token_search_len;
    }

    output_token_string(token_string, token_progression_arr_size);
    output_token_progression(token_string, token_progression, token_progression_endline);
}

#endif