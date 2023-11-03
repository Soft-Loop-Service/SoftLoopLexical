
#ifndef __PRAS
#define __PRAS

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

class ProcessAnalysis
{
    int operation;
    vint data;
};

// #define is_id_Addition 1100       // 足し算記号
// #define is_id_Subtraction 1101    // 引き算記号
// #define is_id_Multiplication 1110 // 掛け算記号
// #define is_id_Division 1111       // 割り算記号
class ProcessAnalysisAddition : public ProcessAnalysis
{
};
class ProcessAnalysisSubtraction : public ProcessAnalysis
{
};
class ProcessAnalysisMultiplication : public ProcessAnalysis
{
};
class ProcessAnalysisDivision : public ProcessAnalysis
{
};
#endif