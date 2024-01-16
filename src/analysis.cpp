#include "./lexical/lexical_analysis.hpp"
#include "./lexical/lexical_analysis_definition.hpp"

#include "./syntactic/syntactic_analysis.hpp"
#include "./syntactic/syntactic_analysis_tree.hpp"
#include "./syntactic/syntactic_parse_tree.hpp"

#include "./process/process_analysis.hpp"
#include "./process/process_analysis_definition.hpp"
#include "./process/process_analysis_function.hpp"
#include "./process/process_analysis_value.hpp"

#include "definition.hpp"
#include "./LR_table/LR_table.hpp"
#include "./LR_table/LR_table_definition.hpp"
#include "./LR_table/LR_table_cell.hpp"
#include "./BNF/BNF.hpp"

#include "./input_table.hpp"

int main(int argc, char *argv[])
{
    char *source_code = new char[source_code_size * sizeof(char)];
    loadText(source_code, argv[1], source_code_size);

    char **token_string = new char *[token_string_arr_size * sizeof(char *)];
    int *token_progression = new int[token_progression_arr_size * sizeof(int)];
    vLexicalToken token_string_vector = lexSyntax(source_code);

    LRTableMultilayer LR_table_multilayer;
    inputTable("table.txt", LR_table_multilayer);

    printf("syntacticAnalysis\n");

    vReduceFormula syntactic_analysis_formula = {};
    syntacticAnalysis(LR_table_multilayer, token_string_vector, syntactic_analysis_formula);

    printf("syntacticPurseTree\n");
    vSyntacticTree syntactic_analysis_tree = {};

    syntacticAnalysisTree(syntactic_analysis_formula, syntactic_analysis_tree, token_string_vector);
    vSyntacticTree syntactic_parse_tree = syntactic_analysis_tree;

    syntacticParseTree(syntactic_parse_tree);
    ProcessVisualization::processAnalysis(syntactic_parse_tree,token_string_vector);

    // ソースコードは用済み
}