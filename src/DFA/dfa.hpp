
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

bool isDfaEqual(DFANode a_node, DFANode b_node)
{
    // バグの温床になるのでブランチ閉
    mapLRItemFormulaStruct a_LR_formula_map = a_node.lr_item.LR_formula_map;
    mapLRItemFormulaStruct b_LR_formula_map = b_node.lr_item.LR_formula_map;

    vstring a_LR_formula_map_keys = getMapKeyString(a_LR_formula_map);
    vstring b_LR_formula_map_keys = getMapKeyString(b_LR_formula_map);

    if (a_LR_formula_map_keys.size() != b_LR_formula_map_keys.size())
    {
        return false;
    }

    for (int i = 0; i < a_LR_formula_map_keys.size(); i++)
    {
        LRItemFormulaStruct a_LR_formula = a_LR_formula_map[a_LR_formula_map_keys[i]];
        LRItemFormulaStruct b_LR_formula = b_LR_formula_map[b_LR_formula_map_keys[i]];

        if (a_LR_formula.LR_formula_expansion_vector.size() != b_LR_formula.LR_formula_expansion_vector.size())
        {
            return false;
        }

        for (int j = 0; j < a_LR_formula.LR_formula_expansion_vector.size(); j++)
        {
            LRItemFormulaExpansionStruct a_LR_formula_expansion = a_LR_formula.LR_formula_expansion_vector[j];
            LRItemFormulaExpansionStruct b_LR_formula_expansion = b_LR_formula.LR_formula_expansion_vector[j];
            vDeploymentTokenStruct a_token_vector = a_LR_formula_expansion.token_vector;
            vDeploymentTokenStruct b_token_vector = b_LR_formula_expansion.token_vector;
            vDeploymentTokenStruct a_lookAhead = a_LR_formula_expansion.lookAhead;
            vDeploymentTokenStruct b_lookAhead = b_LR_formula_expansion.lookAhead;

            if (a_token_vector.size() != b_token_vector.size())
            {
                return false;
            }
            if (a_lookAhead.size() != b_lookAhead.size())
            {
                return false;
            }

            int t_count = 0;
            for (int k = 0; k < a_token_vector.size(); k++)
            {
                for (int n = 0; n < b_token_vector.size(); n++)
                {
                    if (a_token_vector[k].token_str == b_token_vector[n].token_str)
                    {
                        t_count++;
                        break;
                    }
                }
            }
            if (t_count != a_token_vector.size())
            {
                return false;
            }

            int l_count = 0;
            for (int k = 0; k < a_lookAhead.size(); k++)
            {
                for (int n = 0; n < b_lookAhead.size(); n++)
                {
                    if (a_lookAhead[k].token_str == b_lookAhead[n].token_str)
                    {
                        l_count++;
                        break;
                    }
                }
            }
            if (l_count != a_lookAhead.size())
            {
                return false;
            }
        }
    }
    return true;
}

int generateDFARoot(DFANode &root_dfa_node)
{
    root_dfa_node.node_label = "root";
    struct DeploymentTokenStruct token = {START_DFA_SYMBOL, is_id_NonterminalSymbolRight};
    struct DeploymentTokenStruct token_dollar = {DOLLAR, is_id_Dollar};
    struct LRItemFormulaExpansionStruct formula_expansion;
    formula_expansion.token_vector.push_back(token);
    formula_expansion.formula_expansion_label = -1;
    formula_expansion.lookAhead = {token_dollar};
    formula_expansion.dot = 0;
    struct LRItemFormulaStruct formula;
    formula.LR_formula_expansion_vector.push_back(formula_expansion);
    root_dfa_node.lr_item.LR_formula_map[ROOT_DFA_SYMBOL] = formula;
}

vstring getNextLabelDFA(DFANode current_node)
{

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
            // int dot = LR_formula_expansion.dot;
            int index = LR_formula_expansion.dot;

            if (index >= token_vector.size())
            {
                continue;
            }
            DeploymentTokenStruct token = token_vector[index];

            if (hasKeyMap(next_labels, token.token_str))
            {
                continue;
            }
            next_labels.push_back(token.token_str);
        }
    }
    return next_labels;
}

