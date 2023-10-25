
#ifndef __SYNTPT
#define __SYNTPT

#include "./../LR_table/LR_table.hpp"
#include "./../LR_table/LR_table_definition.hpp"
#include "./../LR_table/LR_table_cell.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

struct SyntacticTreeNode // 構文解析用
{
    string token_left;                   // 左辺
    vDeploymentTokenStruct token_vector; // 展開したBNFの右辺
    vint children;
    // int parent;
};
typedef vector<SyntacticTreeNode> vSyntacticTree;

void syntacticPurseTreeDFS() // 導出木に変換するため深さ優先探索を行う。その地点で木構造に分類する。つまり細かく木構造に分割していくイメージ。
{
}

vSyntacticTree syntacticPurseTree(LRTableMultilayer LR_table_multilayer, vstring token_string_vector, vReduceFormula ans_analysis)
{

    // ans_analysisは構文解析の結果 後ろから見ていくことで木構造を構築する

    vSyntacticTree syntactic_tree = {};
}

#endif