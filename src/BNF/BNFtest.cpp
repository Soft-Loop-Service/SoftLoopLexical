// BNF定義ファイルからオートマトンを生成する
#include "./../definition.hpp"
#include "./BNFparser.hpp"
#include "./BNFstruct.hpp"
#include "./../debug.hpp"
#include "./BNFdebug.hpp"
#include "./symbolTable.hpp"
#include "./automaton.hpp"

int main()
{
    char *bnf_source = new char[source_code_size];
    loadText(bnf_source, "./src/BNF/BNF.txt", source_code_size);

    BNFToken bnf_token;
    BNFSymbol bnf_symbol;

    bnf_token.token_string = (char **)calloc(bnf_token_string_len, 1);
    bnf_token.token_len = parseBnf(bnf_source, bnf_token);
    // // printf("token_len\n %d", token_len);
    free(bnf_source);

    output_token_string(bnf_token.token_string, bnf_token.token_len);

    bnf_token.token_label = new int[bnf_token.token_len];

    labelingBnf(bnf_token);
    // // output_labeling_bnf(token_string, token_label, token_len);

    // // printf("sl %d %d %d\n", *nonterminal_symbol_len, *terminal_symbol_len,token_len);

    bnf_symbol.symbol_len = bnf_token.nonterminal_symbol_len + bnf_token.terminal_symbol_len;
    bnf_symbol.symbol_table = new int[bnf_token.token_len];
    bnf_symbol.symbol_string = (char **)calloc(bnf_token.token_len, bnf_token_len);

    int unique_symbol_len = generateSymbolTable(bnf_token, bnf_symbol);

    output_bnf_tablef(bnf_token, bnf_symbol);

    Automaton *automaton_graph = new Automaton[unique_symbol_len];
    generateAutomaton(automaton_graph, bnf_token, bnf_symbol);
}