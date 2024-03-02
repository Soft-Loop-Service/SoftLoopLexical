
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

        ProcessVisualization::Argument Softj::extractValueDefinition(int node_index)
        {
            Syntactic::SyntacticTreeNode node = getTreeNode(node_index);
            Syntactic::SyntacticTreeNode node_left = getTreeNode(node.children[0]);
            Syntactic::SyntacticTreeNode node_right = getTreeNode(node.children[1]);
            //printf("extractValueDefinition %s %s %d\n", node_left.token.c_str(), node_right.token.c_str(), node_index);

            struct ProcessVisualization::Argument rvarg = {node_left.token, node_right.token};

            return rvarg;
        }

        void Softj::extractArgument(int node_index, ProcessVisualization::vArgument &extract_args)
        {
            Syntactic::SyntacticTreeNode node = getTreeNode(node_index);

            if (node.token == "<value_definition>")
            {
                ProcessVisualization::Argument rvarg = extractValueDefinition(node_index);
                extract_args.push_back(rvarg);
                return;
            }

            for (int i = 0; i < node.children.size(); i++)
            {
                int child_node_index = node.children[i];
                Syntactic::SyntacticTreeNode child_node = getTreeNode(child_node_index);

                if (child_node.token_label == is_id_NonterminalSymbol)
                {
                    extractArgument(child_node_index, extract_args);
                }
            }
        }

    }
};
