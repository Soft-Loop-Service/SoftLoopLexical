
#ifndef __TIMELINE
#define __TIMELINE

#include "./../LR_table/LR_table.hpp"
#include "./../LR_table/LR_table_definition.hpp"
#include "./../LR_table/LR_table_cell.hpp"
#include "./../syntactic/syntactic_analysis_tree.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#include "./../../bnf_syntax/softj/softj_tree.hpp"
#include "./../process/process_analysis_definition.hpp"

#include "./json_kit.hpp"


namespace HTMLParse
{

    namespace Timeline
    {

        class Timeline
        {

        private:
            vSyntacticTree *syntactic_analysis_tree_p;
            ProcessVisualization::vProcessAnalysis *process_result_p;
            ProcessVisualization::VariablePossessionUnion *variable_possession_union_p;
            JsonKit::JsonKitTree json_kit_tree;
            int layer_length;

        public:
            Timeline(vSyntacticTree *syntactic_analysis_tree_p, ProcessVisualization::vProcessAnalysis *process_result_p ,ProcessVisualization::VariablePossessionUnion *variable_possession_union_p)
            {
                this->syntactic_analysis_tree_p = syntactic_analysis_tree_p;
                this->process_result_p = process_result_p;
                this->variable_possession_union_p = variable_possession_union_p;
                this->json_kit_tree = JsonKit::JsonKitTree();

                ProcessVisualization::mapVariableProcessEnumeration  variable_enumeration_map = variable_possession_union_p->getVariableProcessEnumeration();
                this->layer_length = variable_enumeration_map.size();
            }

            string timelineArea()
            {

                // return html_txt;
            }
        };
    }

};

#endif