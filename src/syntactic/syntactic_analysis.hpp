
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
void syntacticAnalysisProcessShift(LRTableMultilayer LR_table_multilayer, string token, sint &stack_analysis)
{
    printf("syntacticAnalysisProcessShift\n");
    int top = stack_analysis.top();
    int next_state = LR_table_multilayer.LR_table_shift.LR_table_column_map[token][top].getCell();
    stack_analysis.push(next_state);
}

void syntacticAnalysisProcessReduce(LRTableMultilayer LR_table_multilayer, string token, sint &stack_analysis, vReduceFormula &ans_analysis)
{
    printf("syntacticAnalysisProcessReduce\n");
    int top = stack_analysis.top();
    ReduceFormula state = LR_table_multilayer.LR_table_reduce.LR_table_column_map[token][top].getCell();
    ans_analysis.push_back(state);

    for (int i = 0; i < state.token_vector.size(); i++)
    {
        stack_analysis.pop();
    }

    int top2 = stack_analysis.top();
    int next_state = LR_table_multilayer.LR_table_goto.LR_table_column_map[state.token_left][top2].getCell();
    stack_analysis.push(next_state);
    printf("syntacticAnalysisProcessReduce end\n");
}

void syntacticAnalysisProcessAccept()
{
    printf("syntacticAnalysisProcessAccept\n");
}

void syntacticAnalysisProcess(LRTableMultilayer LR_table_multilayer, vstring token_string_vector)
{
    sint stack_analysis;
    vReduceFormula ans_analysis;

    stack_analysis.push(0);

    for (int i = 0; i < token_string_vector.size(); i++)
    {

        string current_token = token_string_vector[i];
        int top = stack_analysis.top();

        printf("syntacticAnalysisProcess %s %d\n", current_token.c_str(), top);

        printf("A\n");
        if (LR_table_multilayer.LR_table_accept.LR_table_column_map[current_token][top].getValid())
        {
            // syntacticAnalysisProcessAccept();

            for (int a = 0; a < ans_analysis.size(); a++)
            {
                printf("syntacticAnalysisProcess acc %s\n", ans_analysis[a].token_left.c_str());
            }
            continue;
        }

        printf("B\n");
        printf("B2 %d\n", LR_table_multilayer.LR_table_shift.LR_table_column_map[current_token][top].getValid());
        if (LR_table_multilayer.LR_table_shift.LR_table_column_map[current_token][top].getValid())
        {
            syntacticAnalysisProcessShift(LR_table_multilayer, current_token, stack_analysis);
            continue;
        }

        printf("C\n");
        printf("D %d\n", LR_table_multilayer.LR_table_reduce.LR_table_column_map[current_token][top].getValid());

        if (LR_table_multilayer.LR_table_reduce.LR_table_column_map[current_token][top].getValid())
        {
            printf("実行\n");
            syntacticAnalysisProcessReduce(LR_table_multilayer, current_token, stack_analysis, ans_analysis);
            // syntacticAnalysisProcessAccept();
            continue;
        }
        printf("ERROR\n");
        return;
    }
}

void syntacticAnalysis(LRTableMultilayer LR_table_multilayer, vstring token_string_vector)
{
    syntacticAnalysisProcess(LR_table_multilayer, token_string_vector);
}

#endif