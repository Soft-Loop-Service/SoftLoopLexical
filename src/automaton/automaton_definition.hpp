
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
typedef std::map<string, DeploymentFormulaStruct> mapDeploymentFormulaStruct;

struct DeploymentStruct
{
    mapDeploymentFormulaStruct formula_map;
    // vDeploymentStruct children;
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
    string token_str;
    int label;
};

// 左辺非末端記号とNUll集合であるかどうか
class FollowsSetClass
{
public:
    mapstrbool follows;
    DeploymentStruct deployment_syntax;
    vstring formula_map_keys;

    FollowsSetClass(DeploymentStruct deployment_syntax)
    {
        this->deployment_syntax = deployment_syntax;

        this->formula_map_keys = getMapKeyString(this->deployment_syntax.formula_map);
    }

    int findNullsSet()
    {
        int formula_map_size = this->deployment_syntax.formula_map.size();
        for (int i = 0; i < formula_map_size; i++)
        {
            string current_key = this->formula_map_keys[i];
            recursionNullSet(current_key);
        }
    }

private:
    void recursionNullSet(string current_key)
    {
        bool folllow_flag = true;

        if (hasKeyMap(this->formula_map_keys, current_key))
        {
            return;
        }

        vDeploymentFormulaExpansionStruct formula_expansion_vector = this->deployment_syntax.formula_map[current_key].formula_expansion_vector;
        int formula_expansion_vector_size = formula_expansion_vector.size();
        for (int j = 0; j < formula_expansion_vector_size; j++)
        {
            vDeploymentTokenStruct token_vector = formula_expansion_vector[j].token_vector;

            int token_vector_size = token_vector.size();

            if (token_vector_size == 0)
            {
                // NULLである
                continue;
            }
            int k = 0;
            // for (int k = 0; k < token_vector_size; k++)
            // {
            string token_str = token_vector[k].token_str;
            int label = token_vector[k].label;

            if (label == is_id_NonterminalSymbolRight)
            {
                recursionNullSet(token_str);
            }
            // }
        }

        this->follows[current_key] = folllow_flag;
    }
};

// // 子要素構造体
// struct DeploymentGroupStruct
// {
//     DeploymentStruct item_set;
// };

// typedef std::vector<std::vector<DeploymentBnfRightStruct>> v2DeploymentBnfRightStruct;

// typedef std::vector<std::vector<DeploymentStruct>> v2DeploymentTree;
#endif