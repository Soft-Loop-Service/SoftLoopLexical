
#ifndef __PRA
#define __PRA

#include "./../LR_table/LR_table.hpp"
#include "./../LR_table/LR_table_definition.hpp"
#include "./../LR_table/LR_table_cell.hpp"
#include "./../syntactic/syntactic_analysis_tree.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "./../../bnf_syntax/softj/softj.hpp"

#include "./process_analysis_definition.hpp"

#include "./../html_kit/outhtml.hpp"
namespace ProcessVisualization
{

    void debugProcessResult(ProcessAnalysisTimeline process_timeline)
    {
        vProcessAnalysis process_result = process_timeline.getProcessResult();
        for (int i = 0; i < process_result.size(); i++)
        {
            ProcessAnalysis current = process_result[i];

            printf("%d : %2s %s : ", i, current.process_type.c_str(), current.message.c_str());

            // for (int j = 0 ; j < current.layer.size() ; j++){
            //     printf(" %d",current.layer[j].layer);
            // }

            printf("\n");
        }
    }

    void processAnalysis(vSyntacticTree syntactic_analysis_tree, vLexicalToken token_string_vector)
    {
        printf("processAnalysis\n");
        vint parent_stack = {};

        ProcessAnalysisTimeline process_timeline;

        VariablePossessionUnion variable_possession_union;
        FunctionPossessionUnion function_possession_union;
        LanguageSpecifications::SoftjLanguage::Softj softjtree(syntactic_analysis_tree, process_timeline, variable_possession_union, function_possession_union);
        softjtree.calc();

        debugProcessResult(process_timeline);
        HTMLParse::outputHtml(syntactic_analysis_tree, process_timeline, variable_possession_union, token_string_vector);
    }

}
#endif