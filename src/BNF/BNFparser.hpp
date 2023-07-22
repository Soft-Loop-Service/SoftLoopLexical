
#ifndef __BNFPARSER
#define __BNFPARSER

#include "./../definition.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

int parseBnf(char *source_code, char **token_string)
{
    int i_s = 0;
    int state = 0;
    int loop = 0;
    for (;;)
    {
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

        char *bnf_symbol = "_=+-*/!%&~|<>?:.#^()";

        if (strchr("|+*[]", source_code[i_s]) != 0)
        { // or記号
            token_search_len = 1;
        }
        else if (strncmp(&source_code[i_s], "::=", 3) == 0)
        {
            token_search_len = 3;
        }

        else if (isAlphabetOrNumber(source_code[i_s]) || strchr(bnf_symbol, source_code[i_s]) != 0)
        {
            printf("アルファベット %c\n", source_code[i_s]);
            while (isAlphabetOrNumber(source_code[i_s + token_search_len]) || strchr(bnf_symbol, source_code[i_s + token_search_len]) != 0)
            {
                if (source_code[i_s + token_search_len] == 0) // ファイル終端
                {
                    break;
                }

                // char *c = strchr(bnf_symbol, source_code[i_s + token_search_len]);
                printf("アルファベット while : %c %d\n", source_code[i_s + token_search_len], i_s + token_search_len);
                token_search_len++;
            }
        }
        else
        {
            printf("syntax error : %.10s\n", &source_code[i_s]);
            exit(1);
        }

        char *new_token = (char *)calloc(100, 1);
        strncpy(new_token, &source_code[i_s], token_search_len);
        token_string[loop] = new_token;

        i_s += token_search_len;
        loop++;
        /* code */
    }

    return loop;
}

#endif
