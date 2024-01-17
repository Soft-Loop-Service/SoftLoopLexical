#include "./lexical/lexical_analysis.hpp"
#include "./syntactic/syntactic_analysis.hpp"
#include "./process/process_analysis.hpp"
#include "definition.hpp"
#include "./LR_table/LR_table.hpp"
#include "./BNF/bnf.hpp"
#include "./input_table.hpp"
#include "./softj/softj.hpp"
#include "./html_kit/html_kit.hpp"

int main(int argc, char *argv[])
{
    char *source_code = new char[source_code_size * sizeof(char)];
    loadText(source_code, argv[1], source_code_size);

    char **token_string = new char *[token_string_arr_size * sizeof(char *)];
    int *token_progression = new int[token_progression_arr_size * sizeof(int)];
    LexicalAnalysis::vLexicalToken token_string_vector = LexicalAnalysis::lexSyntax(source_code);

    LRTable::LRTableMultilayer LR_table_multilayer;
    inputTable("table.txt", LR_table_multilayer);

    printf("syntacticAnalysis\n");

    LRTable::vReduceFormula syntactic_analysis_formula = {};
    Syntactic::syntacticAnalysis(LR_table_multilayer, token_string_vector, syntactic_analysis_formula);

    printf("syntacticPurseTree\n");
    Syntactic::vSyntacticTree syntactic_analysis_tree = {};

    Syntactic::syntacticAnalysisTree(syntactic_analysis_formula, syntactic_analysis_tree, token_string_vector);
    Syntactic::vSyntacticTree syntactic_parse_tree = syntactic_analysis_tree;

    Syntactic::syntacticParseTree(syntactic_parse_tree);
    // ProcessVisualization::processAnalysis(syntactic_parse_tree, token_string_vector);

    vint parent_stack = {};

    ProcessVisualization::ProcessAnalysisTimeline process_timeline;
    ProcessVisualization::VariablePossessionUnion variable_possession_union;
    ProcessVisualization::FunctionPossessionUnion function_possession_union;
    LanguageSpecifications::SoftjLanguage::Softj softjtree(syntactic_analysis_tree, process_timeline, variable_possession_union, function_possession_union);
    softjtree.calc();
    debugProcessResult(process_timeline);
    HTMLParse::outputHtml(syntactic_analysis_tree, process_timeline, variable_possession_union, token_string_vector);
    // ソースコードは用済み
}
