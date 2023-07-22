#include "./lexical/lexical_analysis.hpp"
#include "definition.hpp"

int main()
{
    printf("start program\n");

    char *source_code = new char[source_code_size];
    loadText(source_code, "sample.txt", source_code_size);

    char **token_string = new char *[token_string_arr_size];
    int *token_progression = new int[token_progression_arr_size];

    lexSyntax(source_code, token_string, token_progression);

    free(source_code);
    // ソースコードは用済み
}