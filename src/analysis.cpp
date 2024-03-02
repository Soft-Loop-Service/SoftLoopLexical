#include "./lexical/lexical_analysis.hpp"
#include "./syntactic/syntactic_analysis.hpp"
#include "./process/process_analysis.hpp"
#include "./definition.hpp"
#include "./LR_table/LR_table.hpp"
#include "./BNF/bnf.hpp"
#include "./input_table.hpp"
#include "./softj/softj.hpp"
#include "./html_kit/html_kit.hpp"

int main(int argc, char *argv[])
{
    char *source_code = new char[source_code_size * sizeof(char)];
    loadText(source_code, argv[1], source_code_size);

    string source_code_file_name = argv[1];

    char **token_string = new char *[token_string_arr_size * sizeof(char *)];
    int *token_progression = new int[token_progression_arr_size * sizeof(int)];
    LexicalAnalysis::vLexicalToken token_string_vector = LexicalAnalysis::lexSyntax(source_code);

    LRTable::LRTableMultilayer LR_table_multilayer;
    inputTable("table.txt", LR_table_multilayer);

    printf("（成功）構文解析テーブルの読み込み\n");

    LRTable::vReduceFormula syntactic_analysis_formula = {};
    Syntactic::syntacticAnalysis(LR_table_multilayer, token_string_vector, syntactic_analysis_formula);

    printf("（成功）構文解析の実行\n");
    Syntactic::vSyntacticTree syntactic_analysis_tree = {};

    Syntactic::syntacticAnalysisTree(syntactic_analysis_formula, syntactic_analysis_tree, token_string_vector);
    Syntactic::vSyntacticTree syntactic_parse_tree = syntactic_analysis_tree;

    printf("（成功）構文木の整理(1)\n");

    Syntactic::syntacticParseTree(syntactic_parse_tree);

    printf("（成功）構文木の整理(2)\n");
    // ProcessVisualization::processAnalysis(syntactic_parse_tree, token_string_vector);

    vint parent_stack = {};

    ProcessVisualization::VariablePossession variable_possession;
    ProcessVisualization::VariablePossessionUnion variable_possession_union(variable_possession);

    ProcessVisualization::ProcessAnalysisTimeline process_timeline(variable_possession_union, variable_possession);
    ProcessVisualization::FunctionPossessionUnion function_possession_union;
    LanguageSpecifications::SoftjLanguage::Softj softjtree(syntactic_parse_tree, process_timeline, variable_possession_union, function_possession_union);

    printf("（成功）実行オブジェクトの生成\n");
    
    softjtree.calc();

    printf("（成功）トレース実行\n");

    // debugProcessResult(process_timeline);
    HTMLParse::outputHtml(syntactic_parse_tree, process_timeline, variable_possession_union, token_string_vector, source_code_file_name);
    
    printf("（成功）可視化ファイルの生成\n");

    // ソースコードは用済み
}
