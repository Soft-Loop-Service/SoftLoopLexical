
#ifndef __DFA_CALC
#define __DFA_CALC

#include "./../definition.hpp"
#include "./../symbol.hpp"
#include "./../BNF/bnf_struct.hpp"
#include "./../BNF/bnf_right.hpp"
#include "./../BNF/bnf_vector.hpp"
#include "./lr_item.hpp"

#include "./../item_set/item_set.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

class DfaNode;
typedef std::vector<DfaNode> vDfaNode;

class DfaNode
{
private:
    mapDeploymentFormulaStruct formula_map;
    LRItemStruct lr_set;

    vstring already_explored;
    int dot;
    string node_label;

public:
    string temporary_start_symbol = "<_S>";
    DfaNode(mapDeploymentFormulaStruct formula_map,  int dot)
    {
        this->formula_map = formula_map;
        this->dot = dot;
        this->lr_set;
    }

    void addRoot(){
        struct DeploymentTokenStruct new_token = {"<S>",is_id_NonterminalSymbolRight};
        struct LRItemFormulaExpansionStruct new_lr_formula_expansion;
        new_lr_formula_expansion.token_vector.push_back(new_token);
        new_lr_formula_expansion.lookAhead.push_back("$");
        LRItemFormulaStruct new_lr_formula;
        new_lr_formula.LR_formula_expansion_vector.push_back(new_lr_formula_expansion);
        lr_set.LR_formula_map[temporary_start_symbol] = new_lr_formula;
    }

    void nodeClosureExpansion(string search_key,string start_key)
    {
        vstring formula_map_keys = getMapKeyString(lr_set.LR_formula_map);
        recursionNodeClosureExpansion(search_key,start_key);

        vstring formula_map_keys_after = getMapKeyString(lr_set.LR_formula_map);

        for (int i = 0; i < formula_map_keys_after.size();i++){
            LRItemFormulaStruct t = lr_set.LR_formula_map[formula_map_keys_after[i]];
            printf("formula %s %ld %ld: ",formula_map_keys_after[i].c_str(),formula_map_keys_after.size(),t.LR_formula_expansion_vector.size());

            for (int j = 0; j< t.LR_formula_expansion_vector.size() ;j++){
                vDeploymentTokenStruct token_vector = t.LR_formula_expansion_vector[j].token_vector;
                for (int k = 0; k < token_vector.size() ; k++){
                    string ts = token_vector[k].token_str;

                    printf("%s ",ts.c_str());
                }
                printf(" - ");
            }
            printf("\n");
        }
    }

private:

    void getFirstCandidate(LRItemFormulaExpansionStruct lr_s){
            vDeploymentTokenStruct first_candidate = {};

            for (int j = dot; j < lr_s.token_vector.size() ; j++){
                DeploymentTokenStruct token = lr_s.token_vector[j];
                first_candidate.push_back(token);
                if(token.label == is_id_TerminalSymbol){
                    return;
                }
            }

    }

    /// @brief 
    /// @param search_key  展開したいキー
    /// @param parent_key  展開元
    void recursionNodeClosureExpansion(string search_key,string parent_key)
    {
        if (hasKeyMap(this->already_explored, search_key))
        {
            return;
        }
        already_explored.push_back(search_key);
        vDeploymentFormulaExpansionStruct current_formula_expansion_vector = formula_map[search_key].formula_expansion_vector;

        printf("search_key %s %ld\n",search_key.c_str(),current_formula_expansion_vector.size());

        // printf("current_formula_expansion_vector %ld\n",current_formula_expansion_vector.size());
        for (int i = 0; i < current_formula_expansion_vector.size();i++){
            struct LRItemFormulaExpansionStruct lr_s;
            lr_s.token_vector = current_formula_expansion_vector[i].token_vector;

            this->lr_set.LR_formula_map[search_key].LR_formula_expansion_vector.push_back(lr_s);

            for (int j = dot; j < lr_s.token_vector.size() ; j++){
                DeploymentTokenStruct token = lr_s.token_vector[j];
                printf("token %s\n",token.token_str.c_str());
                if(token.label == is_id_TerminalSymbol){
                    continue;
                }
                

                recursionNodeClosureExpansion(token.token_str,search_key);       
            }

        }
    }
};

#endif