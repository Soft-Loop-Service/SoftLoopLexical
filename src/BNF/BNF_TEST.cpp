// BNF定義ファイルからオートマトンを生成する

#include "./bnf_parser.hpp"
#include "./bnf_struct.hpp"

#include "./bnf_debug.hpp"
#include "./bnf_deployment.hpp"

#include "./symbol_table.hpp"
#include "./../debug.hpp"

#include "./../definition.hpp"

#include "./retrieve_symbol_table.hpp"
#include "./../item_set/item_set.hpp"
#include "./../DFA/dfa.hpp"
#include "./../DFA/dfa_calc.hpp"

#include "./../LR_table/LR_table.hpp"
#include "./../LR_table/LR_table_definition.hpp"
int main()
{
    char *bnf_source = (char *)calloc(source_code_size, sizeof(char *));
    loadText(bnf_source, "./src/BNF/BNF6.txt", source_code_size);
    // loadText(bnf_source, "./BNF3.txt", source_code_size);
    // loadText(bnf_source, "./BNF.txt", source_code_size);

    struct BNFToken bnf_token;
    struct BNFSymbol bnf_symbol;

    bnf_token.token_string_array = (char **)calloc(bnf_token_arr_len, sizeof(char **));
    bnf_token.token_len = parseBnf(bnf_source, bnf_token);
    bnf_token.token_label_array = (int *)calloc(bnf_token.token_len, sizeof(int));
    bnf_token.nonterminal_symbol_len = 0;
    bnf_token.terminal_symbol_len = 0;

    // // printf("token_len\n %d", token_len);
    free(bnf_source);

    output_token_string(bnf_token.token_string_array, bnf_token.token_len);

    labelingBnf(bnf_token);

    bnf_symbol.symbol_len = bnf_token.nonterminal_symbol_len + bnf_token.terminal_symbol_len;
    bnf_symbol.symbol_table_array = (int *)calloc(bnf_token.token_len, sizeof(int));
    bnf_symbol.symbol_string_array = (char **)calloc(bnf_token.token_len, sizeof(char **));
    printf("bnf_token %d %d %d %d\n", bnf_token.token_len, bnf_symbol.symbol_len, bnf_token.nonterminal_symbol_len, bnf_token.terminal_symbol_len);
    int unique_symbol_len = generateSymbolTable(bnf_token, bnf_symbol);

    printf("char size %ld %ld %ld\n", sizeof(char **), sizeof(char *), sizeof(char));

    struct RetrieveSymbol nonterminal_symbol_left;
    // 左辺非末端記号の配列を取得する
    retrieveSymbolTable(bnf_token, nonterminal_symbol_left, is_id_NonterminalSymbolLeft);
    // 左辺の数を取得する

    struct RetrieveSymbol terminal_symbol;
    // 末端記号の配列を取得する
    retrieveSymbolTable(bnf_token, bnf_symbol, terminal_symbol, is_id_TerminalSymbol);

    struct RetrieveSymbol symbols;
    concatenateArrayRetrieveSymbol(symbols, nonterminal_symbol_left, terminal_symbol);

    // struct RetrieveSymbol symbol_right;
    // 左辺非末端記号の配列を取得する
    // retrieveSymbolTable(bnf_token, bnf_symbol, symbol_right, is_id_TerminalSymbol);

    DeploymentStruct deployment_syntax = expansionDeployment(bnf_token, bnf_symbol, nonterminal_symbol_left, symbols);

    // ItemSetStruct item_set = generateItemSet(deployment_syntax);
    vDFANode dfa_node_graph = generateDFA(deployment_syntax);

    generateLRtable(dfa_node_graph, bnf_token, terminal_symbol, nonterminal_symbol_left);

    // 左辺の数を取得する

    // vAutomaton *automaton_graph = new Automaton[unique_symbol_len];

    // vAutomaton automaton_graph = {};
    // generateAutomaton(automaton_graph, bnf_token, bnf_symbol, nonterminal_symbol_left);

    free((bnf_token.token_label_array));
    free((bnf_token.token_string_array));
    free((bnf_symbol.symbol_string_array));
    free((bnf_symbol.symbol_table_array));
    // output_bnf_tablef(bnf_token, bnf_symbol);

    // for (int i = 0; i < sl_len ; i++){
    //     printf("nonterminal_symbol : %d %d" , nonterminal_symbol_left_array[i] , bnf_symbol.symbol_table_array[nonterminal_symbol_left_array[i]] );
    // }
}