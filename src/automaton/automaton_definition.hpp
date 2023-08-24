
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

// typedef std::vector<DeploymentGroupStruct> vDeploymentGroupStruct;
struct DeploymentStruct;
struct DeploymentFormulaStruct;
struct DeploymentFormulaExpansionStruct;
struct DeploymentTokenStruct;
typedef std::vector<DeploymentStruct> vDeploymentStruct;
typedef std::vector<DeploymentFormulaStruct> vDeploymentFormulaStruct;
typedef std::vector<DeploymentFormulaExpansionStruct> vDeploymentFormulaExpansionStruct;
typedef std::vector<DeploymentTokenStruct> vDeploymentTokenStruct;

struct DeploymentStruct
{
    vDeploymentFormulaStruct formula_vector;
    vDeploymentStruct children;
};

// 構造体 式
struct DeploymentFormulaStruct
{
    vDeploymentFormulaExpansionStruct formula_expansion_vector;
};

// 構造体 展開した式
struct DeploymentFormulaExpansionStruct
{
    vDeploymentTokenStruct token_vector;
};

// 構造体 token
struct DeploymentTokenStruct
{
    int token_number;
};

// // 子要素構造体
// struct DeploymentGroupStruct
// {
//     DeploymentStruct item_set;
// };

// typedef std::vector<std::vector<DeploymentBnfRightStruct>> v2DeploymentBnfRightStruct;

// typedef std::vector<std::vector<DeploymentStruct>> v2DeploymentTree;
#endif