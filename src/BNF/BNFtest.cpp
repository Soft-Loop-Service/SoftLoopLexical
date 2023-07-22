// BNF定義ファイルからオートマトンを生成する
#include "./../definition.hpp"
#include "./BNFparser.hpp"
#include "./../debug.hpp"

int main()
{
    char *bnf_source = new char[source_code_size];
    loadText(bnf_source, "./src/BNF/BNF.txt", source_code_size);

    char **token_string = new char *[1000];
    int token_len = parseBnf(bnf_source, token_string);

    output_token_string(token_string, token_len);
}