

#ifndef __ITEMSET
#define __ITEMSET

#include "./../definition.hpp"
#include "./../debug.hpp"
#include "./../symbol.hpp"
#include "./../BNF/bnf_struct.hpp"
#include "./../BNF/bnf_right.hpp"
#include "./../BNF/bnf_vector.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

/*
bnf_right   : 3次元配列 上から順に 式：展開した式：式を構成するtoken
children    : 4次元配列 上から順に アイテム集合群：式：展開した式：式を構成するtoken
dot
*/

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

        if (hasKeyMap(this->null_set, current_key))
        {
            return true;
        }
        already_explored.push_back(current_key);
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

            if (token_vector_size == 0)
            {
                null_set.push_back(current_key);
                return true;
            }

            // printf("token_vector_size %s %d\n", current_key.c_str(), token_vector_size);

            for (int k = 0; k < token_vector_size; k++)
            {
                string token_str = token_vector[k].token_str;
                int label = token_vector[k].label;

                // あわせて左再帰の除去

                if (current_key == token_str)
                {
                    continue;
                }

                if (label == is_id_NonterminalSymbolRight)
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
    vstring already_explored;

public:
    FirstSetClass(DeploymentStruct deployment_syntax, vstring null_set)
    {
        this->deployment_syntax = deployment_syntax;
        this->formula_map_keys = getMapKeyString(this->deployment_syntax.formula_map);
        this->null_set = null_set;
    }
    mp_s_vstring findFirstSet(vDeploymentTokenStruct request_token_vector)
    {
        first_set = {};
        first_set["$"].push_back("$");
        // int formula_map_size = this->deployment_syntax.formula_map.size();
        int request_token_vector_size = request_token_vector.size();
        for (int i = 0; i < request_token_vector_size; i++)
        {
            string current_key = request_token_vector[i].token_str;
            int current_label = request_token_vector[i].label;

            if(current_label == is_id_TerminalSymbol){
                first_set[current_key].push_back(current_key);
                break;
            }
            
            recursionFirstsSet(current_key);

            if (!hasKeyMap(getMapKeyString(this->first_set), current_key))
            {
                break;
            }
        }


        for (int i = 0; i < first_set.size(); i++)
        {
            printf("first_set output request %s\n", getMapKeyString(first_set)[i].c_str());
            output_vector("first_set", first_set[getMapKeyString(first_set)[i]]);
        }

        return first_set;
    }

    mp_s_vstring findFirstSet()
    {
        first_set = {};
        first_set["$"].push_back("$");
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
        if (hasKeyMap(this->already_explored, current_key))
        {
            return;
        }

        if (hasKeyMap(getMapKeyString(this->first_set), current_key))
        {
            return;
        }
        already_explored.push_back(current_key);
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
                int recursion_flag;
                do
                {
                    recursion_flag = false;
                    string token_str = token_vector[k].token_str;
                    int label = token_vector[k].label;

                    if (label == is_id_NonterminalSymbolRight)
                    {

                        // 左再帰の除去
                        if (current_key == token_str)
                        {
                            recursion_flag = true;
                        }
                        else
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
                    }
                    else if (label == is_id_TerminalSymbol)
                    {

                        first_set[current_key].push_back(token_vector[k].token_str);
                    }
                    k++;

                } while (k < token_vector_size && (hasKeyMap(this->null_set, token_vector[k - 1].token_str) || recursion_flag));
            }
        }
    }
};

