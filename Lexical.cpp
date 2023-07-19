

#include "lexical_analysis.hpp"
#include "definition.hpp"

// プログラム・ファイルを読み込むための関数
void loadText(char *text, const char *file_name, int size)
{
    FILE *fp = fopen(file_name, "rb");
    int read_size = fread(text, 1, size - 1, fp);
    printf("read_size : %s %d\n", file_name, read_size);

    fclose(fp);
    text[read_size] = 0; // 終端マーク 別に配列終端でなくてよい
}

int main()
{
    printf("start program\n");

    char *source_code = new char[source_code_size];
    loadText(source_code, "sample.txt", source_code_size);

    char **token_string = new char *[token_string_arr_size];
    int *token_progression = new int[token_progression_arr_size];

    // vchar token = {};
    // vchar variable = {};

    lexSyntax(source_code, token_string, token_progression);
}