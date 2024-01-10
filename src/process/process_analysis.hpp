
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

#include "./../../bnf_syntax/softj/softj_tree.hpp"

#include "./process_analysis_definition.hpp"

#include "./../outhtml/outhtml.hpp"
namespace ProcessVisualization{

void debugProcessResult(ProcessVisualization::vProcessAnalysis process_result)
{
    for (int i = 0; i < process_result.size(); i++)
    {
        ProcessVisualization::ProcessAnalysis current = process_result[i];

        printf("%d : %d %s\n", i, current.process_type, current.message.c_str());
    }
}

void processAnalysis(vSyntacticTree syntactic_analysis_tree)
{
    printf("processAnalysis\n");
    vint parent_stack = {};

    ProcessVisualization::vProcessAnalysis process_result = {};

    ProcessVisualization::VariablePossessionUnion vpc;
    SoftjTree softjtree(syntactic_analysis_tree, process_result, vpc);

    debugProcessResult(process_result);
    HTMLParse::outputHtml(syntactic_analysis_tree  , process_result);
}
}
#endif