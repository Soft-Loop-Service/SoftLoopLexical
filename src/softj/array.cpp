
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
        void Softj::resolutionCalcMakeArray(int pointer, vint &length_list, string array_type, int depth)
        {
            if (length_list.size() <= depth)
            {
                //printf("配列末端 %d %s\n", pointer, array_type.c_str());

                if (array_type == "string")
                {
                    vpu->newLinkPointerValue(pointer, "");
                }
                if (array_type == "int")
                {
                    vpu->newLinkPointerValue(pointer, 0);
                }
                return;
            }

            vint pointers = vpu->newArray(pointer, length_list[depth]);
            for (int i = 0; i < length_list[depth]; i++)
            {
                resolutionCalcMakeArray(pointers[i], length_list, array_type, (depth + 1));
            }
        }

        void Softj::resolutionCalcArrayLength(int node_index, vint &length_list)
        {
            Syntactic::SyntacticTreeNode current_node = getTreeNode(node_index);

            if (current_node.token == "<array_length>")
            {
                for (int i = 0; i < current_node.children.size(); i++)
                {
                    resolutionCalcArrayLength(current_node.children[i], length_list);
                }
                return;
            }

            int length = resolutionTreeCalcInt(node_index);
            length_list.push_back(length);
            //printf("length %d\n", length);
            return;
        }

        void Softj::resolutionCalcNewArray(int node_index, int pointer)
        {

            Syntactic::SyntacticTreeNode current_node = getTreeNode(node_index);

            if (current_node.children.size() <= 2)
            {
                return;
            }

            int array_type_index = current_node.children[1];
            int array_len_node_index = current_node.children[2];
            string type = getTreeNode(array_type_index).token;

            vint length_list;
            resolutionCalcArrayLength(array_len_node_index, length_list);
            resolutionCalcMakeArray(pointer, length_list, type, 0);

            //printf("resolutionCalcNewArray %d %d\n", node_index, pointer);

            return;
        }

        void Softj::resolutionCalcArray(int node_index, int &pointer)
        {
            Syntactic::SyntacticTreeNode current_node = getTreeNode(node_index);

            if (current_node.children.size() < 2)
            {
                return;
            }

            int array_name_index = current_node.children[0];
            int array_len_node_index = current_node.children[1];
            Syntactic::SyntacticTreeNode array_index_node = getTreeNode(array_name_index);

            vint length_list;
            resolutionCalcArrayLength(array_len_node_index, length_list);

            int array_pointer;
            vpu->getPointer(array_index_node.token, array_pointer);
            //printf("配列アドレスの解決 %s %d\n", array_index_node.token.c_str(), array_pointer);

            if (!(vpu->hasArrayPointer(array_pointer)))
            {
                //printf("配列アドレスの解決(hasArrayPointer失敗)\n");
                ProcessVisualization::ProcessAnalysis pr(ProcessVisualization::is_id_process_type_error, "未定義配列アクセス", vpu->getDepth(), node_index);
                process_timeline->pushProcessAnalysis(pr);
                pointer = -1;
                return;
            }

            for (int i = 0; i < length_list.size(); i++)
            {
                vint pointers = vpu->getArrayPointers(array_pointer);

                if (length_list[i] < pointers.size())
                {
                    array_pointer = pointers[length_list[i]];
                    //printf("配列アドレスの解決(次元) %d %d\n", length_list[i], array_pointer);
                }
                else
                {
                    //printf("配列アドレスの解決(失敗)\n");
                    ProcessVisualization::ProcessAnalysis pr(ProcessVisualization::is_id_process_type_error, "配列範囲外アクセス(要素)", vpu->getDepth(), node_index);
                    process_timeline->pushProcessAnalysis(pr);
                    pointer = -1;
                    return;
                }
            }

            pointer = array_pointer;
            return;
        }

        int Softj::resolutionTreeCalcArray(int node_index)
        {
            Syntactic::SyntacticTreeNode current_node = getTreeNode(node_index);

            if (current_node.token == "<new_array>")
            {
                int pointer = vpu->newPointer();
                resolutionCalcNewArray(node_index, pointer);
                return pointer;
            }

            if (current_node.token == "<array_name>")
            {
                int pointer;
                resolutionCalcArray(node_index, pointer);
                return pointer;
            }

            if (current_node.children.size() == 1)
            {
                int r = resolutionTreeCalcArray(current_node.children[0]);
                return r;
            }
        }

    }
};
