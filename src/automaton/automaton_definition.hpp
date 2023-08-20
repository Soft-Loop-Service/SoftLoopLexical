
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
struct ItemSetStruct
{
    vItemSetFormulaStruct formula;
    vItemSetGroupStruct children;
};

struct ItemSetFormulaStruct
{
    vItemSetFormulaExpansionStruct formula_expansion;
};
struct ItemSetFormulaExpansionStruct
{
    vItemSetTokenStruct token;
};
struct ItemSetTokenStruct
{
    int token_number;
}

struct ItemSetGroupStruct
{
    vItemSetFormulaStruct formula;
};

typedef std::vector<ItemSetFormulaStruct> vItemSetFormulaStruct;
typedef std::vector<ItemSetFormulaExpansionStruct> vItemSetFormulaExpansionStruct;
typedef std::vector<ItemSetTokenStruct> vItemSetTokenStruct;
typedef std::vector<ItemSetGroupStruct> vItemSetGroupStruct;
// typedef std::vector<std::vector<ItemSetBnfRightStruct>> v2ItemSetBnfRightStruct;

// typedef std::vector<std::vector<ItemSetStruct>> v2ItemSetTree;
#endif