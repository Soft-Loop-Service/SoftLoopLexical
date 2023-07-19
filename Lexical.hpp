#ifndef _L_H
#define _L_H

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

// int getToken(uchar sc, )
// {
// }

void splitToken(uchar sc, uchar t, int s, int len)
{
    for (int i = 0; i < len; i++)
    {
        t[i] = sc[s + i];
    }
}

void lexSyntax(uchar sc, std::vector<uchar> *tokens)
{

    int i = 0, j = 0;

    for (;;)
    { // 終了コードまで

        int len = 0;

        if (sc[i] == 0)
        {
            return;
        }
        if (sc[i] == ' ' || sc[i] == '\t' || sc[i] == '\n' || sc[i] == '\r')
        { // スペース、タブ、改行.
            i++;
            len = 1;
            continue;
        }
        if (isAlphabetOrNumber(sc[i]))
        {
            while (isAlphabetOrNumber(sc[i + len]))
                len++;
        }

        uchar t = new unsigned char[len];
        splitToken(sc, t, j, len);
        tokens->push_back(t);
        j += len;
    }

    // *token->push_back();
}

#endif _L_H