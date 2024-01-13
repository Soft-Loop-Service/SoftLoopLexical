
#ifndef __SOFTJ_INLINE_EX
#define __SOFTJ_INLINE_EX

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
#include "./softj_tree.hpp"

namespace LanguageSpecifications
{
    namespace SoftjLanguage
    {

            inline ProcessVisualization::Argument Softj::extractValueDefinition(int node_index)
            {
                SyntacticTreeNode node = (*syntactic_analysis_tree)[node_index];
                SyntacticTreeNode node_left = (*syntactic_analysis_tree)[node.children[0]];
                SyntacticTreeNode node_right = (*syntactic_analysis_tree)[node.children[1]];
                printf("extractValueDefinition %s %s %d\n", node_left.token.c_str(), node_right.token.c_str(), node_index);

                struct ProcessVisualization::Argument rvarg = {node_left.token, node_right.token};

                return rvarg;
            }

            inline void Softj::extractArgument(int node_index, ProcessVisualization::vArgument &extract_args)
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


    }
};
#endif