#ifndef __LexicalAnalysis
#define __LexicalAnalysis

#include "definition.hpp"

void lexSyntax(uchar source_code, vuchar token)
{
}
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

int getToken(char *source_code_current, vchar *token, vchar *variable, int token_search_len)
{
    // for (int i = 0; i < token->size(); i++)
    // {
    //     int result = strncmp((char const *)source_code_current, (char const *)&token[i], token_search_len) == 0;
    //     // 存在するか否か

    //     if (result)
    //     {
    //         variable->push_back(i);
    //         return i;
    //     }
    // }

    // ここから登録
    char *new_token;
    strncpy(new_token, source_code_current, token_search_len);
    // token->push_back(*new_token); // tokenを新規登録する
    // variable->push_back(token->size() - 1);
    return token->size() - 1;
}

void lexSyntax(char *source_code, vchar *token, vchar *variable)
{
    // source_codeとtokenのポインタを得る

    

    int i_s = 0; // 現在地点
    for (;;)
    { // 終了コードまで
        printf("current_text : %d , %c\n",i_s, source_code[i_s]);
        // return;
        int token_search_len = 0;

        if (source_code[i_s] == 0) // ファイル終端
        {
            return;
        }

        if (source_code[i_s] == ' ' || source_code[i_s] == '\t' || source_code[i_s] == '\n' || source_code[i_s] == '\r')
        { // スペース、タブ、改行.
            i_s ++;
            continue;
        }
        if (strchr("(){}[];,", source_code[i_s]) != 0) {	// 1文字記号.
            token_search_len = 1;
        } 
        else if (isAlphabetOrNumber(source_code[i_s]))
        {
            while (isAlphabetOrNumber(source_code[i_s + token_search_len]))
            {
                token_search_len++;
            }

            printf("アルファベット\n");
        }
        else if (strchr("=+-*/!%&~|<>?:.#", source_code[i_s]) != 0)
        { // 現在文字が普通の記号.
            while (strchr("=+-*/!%&~|<>?:.#", source_code[i_s + token_search_len]) != 0 && source_code[i_s + token_search_len] != 0)
                token_search_len++;
            printf("記号\n");
        }
        else
        {
            printf("syntax error : %.10s\n", &source_code[i_s]);
            exit(1);
        }

        

        int current_token_id = getToken(&source_code[i_s], token, variable, token_search_len);
        printf("current_token_id : %d", current_token_id);
        i_s++;
    }
}

#endif