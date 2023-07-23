// BNF定義ファイルからオートマトンを生成する
#include "./../definition.hpp"
#include "./BNFparser.hpp"
#include "./../debug.hpp"

int main()
{
    char *bnf_source = new char[source_code_size];
    loadText(bnf_source, "./src/BNF/BNF.txt", source_code_size);

    char **token_string = (char **)calloc(1000, 1);
    int token_len = parseBnf(bnf_source, token_string);
    printf("token_len\n %d", token_len);
    free(bnf_source);

    output_token_string(token_string, token_len);

    int *token_label = new int[token_len];
    labelingBnf(token_string, token_label, token_len);
    output_labeling_bnf(token_string, token_label, token_len);
}