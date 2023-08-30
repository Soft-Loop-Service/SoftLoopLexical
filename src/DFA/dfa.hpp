
#ifndef __DFA
#define __DFA

#include "./../definition.hpp"
#include "./../symbol.hpp"
#include "./../BNF/bnf_struct.hpp"
#include "./../BNF/bnf_right.hpp"

#include "./../item_set/item_set.hpp"
#include "./dfa_calc.hpp"
#include "./lr_item.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

vDeploymentTokenStruct getNextLabelDFA(DFANode &current_node, int dot)
{
    int index = dot - 1;
    vDeploymentTokenStruct labels;

    vstring LR_formula_map_keys = getMapKeyString(current_node.LR_formula_map);
    int LR_formula_map_size = current_node.LR_formula_map.size();

    for (int i = 0; i < LR_formula_map_size; i++)
    {
        string key = LR_formula_map_keys[i];
        vLRItemFormulaExpansionStruct LR_formula_expansion_vector = current_node.LR_formula_map[key].LR_formula_expansion_vector;

        for (int j = 0; j < LR_formula_expansion_vector.size(); j++)
        {
            vDeploymentTokenStruct token_vector = LR_formula_expansion_vector[j].token_vector;

            if (index >= token_vector.size())
            {
                continue;
            }
            DeploymentTokenStruct token = token_vector[index];
            printf("getNextLabelDFA %s\n", token.token_str.c_str());

            int label_index = -1;

            for (int k = 0; k < labels.size(); k++)
            {
                if (labels[k].token_str == token.token_str)
                {
                    label_index = k;
                    break;
                }
            }
            if (label_index == -1)
            {
                labels.push_back(token);
                label_index = labels.size() - 1;
            }
        }
    }
    return labels;
}

DFANode getNewLRItem(DFANode current_node, string search_key, int dot)
{
    struct DFANode new_node;
    new_node.node_label = search_key;

    int index = dot - 1;
    vstring LR_formula_map_keys = getMapKeyString(current_node.LR_formula_map);
    int LR_formula_map_size = current_node.LR_formula_map.size();

    for (int i = 0; i < LR_formula_map_size; i++)
    {
        string key = LR_formula_map_keys[i];
        vLRItemFormulaExpansionStruct LR_formula_expansion_vector = current_node.LR_formula_map[key].LR_formula_expansion_vector;

        for (int j = 0; j < LR_formula_expansion_vector.size(); j++)
        {
            vDeploymentTokenStruct token_vector = LR_formula_expansion_vector[j].token_vector;
            if (search_key != token_vector[index].token_str)
            {
                continue;
            }
            new_node.LR_formula_map[key].LR_formula_expansion_vector.push_back(LR_formula_expansion_vector[j]);
        }
    }

    return new_node;
}
int addNewLRItem(vDFANode &dfa_nodes, DFANode &current_node, DFANode new_node)
{
    printf("子要素の登録 a %s / %s / %d\n", current_node.node_label.c_str(), new_node.node_label.c_str());
    dfa_nodes.push_back(new_node);
    // int add_index = dfa_nodes.size() - 1;
    // current_node.children_nodes[new_node.node_label] = add_index;
    printf("子要素の登録 b %s / %s / %d\n", current_node.node_label.c_str(), new_node.node_label.c_str());
}

void recursionDFA(DeploymentStruct &deployment_syntax, vDFANode &dfa_nodes, DFANode &current_node, int dot)
{
    vDeploymentTokenStruct next_nodes = getNextLabelDFA(current_node, dot);

    for (int n = 0; n < next_nodes.size(); n++)
    {
        string next_node_token = next_nodes[n].token_str;
        DFANode new_node = getNewLRItem(current_node, next_node_token, dot);

        ClosureExpansionLRItem closure_expansion_LR_item = ClosureExpansionLRItem(new_node, deployment_syntax.formula_map, dot);
        LRItemStruct lr_item = closure_expansion_LR_item.nodeClosureExpansion();

        new_node.LR_formula_map = lr_item.LR_formula_map;

        if (true) // ここに既に同じ要素があるかを探索する処理を書く
        {
        }
        addNewLRItem(dfa_nodes, current_node, new_node);
    }
    // ClosureExpansionLRItem closure_expansion_LR_item = ClosureExpansionLRItem(parent_node, deployment_syntax.formula_map, dot);
    // // LRItemStruct lr_item = closure_expansion_LR_item.nodeClosureExpansion();
    // closure_expansion_LR_item.debug();
}

int outputDFA(vDFANode dfa_nodes)
{
    for (int i = 0; i < dfa_nodes.size(); i++)
    {

        DFANode cdn = dfa_nodes[i];
        printf("%2d 受理 %5s size %ld:  ", i, cdn.node_label.c_str(), cdn.children_nodes.size());
        vstring keys = getMapKeyString(cdn.children_nodes);
        for (int j = 0; j < cdn.children_nodes.size(); j++)
        {
            printf("%d ", cdn.children_nodes[keys[j]]);
        }
        printf("\n");
    }
}

int generateDFA(DeploymentStruct deployment_syntax)
{
    // ConstructionLRItem dfa_node_array = {};
    int dot = 0;

    ClosureExpansionLRItem closure_expansion_LR_item = ClosureExpansionLRItem(deployment_syntax.formula_map, dot);
    closure_expansion_LR_item.addRoot();
    LRItemStruct lr_item = closure_expansion_LR_item.nodeClosureExpansion("<S>");
    DFANode dfa_root_node;
    dfa_root_node.node_label = closure_expansion_LR_item.temporary_start_symbol;
    dfa_root_node.LR_formula_map = lr_item.LR_formula_map;
    closure_expansion_LR_item.debug();

    vDFANode dfa_nodes = {};
    dfa_nodes.push_back(dfa_root_node);
    recursionDFA(deployment_syntax, dfa_nodes, dfa_nodes[0], dot + 1);

    // recursionDFA(deployment_syntax, dfa_nodes, dfa_nodes[0], dot + 1);
    outputDFA(dfa_nodes);
}

#endif