#ifndef Lexical
#include <vector>
typedef unsigned char *uchar;

int isAlphabetOrNumber(unsigned char ch)
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

void lexSyntax(uchar sc, std::vector<uchar> *token)
{

    int i = 0;

    for (;;)
    { // 終了コードまで
        if (sc[i] == 0)
        {
            return;
        }
        if (sc[i] == ' ' || sc[i] == '\t' || sc[i] == '\n' || sc[i] == '\r')
        { // スペース、タブ、改行.
            i++;
            continue;
        }

        i++;
    }

    // *token->push_back();
}

#endif Lexical