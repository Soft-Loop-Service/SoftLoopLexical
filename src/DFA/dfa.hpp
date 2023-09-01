
#ifndef __DFA
#define __DFA

#include "./../definition.hpp"
#include "./../symbol.hpp"
#include "./../BNF/bnf_struct.hpp"
#include "./../BNF/bnf_right.hpp"

#include "./../item_set/item_set.hpp"
#include "./dfa_calc.hpp"
#include "./lr_item.hpp"
#include "./closure_expansion.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

int generateDFARoot(DFANode &root_dfa_node)
{
    root_dfa_node.node_label = "root";
    struct DeploymentTokenStruct token = {START_DFA_SYMBOL, is_id_NonterminalSymbolRight};
    struct DeploymentTokenStruct token_dollar = {"$", is_id_Dollar};
    struct LRItemFormulaExpansionStruct formula_expansion;
    formula_expansion.token_vector.push_back(token);
    formula_expansion.formula_expansion_label = -1;
    formula_expansion.lookAhead = {token_dollar};
    struct LRItemFormulaStruct formula;
    formula.LR_formula_expansion_vector.push_back(formula_expansion);
    root_dfa_node.lr_item.LR_formula_map[ROOT_DFA_SYMBOL] = formula;
}

vstring getNextLabelDFA(DFANode current_node, int dot)
{
    int index = dot - 1;
    vstring next_labels;
    mapLRItemFormulaStruct LR_formula_map = current_node.lr_item.LR_formula_map;

    vstring LR_formula_map_keys = getMapKeyString(LR_formula_map);

    for (int i = 0; i < LR_formula_map_keys.size(); i++)
    {
        LRItemFormulaStruct LR_formula = LR_formula_map[LR_formula_map_keys[i]];

        for (int j = 0; j < LR_formula.LR_formula_expansion_vector.size(); j++)
        {
            LRItemFormulaExpansionStruct LR_formula_expansion = LR_formula.LR_formula_expansion_vector[j];
            vDeploymentTokenStruct token_vector = LR_formula_expansion.token_vector;
            if (index >= token_vector.size())
            {
                continue;
            }
            DeploymentTokenStruct token = token_vector[index];

            if (hasKeyMap(next_labels, token.token_str) )
            {
                continue;
            }
            next_labels.push_back(token.token_str);
        }
    }
    return next_labels;
}

DFANode generateNewNodeDFA(DeploymentStruct &deployment_syntax, DFANode current_node, int dot, string next_label)
{
    struct DFANode new_node;
    new_node.node_label = next_label;
    // new_node.lr_item.
    int index = dot - 1;

    mapLRItemFormulaStruct LR_formula_map = current_node.lr_item.LR_formula_map;

    vstring LR_formula_map_keys = getMapKeyString(LR_formula_map);

    for (int i = 0; i < LR_formula_map_keys.size(); i++)
    {
        string key = LR_formula_map_keys[i];
        LRItemFormulaStruct LR_formula = LR_formula_map[key];

        for (int j = 0; j < LR_formula.LR_formula_expansion_vector.size(); j++)
        {
            LRItemFormulaExpansionStruct LR_formula_expansion = LR_formula.LR_formula_expansion_vector[j];
            vDeploymentTokenStruct token_vector = LR_formula_expansion.token_vector;
            if (index >= token_vector.size())
            {
                continue;
            }

            DeploymentTokenStruct token = token_vector[index];

            if (token.token_str != next_label)
            {
                continue;
            }

            new_node.lr_item.LR_formula_map[key].LR_formula_expansion_vector.push_back(LR_formula_expansion);
        }
    }
    return new_node;
}

int recursionDFA(DeploymentStruct &deployment_syntax, vDFANode &dfa_node_graph, int current_node_index, int dot)
{
    DFANode current_node = dfa_node_graph[current_node_index];
    vstring next_labels = getNextLabelDFA(current_node, dot);

    ClosureExpansion closure_expansion = ClosureExpansion(deployment_syntax, dot);

    for (int i = 0; i < next_labels.size(); i++)
    {
        string next_label = next_labels[i];

        DFANode new_node = generateNewNodeDFA(deployment_syntax, current_node, dot, next_label);
        closure_expansion.nodeClosureExpansion(new_node.lr_item);
        dfa_node_graph.push_back(new_node);
        int push_index = dfa_node_graph.size() - 1;

        dfa_node_graph[current_node_index].children_nodes[next_label] = push_index;

        recursionDFA(deployment_syntax, dfa_node_graph, push_index, dot + 1);
    }
}

void outputDFA(vDFANode dfa_node_graph)
{
    printf("outputDFA * * * * \n");

    for (int d = 0; d < dfa_node_graph.size(); d++)
    {
        DFANode node = dfa_node_graph[d];
        printf("受理 %d %6s ", d, node.node_label.c_str());

        vstring keys = getMapKeyString(node.children_nodes);
        for (int i = 0; i < node.children_nodes.size(); i++)
        {
            printf("( %s %d ) ", keys[i].c_str(), node.children_nodes[keys[i]]);
        }
        printf("\n");
    }

    printf("outputDFA ITEM * * * * \n");
}

vDFANode generateDFA(DeploymentStruct deployment_syntax)
{
    int dot = 0;
    DFANode root_dfa_node = DFANode();
    generateDFARoot(root_dfa_node);

    ClosureExpansion closure_expansion = ClosureExpansion(deployment_syntax, dot);
    closure_expansion.nodeClosureExpansion(root_dfa_node.lr_item, ROOT_DFA_SYMBOL);

    vDFANode dfa_node_graph = {};
    dfa_node_graph.push_back(root_dfa_node);

    recursionDFA(deployment_syntax, dfa_node_graph, 0, dot + 1);

    outputDFA(dfa_node_graph);

    printf("処理終了\n");

    return dfa_node_graph;
}

#endif