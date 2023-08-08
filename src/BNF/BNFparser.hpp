
#ifndef __BNFPARSER
#define __BNFPARSER

#include "./../definition.hpp"
#include "./BNFdefinition.hpp"
#include "./BNFstruct.hpp"
#include "./../symbol.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

// EBNF記法に沿う

/*
labelingBnf
tokenそれぞれの役割を明確化する
token_string : 入力token
token_label  : 役割探索結果
token_len    : 読み込む入力tokenの量
nonterminal_symbol_len   : 役割探索の結果、非末端記号の数
terminal_symbol_len   : 役割探索の結果、末端記号の数
*/
int labelingBnf(BNFToken &bnf_token_p)
{
    printf("labelingBnf %d\n",bnf_token_p.token_len);
    
    int i = 0;
    while (i < bnf_token_p.token_len)
    {

        char *cts = bnf_token_p.token_string[i];

        printf("llb while %d %s\n", i, &*cts);

        // current_token_string

        bool hasLess = strchr(cts, '<') != 0;
        bool hasGreater = strchr(cts, '>') != 0;

        bool isNonterminalSymbol = hasLess && hasGreater;
        //<>の記号を持っていたら、非終端記号と認識できる。

        bool isDefinitionSymbol = strncmp(cts, "::=", 3) == 0;
        bool isDefinitionSymbolNext = false;
        if (i + 1 < bnf_token_p.token_len)
        {
            isDefinitionSymbolNext = strncmp(bnf_token_p.token_string[i + 1], "::=", 3) == 0;
            // その次のトークンが定義記号か調べることによって、左辺なのか右辺なのかを確認する
        }

        bool isVerticalLine = strncmp(cts, "|", 3) == 0;

        bool isEscapeSingle = strncmp(cts, "\'", 1) == 0;
        bool isEscapeDouble = strncmp(cts, "\"", 1) == 0;

        bool hasEscapeSingle = false;
        bool hasEscapeDouble = false;
        if (i + 2 < bnf_token_p.token_len)
        {
            hasEscapeSingle = isEscapeSingle && strncmp(bnf_token_p.token_string[i + 2], "\'", 1) == 0;
            hasEscapeDouble = isEscapeDouble && strncmp(bnf_token_p.token_string[i + 2], "\"", 1) == 0;
        }

        bool isParenthesisLeft = strchr("(", *cts) != 0;
        bool isParenthesisRight = strchr(")", *cts) != 0;
        bool isBracketsLeft = strchr("[", *cts) != 0;
        bool isBracketsRight = strchr("]", *cts) != 0;
        bool isCurlyBracketsLeft = strchr("{", *cts) != 0;
        bool isCurlyBracketsRight = strchr("}", *cts) != 0;

        bool isAddition = strchr("+", *cts) != 0;
        bool isSubtraction = strchr("-", *cts) != 0;
        bool isMultiplication = strchr("*", *cts) != 0;
        bool isDivision = strchr("/", *cts) != 0;
        bool isEqual = strchr("=", *cts) != 0;

        int work = 1;

        if (isNonterminalSymbol)
        {
            bnf_token_p.nonterminal_symbol_len++;
            if (isDefinitionSymbolNext)
            {
                bnf_token_p.token_label[i] = is_id_NonterminalSymbolLeft;
            }
            else
            {
                bnf_token_p.token_label[i] = is_id_NonterminalSymbolRight;
            }
        }
        else if (isDefinitionSymbol)
        {
            bnf_token_p.token_label[i] = is_id_DefinitionSymbol;
        }

        else if (hasEscapeSingle)
        {
            bnf_token_p.terminal_symbol_len++;
            bnf_token_p.token_label[i] = is_id_SingleQuotationLeft;
            bnf_token_p.token_label[i + 1] = is_id_TerminalSymbol;
            bnf_token_p.token_label[i + 2] = is_id_SingleQuotationRight;
            work = 3;
        }
        else if (hasEscapeDouble)
        {
            bnf_token_p.terminal_symbol_len++;
            bnf_token_p.token_label[i] = is_id_DoubleQuotationLeft;
            bnf_token_p.token_label[i + 1] = is_id_TerminalSymbol;
            bnf_token_p.token_label[i + 2] = is_id_DoubleQuotationRight;
            work = 3;
        }
        else if (isEscapeSingle)
        {
            bnf_token_p.token_label[i] = is_id_SingleQuotation;
        }
        else if (isEscapeDouble)
        {
            bnf_token_p.token_label[i] = is_id_DoubleQuotation;
        }
        else if (isVerticalLine)
        {
            bnf_token_p.token_label[i] = is_id_VerticalLine;
        }
        else if (isAddition)
        {
            bnf_token_p.token_label[i] = is_id_Addition;
        }
        else if (isSubtraction)
        {
            bnf_token_p.token_label[i] = is_id_Subtraction;
        }
        else if (isMultiplication)
        {
            bnf_token_p.token_label[i] = is_id_Multiplication;
        }
        else if (isDivision)
        {
            bnf_token_p.token_label[i] = is_id_Division;
        }
        else if (isParenthesisLeft)
        {
            bnf_token_p.token_label[i] = is_id_ParenthesisLeft;
        }
        else if (isParenthesisRight)
        {
            bnf_token_p.token_label[i] = is_id_ParenthesisRight;
        }
        else if (isBracketsLeft)
        {
            bnf_token_p.token_label[i] = is_id_BracketLeft;
        }
        else if (isBracketsRight)
        {
            bnf_token_p.token_label[i] = is_id_BracketRight;
        }
        else if (isCurlyBracketsLeft)
        {
            bnf_token_p.token_label[i] = is_id_CurlyBracketLeft;
        }
        else if (isCurlyBracketsRight)
        {
            bnf_token_p.token_label[i] = is_id_CurlyBracketRight;
        }

        else
        {
            bnf_token_p.terminal_symbol_len++;
            bnf_token_p.token_label[i] = is_id_TerminalSymbol;
        }
        i += work;
    }
}

