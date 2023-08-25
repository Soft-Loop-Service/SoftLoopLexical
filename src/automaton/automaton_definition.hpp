
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
class NullSetClass
{
public:
    NullSetClass(DeploymentStruct deployment_syntax)
    {
        this->deployment_syntax = deployment_syntax;
        this->formula_map_keys = getMapKeyString(this->deployment_syntax.formula_map);
    }

    vstring findNullsSet()
    {
        int formula_map_size = this->deployment_syntax.formula_map.size();
        printf("formula_map_size %d\n", formula_map_size);
        for (int i = 0; i < formula_map_size; i++)
        {
            string current_key = this->formula_map_keys[i];
            recursionNullSet(current_key);
        }
        output_vector("null_set", null_set);
        return null_set;
    }

private:
    vstring null_set;
    DeploymentStruct deployment_syntax;
    vstring formula_map_keys;
    vstring already_explored;

    bool recursionNullSet(string current_key)
    {

        if (hasKeyMap(this->already_explored, current_key))
        {
            if (hasKeyMap(this->null_set, current_key))
            {
                return true;
            }
            return false;
        }

        already_explored.push_back(current_key);

        if (hasKeyMap(this->null_set, current_key))
        {
            return true;
        }

        vDeploymentFormulaExpansionStruct formula_expansion_vector = this->deployment_syntax.formula_map[current_key].formula_expansion_vector;
        int formula_expansion_vector_size = formula_expansion_vector.size();

        // printf("recursionNullSet %s %d\n", current_key.c_str(), formula_expansion_vector_size);

        if (formula_expansion_vector_size == 0)
        {
            // NULLである
            null_set.push_back(current_key);
            // printf("null push a %s %d\n", current_key.c_str(), formula_expansion_vector_size);
            return true;
        }

        for (int j = 0; j < formula_expansion_vector_size; j++)
        {
            printf("formula_expansion_vector\n");
            int null_count = 0;
            vDeploymentTokenStruct token_vector = formula_expansion_vector[j].token_vector;

            int token_vector_size = token_vector.size();

            // printf("token_vector_size %s %d\n", current_key.c_str(), token_vector_size);

            for (int k = 0; k < token_vector_size; k++)
            {
                string token_str = token_vector[k].token_str;
                int label = token_vector[k].label;

                // あわせて左再帰の除去
                if (label == is_id_NonterminalSymbolRight && current_key != token_str)
                {
                    printf("    探索 %s -> %s\n", current_key.c_str(), token_str.c_str());
                    bool result = recursionNullSet(token_str);
                    if (result)
                    {
                        null_count++;
                        printf("    加算\n");
                    }

                    printf("    結果 %s -> %s %d %d\n", current_key.c_str(), token_str.c_str(), result, null_count);
                }

                // }
            }
            printf("判定 %s %d %d\n", current_key.c_str(), null_count, token_vector_size);
            // printf("null_count == token_vector_size %s %d %d %d\n", current_key.c_str(), null_count, token_vector_size, formula_expansion_vector_size);
            if (null_count == token_vector_size)
            {
                printf("    登録 %s\n", current_key.c_str());
                null_set.push_back(current_key);
                // printf("null push b %s %d\n", current_key.c_str(), token_vector_size);
                return true;
            }

            // this->null_set[current_key] = null_flag;
        }
        return false;
    }
};

class FirstSetClass
{
private:
    DeploymentStruct deployment_syntax;
    vstring null_set;
    mp_s_vstring first_set;
    vstring formula_map_keys;

public:
    FirstSetClass(DeploymentStruct deployment_syntax, vstring null_set)
    {
        this->deployment_syntax = deployment_syntax;
        this->formula_map_keys = getMapKeyString(this->deployment_syntax.formula_map);
        this->null_set = null_set;
    }

    mp_s_vstring findFirstSet()
    {
        int formula_map_size = this->deployment_syntax.formula_map.size();
        for (int i = 0; i < formula_map_size; i++)
        {
            string current_key = this->formula_map_keys[i];
            recursionFirstsSet(current_key);
        }

        for (int i = 0; i < first_set.size(); i++)
        {
            printf("first_set output %s\n", getMapKeyString(first_set)[i].c_str());
            output_vector("first_set", first_set[getMapKeyString(first_set)[i]]);
        }
        //
        return first_set;
    }

    void recursionFirstsSet(string current_key)
    {
        if (hasKeyMap(getMapKeyString(this->first_set), current_key))
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
            else
            {
                int k = 0;
                do
                {

                    string token_str = token_vector[k].token_str;
                    int label = token_vector[k].label;
                    if (label == is_id_NonterminalSymbolRight && current_key != token_str)
                    {
                        recursionFirstsSet(token_str);

                        for (int fc = 0; fc < first_set[token_str].size(); fc++)
                        {
                            string fc_element = first_set[token_str][fc];
                            if (!hasKeyMap(first_set[current_key], fc_element))
                            {
                                first_set[current_key].push_back(fc_element);
                            }
                        }
                    }
                    else if (label == is_id_TerminalSymbol)
                    {
                        first_set[current_key].push_back(token_vector[k].token_str);
                    }
                    k++;
                } while (k < token_vector_size && hasKeyMap(this->null_set, token_vector[k - 1].token_str));
            }
        }
    }
};

class FollowSetClass
{
private:
    DeploymentStruct deployment_syntax;
    vstring first_set;
    vstring null_set;
    vstring formula_map_keys;

public:
    mapstr follow_set;
    FollowSetClass(DeploymentStruct deployment_syntax, vstring null_set, vstring first_set)
    {
        this->deployment_syntax = deployment_syntax;
        this->formula_map_keys = getMapKeyString(this->deployment_syntax.formula_map);
        this->null_set = null_set;
    }
    vstring findFolllowSet()
    {
        int formula_map_size = this->deployment_syntax.formula_map.size();
        for (int i = 0; i < formula_map_size; i++)
        {
            string current_key = this->formula_map_keys[i];
            recursionFollowSet(current_key);
        }
        return first_set;
    }
    void recursionFollowSet(string current_key)
    {
        vDeploymentFormulaExpansionStruct formula_expansion_vector = this->deployment_syntax.formula_map[current_key].formula_expansion_vector;
        int formula_expansion_vector_size = formula_expansion_vector.size();
        for (int j = 0; j < formula_expansion_vector_size; j++)
        {
            vDeploymentTokenStruct token_vector = formula_expansion_vector[j].token_vector;

            int token_vector_size = token_vector.size();

            string token_str_0 = token_vector[0].token_str;
            int label_0 = token_vector[0].label;

            if (token_str_0 == "<S>")
            {
                follow_set[token_str_0] = "$";
            }
        }
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