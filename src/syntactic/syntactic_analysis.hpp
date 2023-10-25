
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

void output_vReduceFormula(string name, vReduceFormula v)
{
    printf("%s 結果 : ", name.c_str());
    int vsize = v.size();
    for (int i = 0; i < vsize; i++)
    {
        // printf("%s ", v[vsize - i - 1].token_left.c_str());
        printf("%s%d ", v[i].token_left.c_str(), v[i].depth);
    }
    printf("\n");
}

// 入力を一つ消費して、指定された値をpushする
void syntacticAnalysisProcessShift(LRTableMultilayer LR_table_multilayer, string token, sint &stack_analysis)
{
    printf("Shift : ");
    int top = stack_analysis.top();

    printf("top : %d ", top);

    int next_state = LR_table_multilayer.LR_table_shift.LR_table_column_map[token][top].getCell();
    stack_analysis.push(next_state);
    printf("\n");
}

void syntacticAnalysisProcessReduce(LRTableMultilayer LR_table_multilayer, string token, sint &stack_analysis, vReduceFormula &ans_analysis)
{
    printf("Reduce : ");
    int top = stack_analysis.top();
    ReduceFormula state = LR_table_multilayer.LR_table_reduce.LR_table_column_map[token][top].getCell();
    ans_analysis.push_back(state);

    printf("token_left : %s %d ", state.token_left.c_str(), state.token_vector.size());

    for (int i = 0; i < state.token_vector.size(); i++)
    {
        stack_analysis.pop();
    }

    int top2 = stack_analysis.top();
    printf("top2 : %d ", top2);

    int next_state = LR_table_multilayer.LR_table_goto.LR_table_column_map[state.token_left][top2].getCell();
    stack_analysis.push(next_state);
    printf("\n");

    int default_depth = 0;

    for (int i = 1; i < ans_analysis.size(); i++)
    {
        int bi = ans_analysis.size() - 1 - i;

        default_depth++;

        ans_analysis[bi].depth = default_depth;

        if (ans_analysis[bi].token_vector.size() == 1 && ans_analysis[bi].token_vector[0].label == is_id_TerminalSymbol)
        {
            default_depth = 0;
        }
    }
}

void syntacticAnalysisProcessAccept()
{
    printf("syntacticAnalysisProcessAccept\n");
}

vReduceFormula syntacticAnalysisProcess(LRTableMultilayer LR_table_multilayer, vstring token_string_vector)
{
    sint stack_analysis;              // 構文解析表スタック
    vReduceFormula ans_analysis = {}; // 構文解析表出力。出力ストリーム

    stack_analysis.push(0);

    int i = 0;
    while (i < token_string_vector.size())
    {

        string current_token = token_string_vector[i];
        int top = stack_analysis.top();
        printf("CurrentToken %s\n", current_token.c_str());

        if (LR_table_multilayer.LR_table_accept.LR_table_column_map[current_token][top].getValid())
        {
            printf("acc \n");
            return ans_analysis;
        }

        if (LR_table_multilayer.LR_table_shift.LR_table_column_map[current_token][top].getValid())
        {
            syntacticAnalysisProcessShift(LR_table_multilayer, current_token, stack_analysis);
            output_stack("構文解析", stack_analysis);
            output_vReduceFormula("構文解析", ans_analysis);

            printf("\n");
            i++;
            continue;
        }

        if (LR_table_multilayer.LR_table_reduce.LR_table_column_map[current_token][top].getValid())
        {
            syntacticAnalysisProcessReduce(LR_table_multilayer, current_token, stack_analysis, ans_analysis);
            output_stack("構文解析", stack_analysis);
            output_vReduceFormula("構文解析", ans_analysis);

            printf("\n");
            continue;
        }
        printf("ERROR\n");
        return ans_analysis;
    }
    output_stack("構文解析 終了", stack_analysis);
    output_vReduceFormula("構文解析 終了", ans_analysis);

    return ans_analysis;
}

vReduceFormula syntacticAnalysis(LRTableMultilayer LR_table_multilayer, vstring token_string_vector)
{
    vReduceFormula ans_analysis = syntacticAnalysisProcess(LR_table_multilayer, token_string_vector);
    return ans_analysis;
}

#endif