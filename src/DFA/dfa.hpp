
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

int newNodeDFA(vLRItemStruct &dfa_nodes, LRItemStruct &parent_node, string token_str)
{
    struct LRItemStruct new_node;
    dfa_nodes.push_back(new_node);
    int index = dfa_nodes.size() - 1;
    parent_node.children_nodes[token_str] = index;
    printf("recursionDFA %s %d\n", token_str.c_str(), index);
    return index;
}

quint constructionRecursionDFA(vLRItemStruct &dfa_nodes, LRItemStruct &parent_node, int dot)
{
    printf("dot sta %d\n", dot);
    quint next_que;

    vstring formula_map_keys = getMapKeyString(parent_node.LR_formula_map);
    for (int i = 0; i < formula_map_keys.size(); i++)
    {
        string formula_key = formula_map_keys[i];
        LRItemFormulaStruct lr_formula = parent_node.LR_formula_map[formula_key];

        for (int j = 0; j < lr_formula.LR_formula_expansion_vector.size(); j++)
        {
            LRItemFormulaExpansionStruct parent_lr_formula_expansion = lr_formula.LR_formula_expansion_vector[j];
            vDeploymentTokenStruct parent_token_vector = parent_lr_formula_expansion.token_vector;

            if (dot > parent_token_vector.size())
            {
                continue;
            }

            string label_token_str = parent_token_vector[dot - 1].token_str;

            int child_node_index = hasKeyMap(getMapKeyString(parent_node.children_nodes), label_token_str) ? parent_node.children_nodes[label_token_str] : newNodeDFA(dfa_nodes, parent_node, label_token_str);
            LRItemStruct *child_node_p = &(dfa_nodes[child_node_index]);
            child_node_p->LR_formula_map[formula_key].LR_formula_expansion_vector.push_back(parent_lr_formula_expansion);
            next_que.push(child_node_index);
            // conveyNodeDFA
        }
    }
    printf("dot end %d\n", dot);
    return next_que;
}

void recursionDFA(vLRItemStruct &dfa_nodes, LRItemStruct &parent_node, int dot)
{
    quint que = constructionRecursionDFA(dfa_nodes, parent_node, dot);

    int que_size = que.size();

    for (int i = 0; i < que_size; i++)
    {
        int f = que.front();
        LRItemStruct node = dfa_nodes[f];
        que.pop();
        recursionDFA(dfa_nodes, node, dot + 1);
    }
}

int generateDFA(DeploymentStruct deployment_syntax)
{
    // ConstructionLRItem dfa_node_array = {};
    int dot = 0;

    ClosureExpansionLRItem closure_expansion_LR_item = ClosureExpansionLRItem(deployment_syntax.formula_map, dot);
    closure_expansion_LR_item.addRoot();
    LRItemStruct lr_item = closure_expansion_LR_item.nodeClosureExpansion("<S>");
    closure_expansion_LR_item.debug();

    vLRItemStruct dfa_nodes;
    dfa_nodes.push_back(lr_item);
    recursionDFA(dfa_nodes, lr_item, dot + 1);
}

#endif