class FollowSetClass
{
private:
    DeploymentStruct deployment_syntax;
    mp_s_vstring first_set;
    vstring null_set;
    mp_s_vstring follow_set;
    vstring formula_map_keys;
    vstring already_explored;

public:
    FollowSetClass(DeploymentStruct deployment_syntax, vstring null_set, mp_s_vstring first_set)
    {
        this->deployment_syntax = deployment_syntax;
        this->formula_map_keys = getMapKeyString(this->deployment_syntax.formula_map);
        this->null_set = null_set;
        this->first_set = first_set;
    }
    mp_s_vstring findFolllowSet()
    {
        follow_set["<S>"].push_back("$");
        int formula_map_size = this->deployment_syntax.formula_map.size();
        for (int s = 0; s < formula_map_size; s++)
        {
            string search_key = this->formula_map_keys[s];
            recursionFollowSet(search_key);
        }

        for (int i = 0; i < follow_set.size(); i++)
        {
            printf("follow_set output %s\n", getMapKeyString(follow_set)[i].c_str());
            output_vector("follow_set", follow_set[getMapKeyString(follow_set)[i]]);
        }
        return follow_set;
    }

    void recursionFollowSet(string search_key)
    {
        if (hasKeyMap(this->already_explored, search_key))
        {
            return;
        }
        already_explored.push_back(search_key);

        printf("recursionFollowSet %s\n", search_key.c_str());

        int formula_map_size = this->deployment_syntax.formula_map.size();
        for (int i = 0; i < formula_map_size; i++)
        {
            string current_key = this->formula_map_keys[i];
            vDeploymentFormulaExpansionStruct formula_expansion_vector = this->deployment_syntax.formula_map[current_key].formula_expansion_vector;
            int formula_expansion_vector_size = formula_expansion_vector.size();
            for (int j = 0; j < formula_expansion_vector_size; j++)
            {
                vDeploymentTokenStruct token_vector = formula_expansion_vector[j].token_vector;

                int token_vector_size = token_vector.size();
                for (int k = 0; k < token_vector_size; k++)
                {
                    if (search_key == token_vector[k].token_str)
                    {
                        // printf("対象との一致 %s\n", search_key.c_str());
                        bool flag = true;
                        int n = k;
                        while (flag && n < token_vector_size)
                        {

                            if (n == token_vector_size - 1) // 一番最後であるとき
                            {
                                printf("token終端\n");
                                findNextNull(search_key, current_key);
                                flag = false;
                            }
                            else // 最後以外の時
                            {
                                string next_key = token_vector[n + 1].token_str;
                                int next_label = token_vector[n + 1].label;

                                if (next_label == is_id_TerminalSymbol)
                                {
                                    if (!hasKeyMap(this->follow_set[search_key], next_key))
                                    {
                                        this->follow_set[search_key].push_back(next_key);
                                    }
                                    flag = false;
                                }

                                flag = findNext(search_key, current_key, next_key);
                                if (flag)
                                {
                                    findNextNull(search_key, current_key);
                                }
                            }

                            n++;
                        }
                    }
                }
            }
        }
    }

private: /// @brief
    /// @return nullの可能性があるか否か
    bool findNext(string search_key, string current_key, string next_key)
    {
        printf("findNext %s : %s -> %s\n", current_key.c_str(), search_key.c_str(), next_key.c_str());

        vstring next_first_set = first_set[next_key];

        for (int i = 0; i < next_first_set.size(); i++)
        {
            if (!hasKeyMap(this->follow_set[search_key], next_first_set[i]))
            {
                this->follow_set[search_key].push_back(next_first_set[i]);
            }
        }
        bool isNull = hasKeyMap(this->null_set, next_key);
        return isNull;
    }

    // Nullの可能性があるとき
    bool findNextNull(string search_key, string current_key)
    {
        recursionFollowSet(current_key);

        printf("findNextNull %s -> %s\n", current_key.c_str(), search_key.c_str());

        for (int i = 0; i < follow_set[current_key].size(); i++)
        {
            printf("findNextNull push %s - %s %s\n", search_key.c_str(), current_key.c_str(), follow_set[current_key][i].c_str());
            if (!hasKeyMap(this->follow_set[search_key], follow_set[current_key][i]))
            {

                this->follow_set[search_key].push_back(follow_set[current_key][i]);
            }
        }
    }
};

#endif