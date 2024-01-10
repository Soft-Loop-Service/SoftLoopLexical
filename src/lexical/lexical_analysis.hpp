// 字句解析定義ファイル

#ifndef __LexicalAnalysis
#define __LexicalAnalysis

#include "./../definition.hpp"
#include "./../debug.hpp"
#include "./../symbol.hpp"

#include "./lexical_analysis_definition.hpp"

string getToken(char *source_text, int token_search_len)
{
    // ここから登録
    char *new_token = (char *)calloc(code_token_len, sizeof(char));
    strncpy(new_token, source_text, token_search_len);
    string token_string = string(new_token);

    return token_string;
}
// スキャナ
vLexicalToken lexSyntax(char *source_code)
{
    // source_codeとtokenのポインタを得る
    vLexicalToken lexical_token = {};

    int i_s = 0; // 現在地点
    for (;;)

    { // 終了コードまで
        // return;

        string token_type = "\t";
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
        else if (isNumber(source_code[i_s]))
        {
            token_type = "NUM";
            while (isNumber(source_code[i_s + token_search_len]))
            {
                token_search_len++;
            }
        }
        else if (isAlphabetOrNumber(source_code[i_s]))
        {
            token_type = "TEXT";
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

        if (token_type == "\t")
        {
            token_type = current_token;
        }

        struct lexicalToken ts = {current_token, token_type};

        lexical_token.push_back(ts);
        // printf("current_token_id : %d", current_token_id);
        i_s += token_search_len;
    }

    struct lexicalToken tsd = {DOLLAR, DOLLAR};
    lexical_token.push_back(tsd);
    return lexical_token;

    // output_token_string(token_string, token_string_arr_size);
    // output_token_progression(token_string, token_progression, token_progression_endline);
}

#endif