
#ifndef __SYNTPT
#define __SYNTPT

// 構文木

#include "./../LR_table/LR_table.hpp"
#include "./../LR_table/LR_table_definition.hpp"
#include "./../LR_table/LR_table_cell.hpp"
#include "./syntactic_analysis_tree.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

void syntacticParseTree(LRTableMultilayer LR_table_multilayer, vstring token_string_vector, vReduceFormula syntactic_analysis_formula, vSyntacticTree &syntactic_tree)
{
}

#endif