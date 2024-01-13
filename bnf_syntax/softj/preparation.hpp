
#ifndef __SOFTJP
#define __SOFTJP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "./../../src/syntactic/syntactic_analysis_tree.hpp"
#include "./../../src/process/process_analysis_definition.hpp"
#include "./../../src/process/process_analysis_function.hpp"
#include "./../../src/process/process_analysis_value.hpp"
#include "./definition.hpp"

namespace LanguageSpecifications
{
    namespace SoftjLanguage
    {

        namespace SoftjPreparation
        {
        private:
            vSyntacticTree *syntactic_analysis_tree;
            ProcessVisualization::FunctionPossessionUnion *fpu;
            m_i_FunctionMessagePassing function_message_passing_map;

        public:
            ProcessVisualization::Argument extractValueDefinition(int node_index)
            {
                SyntacticTreeNode node = (*syntactic_analysis_tree)[node_index];
                SyntacticTreeNode node_left = (*syntactic_analysis_tree)[node.children[0]];
                SyntacticTreeNode node_right = (*syntactic_analysis_tree)[node.children[1]];
                printf("extractValueDefinition %s %s %d\n", node_left.token.c_str(), node_right.token.c_str(), node_index);

                struct ProcessVisualization::Argument rvarg = {node_left.token, node_right.token};

                return rvarg;
            }

            void extractArgument(int node_index, ProcessVisualization::vArgument &extract_args)
            {
                SyntacticTreeNode node = (*syntactic_analysis_tree)[node_index];

                if (node.token == "<value_definition>")
                {
                    ProcessVisualization::Argument rvarg = extractValueDefinition(node_index);
                    extract_args.push_back(rvarg);
                    return;
                }

                for (int i = 0; i < node.children.size(); i++)
                {
                    int child_node_index = node.children[i];
                    SyntacticTreeNode child_node = (*syntactic_analysis_tree)[child_node_index];

                    if (child_node.token_label == is_id_NonterminalSymbol)
                    {
                        extractArgument(child_node_index, extract_args);
                    }
                }
            }

            void preparationValueEnumeration(int node_index, vValueEnumeration &args_type)
            {
                SyntacticTreeNode node = (*syntactic_analysis_tree)[node_index];

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
                    SyntacticTreeNode child_node = (*syntactic_analysis_tree)[child_node_index];

                    preparationValueEnumeration(child_node_index, args_type);
                }
            }

            void preparationFunctionMessagePassing(int node_index)
            {
                SyntacticTreeNode node = (*syntactic_analysis_tree)[node_index];
                int child_node_left_index = node.children[0];

                SyntacticTreeNode node_left = (*syntactic_analysis_tree)[child_node_left_index];

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
            void preparationFunction(int node_index)
            {
                SyntacticTreeNode node = (*syntactic_analysis_tree)[node_index];
                ProcessVisualization::vArgument extract_args = {};

                // 変数の名前と戻り地の定義
                ProcessVisualization::Argument function_definition = extractValueDefinition(node.children[0]);

                if (node.children.size() == 1)
                {
                    return;
                }

                if (node.children.size() == 2)
                {
                    if ((*syntactic_analysis_tree)[node.children[1]].token == "<value_definition>")
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
            void preparationTree()
            {
                for (int i = 0; i < syntactic_analysis_tree->size(); i++)
                {
                    SyntacticTreeNode node = (*syntactic_analysis_tree)[i];

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
        };

    };
};

#endif