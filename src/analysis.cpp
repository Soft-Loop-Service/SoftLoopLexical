#include "./lexical/lexical_analysis.hpp"
#include "./syntactic/syntactic_analysis.hpp"
#include "./syntactic/syntactic_parse_tree.hpp"

#include "./process/process_analysis.hpp"

#include "definition.hpp"
#include "./LR_table/LR_table.hpp"
#include "./LR_table/LR_table_definition.hpp"
#include "./LR_table/LR_table_cell.hpp"
#include "./BNF/BNF.hpp"

#include "./input_table.hpp"

int main(int argc, char *argv[])
{
    char *source_code = new char[source_code_size * sizeof(char)];
    loadText(source_code, "sample.txt", source_code_size);

    LRTableMultilayer LR_table_multilayer;
    inputTable(argv[1], LR_table_multilayer);

    printf("syntacticAnalysis\n");

    vReduceFormula syntactic_analysis_formula = {};
    syntacticAnalysis(LR_table_multilayer, {}, syntactic_analysis_formula);

    printf("syntacticPurseTree\n");
    vSyntacticTree syntactic_analysis_tree = {};

    syntacticAnalysisTree(syntactic_analysis_formula, syntactic_analysis_tree);
    vSyntacticTree syntactic_parse_tree = syntactic_analysis_tree;

    syntacticParseTree(syntactic_parse_tree);
    processAnalysis(syntactic_parse_tree);

    // ソースコードは用済み
}