int parseBnf(char *source_code, BNFToken &bnf_token_p)
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

        char *bnf_symbol = "_=+-*/!%&~<>?:.#^|";
        char *bnf_val_symbol = "<>_";

        if (strncmp(&source_code[i_s], "::=", 3) == 0)
        {
            token_search_len = 3;
        }
        else if (isAlphabetOrNumber(source_code[i_s]) || strchr(bnf_val_symbol, source_code[i_s]) != 0)
        {
            while (isAlphabetOrNumber(source_code[i_s + token_search_len]) || strchr(bnf_val_symbol, source_code[i_s + token_search_len]) != 0)
            {
                if (source_code[i_s + token_search_len] == 0) // ファイル終端
                {
                    break;
                }

                token_search_len++;
            }
        }

        else if (strchr(bnf_symbol, source_code[i_s]) != 0)
        {
            while (strchr(bnf_symbol, source_code[i_s + token_search_len]) != 0)
            {
                if (source_code[i_s + token_search_len] == 0) // ファイル終端
                {
                    break;
                }

                token_search_len++;
            }
        }

        else if (strchr("+*[]()\'\"", source_code[i_s]) != 0)
        { // or記号
            token_search_len = 1;
        }
        else
        {
            printf("syntax error : %.10s\n", &source_code[i_s]);
            exit(1);
        }

        char* new_token = (char *)realloc(bnf_token_p.token_string[loop],bnf_token_len);

        strncpy(new_token, &source_code[i_s], token_search_len);
        bnf_token_p.token_string[loop] = new_token;

        printf("parseBnf %d %s\n",token_search_len,bnf_token_p.token_string[loop]);

        i_s += token_search_len;
        loop++;
        /* code */
    }

    return loop;
}

#endif
