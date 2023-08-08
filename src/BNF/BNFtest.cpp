// BNF定義ファイルからオートマトンを生成する
#include "./../definition.hpp"
#include "./BNFparser.hpp"
#include "./../debug.hpp"
#include "./symbolTable.hpp"

int main()
{
    char *bnf_source = new char[source_code_size];
    loadText(bnf_source, "./src/BNF/BNF.txt", source_code_size);

    char **token_string = (char **)calloc(bnf_token_string_len, 1);
    int token_len = parseBnf(bnf_source, token_string);
    printf("token_len\n %d", token_len);
    free(bnf_source);

    output_token_string(token_string, token_len);

    int *token_label = new int[token_len];

    int np = 0;
    int tp = 0; // ポインタ確保用
    int *nonterminal_symbol_len, *terminal_symbol_len;
    nonterminal_symbol_len = &np;
    terminal_symbol_len = &tp;

    labelingBnf(token_string, token_len, token_label, nonterminal_symbol_len, terminal_symbol_len);
    output_labeling_bnf(token_string, token_label, token_len);

    printf("sl %d %d %d\n", *nonterminal_symbol_len, *terminal_symbol_len,token_len);

    int symbol_len = *nonterminal_symbol_len + *terminal_symbol_len;
    int *symbol_table = new int[token_len];
    char **symbol_string = (char **)calloc(symbol_len, bnf_token_len);
    int unique_symbol_len = generateSymbolTable(token_string, symbol_string, symbol_table, token_label, token_len,symbol_len);
    output_bnf_tablef(token_string, symbol_string, symbol_table, token_label,token_len, unique_symbol_len);


}