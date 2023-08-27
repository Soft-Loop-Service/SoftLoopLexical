
#ifndef __LRITEM
#define __LRITEM
#include "./item_set_calc.hpp"
#include "./../definition.hpp"
#include "./../symbol.hpp"
#include "./../BNF/bnf_struct.hpp"
#include "./../BNF/bnf_right.hpp"
#include "./../BNF/bnf_vector.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

typedef std::vector<LRItemStruct> vLRItemStruct;
typedef std::vector<LRItemFormulaStruct> vLRItemFormulaStruct;
typedef std::vector<LRItemFormulaExpansionStruct> vLRItemFormulaExpansionStruct;
// typedef std::vector<LRItemTokenStruct> vLRItemTokenStruct;
typedef std::map<string, LRItemFormulaStruct> mapLRItemFormulaStruct;

struct LRItemStruct
{
    mapLRItemFormulaStruct formula_map;
};

// 構造体 式
struct LRItemFormulaStruct
{
    vLRItemFormulaExpansionStruct formula_expansion_vector;
};

// 構造体 展開した式
struct LRItemFormulaExpansionStruct
{
    vDeploymentTokenStruct token_vector;
    vstring lookAhead;
};

// // 構造体 token
// struct LRItemTokenStruct
// {
//     string token_str;
//     int label;
// };

// class LRItem
// {
// private:
// public:
//     LRItem()
//     {
//     }

// private:
// };

#endif