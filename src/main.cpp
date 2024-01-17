#include "./lexical/lexical_analysis.hpp"
#include "./syntactic/syntactic_analysis.hpp"
#include "./process/process_analysis.hpp"
#include "definition.hpp"
#include "./LR_table/LR_table.hpp"
#include "./BNF/BNF.hpp"

// int main(int argc, char *argv[])
// {
//     printf("start program\n");

//     char *source_code = new char[source_code_size * sizeof(char)];
//     loadText(source_code, "sample.txt", source_code_size);

//     char **token_string = new char *[token_string_arr_size * sizeof(char *)];
//     int *token_progression = new int[token_progression_arr_size * sizeof(int)];

//     vstring token_string_vector = lexSyntax(source_code);

//     delete source_code;
//     delete token_string;
//     delete token_progression;
//     output_vector("token_string_vector", token_string_vector);

//     LRTableMultilayer LR_table_multilayer;

//     bnfMain(argv[1], LR_table_multilayer);

//     vReduceFormula syntactic_analysis_formula = {};
//     syntacticAnalysis(LR_table_multilayer, token_string_vector, syntactic_analysis_formula);

//     printf("syntacticPurseTree\n");
//     vSyntacticTree syntactic_analysis_tree = {};

//     syntacticAnalysisTree(syntactic_analysis_formula, syntactic_analysis_tree);
//     vSyntacticTree syntactic_parse_tree = syntactic_analysis_tree;

//     syntacticParseTree(syntactic_parse_tree);
//     processAnalysis(syntactic_parse_tree);

//     // ソースコードは用済み
// }