#ifndef Lexical
#include <vector>
typedef unsigned char *uchar;

int isAlphabetOrNumber(char ch)
{
    if ('A' <= ch && ch <= 'Z')
    {
        return 1;
    }
    if ('a' <= ch && ch <= 'a')
    {
        return 1;
    }
    if ('0' <= ch && ch <= '9')
    {
        return 1;
    }
    return 0;
}

void getToken(uchar source_code_current, int token_len)
{
    return;
}

void lexSyntax(uchar source_code, std::vector<uchar> *token)
{

    int i_s = 0; // 現在地点
    for (;;)
    { // 終了コードまで
        int token_search_len = 0;
        if (source_code[i_s] == 0) // ファイル終端
        {
            return;
        }
        if (source_code[i_s] == ' ' || source_code[i_s] == '\t' || source_code[i_s] == '\n' || source_code[i_s] == '\r')
        { // スペース、タブ、改行.
            continue;
        }
        else if (isAlphabetOrNumber(source_code[i_s]))
        {
            while (isAlphabetOrNumber(source_code[i_s + token_search_len]))
            {
                token_search_len++;
            }
        }
        else if (strchr("=+-*/!%&~|<>?:.#", source_code[i_s]) != 0)
        { // 1文字目が普通の記号.
            while (strchr("=+-*/!%&~|<>?:.#", source_code[i_s + token_search_len]) != 0 && source_code[i_s + token_search_len] != 0)
                token_search_len++;
            i_s++;
        };

        // uchar current_token = getToken(&source_code[i_s], token_search_len);



        // *token->push_back();
    }

}

#endif Lexical