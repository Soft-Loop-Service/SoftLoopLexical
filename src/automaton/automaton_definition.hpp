
#ifndef __AUTOMATON_DE
#define __AUTOMATON_DE

#include "./../definition.hpp"
#include "./automaton.hpp"

#define automaton_0or1 1      // ? 記号
#define automaton_asterisk 2  // * 記号
#define automaton_plus_sign 3 // + 記号

/*
bnf_right   : 3次元配列 上から順に 式：展開した式：式を構成するtoken
children    : 4次元配列 上から順に アイテム集合群：式：展開した式：式を構成するtoken
dot
*/

// typedef std::vector<ItemSetGroupStruct> vItemSetGroupStruct;
struct ItemSetStruct;
struct ItemSetFormulaStruct;
struct ItemSetFormulaExpansionStruct;
struct ItemSetTokenStruct;
typedef std::vector<ItemSetStruct> vItemSetStruct;
typedef std::vector<ItemSetFormulaStruct> vItemSetFormulaStruct;
typedef std::vector<ItemSetFormulaExpansionStruct> vItemSetFormulaExpansionStruct;
typedef std::vector<ItemSetTokenStruct> vItemSetTokenStruct;

struct ItemSetStruct
{
    vItemSetFormulaStruct formula_vector;
    vItemSetStruct children;
};

// 構造体 式
struct ItemSetFormulaStruct
{
    vItemSetFormulaExpansionStruct formula_expansion_vector;
};

// 構造体 展開した式
struct ItemSetFormulaExpansionStruct
{
    vItemSetTokenStruct token_vector;
};

// 構造体 token
struct ItemSetTokenStruct
{
    int token_number;
};

// // 子要素構造体
// struct ItemSetGroupStruct
// {
//     ItemSetStruct item_set;
// };

// typedef std::vector<std::vector<ItemSetBnfRightStruct>> v2ItemSetBnfRightStruct;

// typedef std::vector<std::vector<ItemSetStruct>> v2ItemSetTree;
#endif