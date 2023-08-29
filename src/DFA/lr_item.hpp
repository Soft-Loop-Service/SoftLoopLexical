
#ifndef __LRITEM
#define __LRITEM
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

struct LRItemStruct;
struct LRItemFormulaStruct;
struct LRItemFormulaExpansionStruct;
typedef std::vector<LRItemStruct> vLRItemStruct;
typedef std::vector<LRItemFormulaStruct> vLRItemFormulaStruct;
typedef std::vector<LRItemFormulaExpansionStruct> vLRItemFormulaExpansionStruct;
typedef std::map<string, LRItemFormulaStruct> mapLRItemFormulaStruct;

struct LRItemStruct
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