
#ifndef __BNFPARSER
#define __BNFPARSER

#include "./../definition.hpp"
#include "./BNFdefinition.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

// 記号の読み方
// https://www602.math.ryukoku.ac.jp/Prog1/charnames.html

int labelingBnf(char **token_string, int *token_label, int token_len)
{
    int i = 0;
    while (i < token_len)
    {

        char *cts = token_string[i];

        printf("llb while %d %s\n", i, &*cts);

        // current_token_string

        bool hasLess = strchr(cts, '<') != 0;
        bool hasGreater = strchr(cts, '>') != 0;

        bool isNonterminalSymbol = hasLess && hasGreater;
        //<>の記号を持っていたら、非終端記号と認識できる。

        bool isDefinitionSymbol = strncmp(cts, "::=", 3) == 0;

        bool isVerticalLine = strncmp(cts, "|", 3) == 0;

        bool hasEscapeSingle = false;
        bool hasEscapeDouble = false;
        if (i + 2 < token_len)
        {
            hasEscapeSingle = strncmp(cts, "\'", 1) == 0 && strncmp(token_string[i + 2], "\'", 1) == 0;
            hasEscapeDouble = strncmp(cts, "\"", 1) == 0 && strncmp(token_string[i + 2], "\"", 1) == 0;
        }

        bool isParenthesisLeft = strchr("(", *cts) != 0;
        bool isParenthesisRight = strchr(")", *cts) != 0;
        bool isBracketsLeft = strchr("[", *cts) != 0;
        bool isBracketsRight = strchr("]", *cts) != 0;

        int work = 1;

        if (isNonterminalSymbol)
        {
            token_label[i] = is_id_NonterminalSymbol;
        }
        else if (isDefinitionSymbol)
        {
            token_label[i] = is_id_DefinitionSymbol;
        }
        else if (isVerticalLine)
        {
            token_label[i] = is_id_VerticalLine;
        }
        else if (hasEscapeSingle)
        {

            token_label[i] = is_id_SingleQuotation;
            token_label[i + 1] = is_id_Token;
            token_label[i + 2] = is_id_SingleQuotation;
            work = 3;
        }
        else if (hasEscapeDouble)
        {

            token_label[i] = is_id_DoubleQuotation;
            token_label[i + 1] = is_id_Token;
            token_label[i + 2] = is_id_DoubleQuotation;
            work = 3;
        }
        else if (isParenthesisLeft)
        {
            token_label[i] = is_id_ParenthesisLeft;
        }
        else if (isParenthesisRight)
        {
            token_label[i] = is_id_ParenthesisRight;
        }
        else if (isBracketsLeft)
        {
            token_label[i] = is_id_BracketLeft;
        }
        else if (isBracketsRight)
        {
            token_label[i] = is_id_BracketRight;
        }
        else
        {
            token_label[i] = is_id_Token;
        }
        i += work;
    }
}

int parseBnf(char *source_code, char **token_string)
{
    int i_s = 0;
    int state = 0;
    int loop = 0;
    int tc = 100; // 一つのtokenの長さ
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

        char *bnf_symbol = "_=+-*/!%&~<>?:.#^";

        if (strchr("|+*[]()\'\"", source_code[i_s]) != 0)
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
                    printf("アルファベット探知終了");
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

        char *new_token = (char *)calloc(tc, 1);
        strncpy(new_token, &source_code[i_s], token_search_len);
        token_string[loop] = new_token;

        i_s += token_search_len;
        loop++;
        /* code */
    }

    return loop;
}

#endif
