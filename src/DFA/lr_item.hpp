
#ifndef __LRITEM
#define __LRITEM
#include "./../definition.hpp"
#include "./../symbol.hpp"
#include "./../BNF/bnf_struct.hpp"
#include "./../BNF/bnf_right.hpp"
#include "./../BNF/bnf_deployment.hpp"
// #include "./closure_expansion.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

#define ROOT_DFA_SYMBOL "<_S>"
#define START_DFA_SYMBOL "<S>"

struct LRItemStruct;
struct DFANode;
struct LRItemFormulaStruct;
struct LRItemFormulaExpansionStruct;
// typedef std::vector<LRItemStruct> vLRItemStruct;
typedef std::vector<DFANode> vDFANode;
typedef std::vector<LRItemFormulaStruct> vLRItemFormulaStruct;
typedef std::vector<LRItemFormulaExpansionStruct> vLRItemFormulaExpansionStruct;
typedef std::map<string, LRItemFormulaStruct> mapLRItemFormulaStruct;
/*
DFANodeはLRItemStructの機能に加えて他nodeの事も考えることができる。LRItemStructはコンポジションである
*/

struct LRItemStruct // LRItemStructは自分のこと(自身node)の事しか考えることができない
{
    mapLRItemFormulaStruct LR_formula_map;
};

// 構造体 式
struct LRItemFormulaStruct
{

    vLRItemFormulaExpansionStruct LR_formula_expansion_vector;
};

/*構造体 展開した式
lookAhead : 先読み記号
*/
struct LRItemFormulaExpansionStruct : DeploymentFormulaExpansionStruct
{
    vDeploymentTokenStruct lookAhead;
};
struct DFANode
{
    LRItemStruct lr_item;
    mp_s_i children_nodes;            // 子要素のindex
    vint has_formula_expansion_label; // 高速計算用。子ノードが何を持っているかを保有
    string node_label;                // 受理記号 rootである<_S>にはrootと代入される
};

#endif