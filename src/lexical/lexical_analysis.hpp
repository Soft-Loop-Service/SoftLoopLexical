// 字句解析定義ファイル

#ifndef __LexicalAnalysis
#define __LexicalAnalysis

#include "./../definition.hpp"
#include "./../debug.hpp"
#include "./../symbol.hpp"

#include "./../analysis/common_analysis.hpp"

void lexicalAnalysisProcess(LRTableMultilayer LR_table_multilayer, vstring token_string_vector, vReduceFormula &lexical_analysis_formula)
{
    commonAnalysis(LR_table_multilayer, token_string_vector, lexical_analysis_formula);

    for (int i = 0; i < lexical_analysis_formula.size(); i++)
    {
        // lexical_analysis_formula[i].
    }
    return;
}

#endif