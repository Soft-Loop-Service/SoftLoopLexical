
#ifndef __SYNTAXA
#define __SYNTAXA

#include "./../LR_table/LR_table.hpp"
#include "./../LR_table/LR_table_definition.hpp"
#include "./../LR_table/LR_table_cell.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

// 入力を一つ消費して、指定された値をpushする
vstring syntacticAnalysisProcessShift(LRTableMultilayer LR_table_multilayer, string token, sint &stack_analysis)
{
    printf("syntacticAnalysisProcessShift");
    int top = stack_analysis.top();
    int next_state = LR_table_multilayer.LR_table_shift.LR_table_column_map[token][top].getCell();
    stack_analysis.push(next_state);
}

vReduceFormula syntacticAnalysisProcessReduce(LRTableMultilayer LR_table_multilayer, string token, sint &stack_analysis, vReduceFormula &ans_analysis)
{
    printf("syntacticAnalysisProcessReduce");
    // int top = stack_analysis.top();
    // ReduceFormula state = LR_table_multilayer.LR_table_reduce.LR_table_column_map[token][top].getCell();

    // for (int i = 0; i < state.token_vector.size(); i++)
    // {
    //     stack_analysis.pop();
    // }
    // ans_analysis.push_back(state);
    // int top2 = stack_analysis.top();
    // int next_state = LR_table_multilayer.LR_table_goto.LR_table_column_map[state.token_left][top2].getCell();
    // stack_analysis.push(next_state);
}

vstring syntacticAnalysisProcessAccept()
{
    printf("syntacticAnalysisProcessAccept\n");
}

vReduceFormula syntacticAnalysisProcess(LRTableMultilayer LR_table_multilayer, vstring token_string_vector)
{
    sint stack_analysis;
    vReduceFormula ans_analysis;

    stack_analysis.push(0);

    for (int i = 0; i < token_string_vector.size(); i++)
    {

        string current_token = token_string_vector[i];
        int top = stack_analysis.top();

        printf("syntacticAnalysisProcess %s %d\n", current_token.c_str(), top);

        if (LR_table_multilayer.LR_table_accept.LR_table_column_map[current_token][top].getValid())
        {
            // syntacticAnalysisProcessAccept();

            for (int a = 0; a < ans_analysis.size(); a++)
            {
                printf("syntacticAnalysisProcess acc %s\n", ans_analysis[a].token_left.c_str());
            }
            continue;
        }

        if (LR_table_multilayer.LR_table_shift.LR_table_column_map[current_token][top].getValid())
        {
            syntacticAnalysisProcessShift(LR_table_multilayer, current_token, stack_analysis);
            continue;
        }

        printf("拒否A\n");
        printf("拒否A2 %d\n", LR_table_multilayer.LR_table_reduce.LR_table_column_map[current_token][top].getValid());

        if (LR_table_multilayer.LR_table_reduce.LR_table_column_map[current_token][top].getValid())
        {
            printf("実行\n");
            syntacticAnalysisProcessReduce(LR_table_multilayer, current_token, stack_analysis, ans_analysis);
            // syntacticAnalysisProcessAccept();
            return ans_analysis;
            continue;
        }
        printf("拒否B\n");
    }
}

vReduceFormula syntacticAnalysis(LRTableMultilayer LR_table_multilayer, vstring token_string_vector)
{
    syntacticAnalysisProcess(LR_table_multilayer, token_string_vector);
}

#endif