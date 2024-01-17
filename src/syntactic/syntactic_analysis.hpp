
#ifndef __SYNTDT
#define __SYNTDT
#include "./../definition.hpp"
#include "./../LR_table/LR_table.hpp"
#include "./../symbol.hpp"
#include "./../lexical/lexical_analysis.hpp"

namespace Syntactic
{
    struct SyntacticTreeNode // 構文解析用
    {
        string token;
        int token_label;
        vint children;
        string parent_token;

        int source_code_line;
        int source_code_column;
        int token_order;
    };
    typedef vector<SyntacticTreeNode> vSyntacticTree;

    void output_vReduceFormula(string name, LRTable::vReduceFormula v);
    void syntacticAnalysisProcessShift(LRTable::LR_table_multilayer, string token_tyoke, sint &stack_analysis);
    void syntacticAnalysisProcessReduce(LRTable::LRTableMultilayer LR_table_multilayer, string token_tyoke, sint &stack_analysis,LRTable::vReduceFormula &syntactic_analysis_formula);
    void syntacticAnalysisProcessAccept();
    void syntacticAnalysisProcess(LRTable::LRTableMultilayer LR_table_multilayer, LexicalAnalysis::vLexicalToken token_string_vector, LRTable::vReduceFormula &syntactic_analysis_formula);
    void syntacticAnalysis(LRTable::LRTableMultilayer LR_table_multilayer, LexicalAnalysis::vLexicalToken token_string_vector, LRTable::vReduceFormula &syntactic_analysis_formula);
    bool isTokenSkepSyntacticAnalysis(string token_str);
    bool isTokenExpr(string token_str);
    int isCutExpr(vSyntacticTree &syntactic_parse_tree, int current_node_index);
    int cutExpr(vSyntacticTree &syntactic_parse_tree, int current_node_index);
    int recursionCutExpr(vSyntacticTree &syntactic_parse_tree, int current_node_index);
    int recursionCutSyntacticParseTree(vSyntacticTree &syntactic_parse_tree, int current_node_index);
    void recursionSyntacticParseTree(vSyntacticTree &syntactic_parse_tree, int current_node_index);
    void syntacticParseTree(vSyntacticTree &syntactic_parse_tree);
    void recursionSyntacticAnalysisTreeDFS(vSyntacticTree &syntactic_analysis_tree, LRTable::vReduceFormula &syntactic_analysis_formula, LexicalAnalysis::vLexicalToken token_string_vector, int &search_first_index, int parent_node_index, int depth);
    void debugSyntacticAnalysisTree(vSyntacticTree &syntactic_analysis_tree);
    void syntacticAnalysisTreeSubstitution(LRTable::vReduceFormula syntactic_analysis_formula, vSyntacticTree &syntactic_analysis_tree, LexicalAnalysis::vLexicalToken token_string_vector);
    void syntacticAnalysisTree(LRTable::vReduceFormula syntactic_analysis_formula, vSyntacticTree &syntactic_analysis_tree, LexicalAnalysis::vLexicalToken token_string_vector);
}
#endif