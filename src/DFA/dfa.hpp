
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

    return index;
}

quint constructionRecursionDFA(vLRItemStruct &dfa_nodes, LRItemStruct &parent_node, int dot)
{

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
            LRItemStruct *child_node_p;
            child_node_p = &(dfa_nodes[child_node_index]);
            child_node_p->LR_formula_map[formula_key].LR_formula_expansion_vector.push_back(parent_lr_formula_expansion);
            child_node_p->node_label = label_token_str;

            next_que.push(child_node_index);
            // conveyNodeDFA
        }
    }
    return next_que;
}

void removeDuplicatesDFA(DeploymentStruct &deployment_syntax, vLRItemStruct &dfa_nodes, int target, int duplicate)
{
    printf("削除対象 %d %d\n", target, duplicate);
}

void hadDuplicatesDFA(DeploymentStruct &deployment_syntax, vLRItemStruct &dfa_nodes, quint que)
{
    int que_size = que.size();
    for (int i = 0; i < que_size; i++)
    {
        int f = que.front();
        LRItemStruct *node_p = &dfa_nodes[f];
        que.pop();

        for (int j = 0; j <= f; j++)
        {
            if (j >= dfa_nodes.size())
            {
                continue;
            }
            int a_size = node_p->has_formula_expansion_label.size();
            int b_size = dfa_nodes[j].has_formula_expansion_label.size();
            if (a_size != b_size && a_size == 0)
            {
                continue;
            }
            for (int k = 0; k < a_size; k++)
            {
                if (node_p->has_formula_expansion_label[k] != dfa_nodes[j].has_formula_expansion_label[k])
                {
                    continue;
                }
            }
            removeDuplicatesDFA(deployment_syntax, dfa_nodes, f, j);
        }
    }
}

void recursionDFA(DeploymentStruct &deployment_syntax, vLRItemStruct &dfa_nodes, LRItemStruct &parent_node, int dot)
{
    printf("recursionDFA dot : %d\n", dot);
    quint que = constructionRecursionDFA(dfa_nodes, parent_node, dot);

    int que_size = que.size();
    // hadDuplicatesDFA(deployment_syntax, dfa_nodes, que);

    for (int i = 0; i < que_size; i++)
    {
        int f = que.front();
        LRItemStruct *node_p = &dfa_nodes[f];
        que.pop();

        ClosureExpansionLRItem closure_expansion_LR_item = ClosureExpansionLRItem(*node_p, deployment_syntax.formula_map, dot);
        LRItemStruct closure_lr_item = closure_expansion_LR_item.nodeClosureExpansion();
        // closure_lr_item.node_label;
        printf("label : %s ", closure_lr_item.node_label.c_str());
        for (int c = 0; c < closure_lr_item.has_formula_expansion_label.size(); c++)
        {
            printf("%d ", closure_lr_item.has_formula_expansion_label[c]);
        }
        printf("\n");

        // // closure_expansion_LR_item.debug();
        dfa_nodes[f] = closure_lr_item;
        recursionDFA(deployment_syntax, dfa_nodes, dfa_nodes[f], dot + 1);
    }
}

int outputDFA(vLRItemStruct dfa_nodes)
{
    for (int i = 0; i < dfa_nodes.size(); i++)
    {

        LRItemStruct cdn = dfa_nodes[i];
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
    lr_item.node_label = closure_expansion_LR_item.temporary_start_symbol;
    closure_expansion_LR_item.debug();

    vLRItemStruct dfa_nodes;

    dfa_nodes.push_back(lr_item);
    recursionDFA(deployment_syntax, dfa_nodes, dfa_nodes[0], dot + 1);
    outputDFA(dfa_nodes);
}

#endif