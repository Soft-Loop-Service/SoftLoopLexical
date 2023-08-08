
#ifndef __Debug
#define __Debug
#include "definition.hpp"


void output_token_string(char **token_string, int line)
{
    for (int i = 0; i < line; i++)
    {
        printf("output_token_string :%d %s\n", i, *&token_string[i]);
    }
}
void output_token_progression(char **token_string, int *token_progression, int line)
{
    for (int i = 0; i < line; i++)
    {
        // printf("%s\n", &token[variable[i]]);
        printf("output_token_progression a : %d\n", token_progression[i]);
    }
    for (int i = 0; i < line; i++)
    {
        // printf("%s\n", &token[variable[i]]);
        printf("output_token_progression b : %s\n", *&token_string[token_progression[i]]);
    }
}

int output_labeling_bnf(char **token_string, int *token_label, int token_len)
{
    for (int i = 0; i < token_len; i++)
    {
        // printf("%s\n", &token[variable[i]]);
        printf("olb %d: %25s %d\n", token_len, token_string[i], token_label[i]);
    }
}


#endif