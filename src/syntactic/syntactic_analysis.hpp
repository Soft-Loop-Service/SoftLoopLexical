
#ifndef __SYNTAXA
#define __SYNTAXA

#include "./../definition.hpp"
#include "./../debug.hpp"
#include "./../symbol.hpp"

#include "./../analysis/common_analysis.hpp"
#include "./../analysis/common_analysis_tree.hpp"

void syntacticAnalysis(LRTableMultilayer LR_table_multilayer, vstring token_string_vector, vReduceFormula &syntactic_analysis_formula)
{
    commonAnalysis(LR_table_multilayer, token_string_vector, syntactic_analysis_formula);
    return;
}

void syntacticAnalysisTree(vReduceFormula syntactic_analysis_formula, vSyntacticTree &syntactic_analysis_tree)
{
    commonAnalysisTree(syntactic_analysis_formula, syntactic_analysis_tree);
    return;
}

#endif