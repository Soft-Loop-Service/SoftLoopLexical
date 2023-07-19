

#include "lexical_analysis.hpp"
#include "definition.hpp"

// プログラム・ファイルを読み込むための関数
void loadText(char *text, const char *file_name, int size)
{
    FILE *fp = fopen(file_name, "rb");
    int read_size = fread(text, 1, size - 1, fp);
    printf("read_size %d", read_size);

    fclose(fp);
    text[read_size] = 0; // 終端マーク
}

int main()
{
    printf("start program");

    int size = 1000000;
    char *source_code;
    // loadText(source_code, "sample.txt", size);

    vchar *token;
    vchar *variable;

    // lexSyntax(source_code,token,variable);
}