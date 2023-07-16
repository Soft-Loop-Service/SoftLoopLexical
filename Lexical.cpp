#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

#include "LexicalAnalysis.hpp"

using namespace std;

// プログラム・ファイルを読み込むための関数
void loadText(unsigned char *text, const char *file_name, int size)
{
    FILE *fp = fopen(file_name, "rb");
    int read_size = fread(text, 1, size - 1, fp);
    fclose(fp);
    text[read_size] = 0; // 終端マーク
}

int main()
{

    int size = 1000000;
    unsigned char *source_code;
    loadText(source_code, "sample.txt", size);

    std::vector<unsigned char *> *token;
    lexSyntax(source_code, token);
}