
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "./softj.hpp"

namespace LanguageSpecifications
{
    namespace SoftjLanguage
    {

        void Softj::preparationValueEnumeration(int node_index, vValueEnumeration &args_type)
        {
            Syntactic::SyntacticTreeNode node = getTreeNode(node_index);

            if (node.parent_token == "<value_name>")
            {
                struct ValueEnumeration ve = {"unsettled", node_index, node.token};
                args_type.push_back(ve);
                printf("preparationValueEnumeration %s %d\n", ve.type.c_str(), node_index);
                return;
            }

            if (node.parent_token == "<number>")
            {
                struct ValueEnumeration ve = {"int", node_index, node.token};

                args_type.push_back(ve);
                printf("preparationValueEnumeration %s %d\n", ve.type.c_str(), node_index);
                return;
            }

            if (node.parent_token == "<text>")
            {
                struct ValueEnumeration ve = {"string", node_index, node.token};
                args_type.push_back(ve);
                printf("preparationValueEnumeration %s %d\n", ve.type.c_str(), node_index);
                return;
            }

            for (int i = 0; i < node.children.size(); i++)
            {
                int child_node_index = node.children[i];
                Syntactic::SyntacticTreeNode child_node = getTreeNode(child_node_index);

                preparationValueEnumeration(child_node_index, args_type);
            }
        }

        void Softj::preparationFunctionMessagePassing(int node_index)
        {
            Syntactic::SyntacticTreeNode node = getTreeNode(node_index);
            int child_node_left_index = node.children[0];

            Syntactic::SyntacticTreeNode node_left = getTreeNode(child_node_left_index);

            vValueEnumeration args_type = {};

            int child_node_right_index = -1;
            if (node.children.size() == 2)
            {
                child_node_right_index = node.children[1];
                preparationValueEnumeration(child_node_right_index, args_type);
            }

            struct FunctionMessagePassing fmp = {node_left.token, child_node_left_index, args_type};

            printf("preparationFunctionMessagePassing %d %d %s %d\n", child_node_left_index, child_node_right_index, node_left.token.c_str(), args_type.size());

            function_message_passing_map[child_node_left_index] = fmp;
        }

        // 関数定義について、予め軽く解析しておく
        void Softj::preparationFunction(int node_index)
        {
            Syntactic::SyntacticTreeNode node = getTreeNode(node_index);
            ProcessVisualization::vArgument extract_args = {};

            // 変数の名前と戻り地の定義
            ProcessVisualization::Argument function_definition = extractValueDefinition(node.children[0]);

            if (node.children.size() == 1)
            {
                return;
            }

            if (node.children.size() == 2)
            {
                if (getTreeNode(node.children[1]).token == "<value_definition>")
                {
                    extractArgument(node.children[1], extract_args);
                    ProcessVisualization::FunctionUnit function_unit(function_definition.name, function_definition.type, extract_args, -2);
                    fpu->addFunction(function_unit);
                }
                else
                {
                    ProcessVisualization::FunctionUnit function_unit(function_definition.name, function_definition.type, extract_args, node.children[1]);
                    fpu->addFunction(function_unit);
                }
                return;
            }

            int arg_node = node.children[1];
            int block_node = node.children[2];

            // 引数一覧
            extractArgument(arg_node, extract_args);
            printf("preparationFunction %s %s %d\n", function_definition.name.c_str(), function_definition.type.c_str(), node_index);
            ProcessVisualization::FunctionUnit function_unit(function_definition.name, function_definition.type, extract_args, block_node);
            fpu->addFunction(function_unit);
        }

        // 予め軽く木構造を走査しておく
        void Softj::preparationTree()
        {
            for (int i = 0; i < syntactic_analysis_tree->size(); i++)
            {
                Syntactic::SyntacticTreeNode node = getTreeNode(i);

                if (node.token == "<function>")
                {
                    preparationFunction(i);
                }
                if (node.token == "<function_message_passing>")
                {
                    preparationFunctionMessagePassing(i);
                }
            }
        }
    }
};