DFANode generateNewNodeDFA(DeploymentStruct &deployment_syntax, DFANode current_node, string next_label)
{
    struct DFANode new_node;
    new_node.node_label = next_label;
    // new_node.lr_item.

    mapLRItemFormulaStruct LR_formula_map = current_node.lr_item.LR_formula_map;

    vstring LR_formula_map_keys = getMapKeyString(LR_formula_map);

    for (int i = 0; i < LR_formula_map_keys.size(); i++)
    {
        string key = LR_formula_map_keys[i];
        LRItemFormulaStruct LR_formula = LR_formula_map[key];

        for (int j = 0; j < LR_formula.LR_formula_expansion_vector.size(); j++)
        {
            LRItemFormulaExpansionStruct LR_formula_expansion = LR_formula.LR_formula_expansion_vector[j];
            int index = LR_formula_expansion.dot;
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
            LR_formula_expansion.dot++;
            new_node.lr_item.LR_formula_map[key].LR_formula_expansion_vector.push_back(LR_formula_expansion);
        }
    }
    return new_node;
}

int recursionDFA(DeploymentStruct &deployment_syntax, vDFANode &dfa_node_graph, int current_node_index)
{
    DFANode current_node = dfa_node_graph[current_node_index];
    vstring next_labels = getNextLabelDFA(current_node);

    ClosureExpansion closure_expansion = ClosureExpansion(deployment_syntax);

    for (int i = 0; i < next_labels.size(); i++)
    {
        string next_label = next_labels[i];

        DFANode new_node = generateNewNodeDFA(deployment_syntax, current_node, next_label);

        closure_expansion.nodeClosureExpansion(new_node.lr_item);

        int flag = -1;
        for (int j = 0; j < dfa_node_graph.size(); j++)
        {
            if (isDfaEqual(new_node, dfa_node_graph[j]))
            {
                flag = j;
                break;
            }
        }
        if (flag != -1)
        {
            dfa_node_graph[current_node_index].children_nodes[next_label] = flag;
            continue;
        }
        dfa_node_graph.push_back(new_node);
        int push_index = dfa_node_graph.size() - 1;
        dfa_node_graph[current_node_index].children_nodes[next_label] = push_index;

        recursionDFA(deployment_syntax, dfa_node_graph, push_index);
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
    for (int d = 0; d < dfa_node_graph.size(); d++)
    {
        DFANode node = dfa_node_graph[d];
        // printf("受理 %d %6s ", d, node.node_label.c_str());

        vstring keys = getMapKeyString(node.lr_item.LR_formula_map);
        for (int i = 0; i < keys.size(); i++)
        {
            vLRItemFormulaExpansionStruct LR_formula_expansion_vector = node.lr_item.LR_formula_map[keys[i]].LR_formula_expansion_vector;

            for (int j = 0; j < LR_formula_expansion_vector.size(); j++)
            {
                vDeploymentTokenStruct token_vector = LR_formula_expansion_vector[j].token_vector;
                vDeploymentTokenStruct lookAhead = LR_formula_expansion_vector[j].lookAhead;

                printf("%d %d %d dot : %d ITEM群 : %s ::= ", d, i, j, LR_formula_expansion_vector[j].dot, keys[i].c_str());
                for (int k = 0; k < token_vector.size(); k++)
                {
                    printf("%s , ", token_vector[k].token_str.c_str());
                }
                printf("先読み記号 : ");
                for (int k = 0; k < lookAhead.size(); k++)
                {
                    printf("%s ,  ", lookAhead[k].token_str.c_str());
                }
                printf("\n");
            }
        }
    }
}

vDFANode generateDFA(DeploymentStruct deployment_syntax)
{
    DFANode root_dfa_node = DFANode();
    generateDFARoot(root_dfa_node);

    ClosureExpansion closure_expansion = ClosureExpansion(deployment_syntax);
    closure_expansion.nodeClosureExpansion(root_dfa_node.lr_item, ROOT_DFA_SYMBOL);

    vDFANode dfa_node_graph = {};
    dfa_node_graph.push_back(root_dfa_node);

    recursionDFA(deployment_syntax, dfa_node_graph, 0);

    outputDFA(dfa_node_graph);

    printf("処理終了\n");

    return dfa_node_graph;
}

#endif