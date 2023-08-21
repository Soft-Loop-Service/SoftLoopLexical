// BNF定義ファイルからオートマトンを生成する
#include "./../definition.hpp"
#include "./bnf_parser.hpp"
#include "./bnf_struct.hpp"
#include "./../debug.hpp"
#include "./bnf_debug.hpp"
#include "./symbol_table.hpp"
#include "./automaton.hpp"
#include "./retrieve_symbol_table.hpp"

int main()
{
    char *bnf_source = new char[source_code_size];
    loadText(bnf_source, "./src/BNF/BNF.txt", source_code_size);
    // loadText(bnf_source, "./BNF.txt", source_code_size);

    BNFToken bnf_token;
    BNFSymbol bnf_symbol;


    bnf_token.token_string_array = (char **)calloc(bnf_token_arr_len, sizeof(char**));
    bnf_token.token_len = parseBnf(bnf_source, bnf_token);
    bnf_token.token_label_array = new int[bnf_token.token_len];
    bnf_token.nonterminal_symbol_len = 0;
    bnf_token.terminal_symbol_len = 0;
    
    // // printf("token_len\n %d", token_len);
    free(bnf_source);

    output_token_string(bnf_token.token_string_array, bnf_token.token_len);

    labelingBnf(bnf_token);

    bnf_symbol.symbol_len = bnf_token.nonterminal_symbol_len + bnf_token.terminal_symbol_len;
    bnf_symbol.symbol_table_array = new int[bnf_token.token_len];
    bnf_symbol.symbol_string_array = (char **)calloc(bnf_token_arr_len, sizeof(char**));
    printf("bnf_token %d %d %d %d\n",bnf_token.token_len,bnf_symbol.symbol_len , bnf_token.nonterminal_symbol_len , bnf_token.terminal_symbol_len);
    int unique_symbol_len = generateSymbolTable(bnf_token, bnf_symbol);

    printf("char size %ld %ld %ld\n",sizeof(char**),sizeof(char*),sizeof(char));

    int *nonterminal_symbol_left_array;
    int sl_len = retrieveSymbolTable(bnf_token,bnf_symbol , is_id_NonterminalSymbolLeft  ,nonterminal_symbol_left_array);

    free(&(bnf_token.token_label_array));
    free(&(bnf_token.token_string_array));
    free(&(bnf_symbol.symbol_string_array));
    free(&(bnf_symbol.symbol_table_array));
    // output_bnf_tablef(bnf_token, bnf_symbol);

    // Automaton *automaton_graph = new Automaton[unique_symbol_len];
    // generateAutomaton(automaton_graph, bnf_token, bnf_symbol);

    // for (int i = 0; i < sl_len ; i++){
    //     printf("nonterminal_symbol : %d %d" , nonterminal_symbol_left_array[i] , bnf_symbol.symbol_table_array[nonterminal_symbol_left_array[i]] );
    // }


}