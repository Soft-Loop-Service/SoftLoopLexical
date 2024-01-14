
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

            void process_group()
            {
                JsonKit::JsonKitElement process_groups("array");
                int process_groups_index = json_kit_tree.add_node(0,process_groups);

                for (int i = 0 ; i < process_result_p->size() ; i++){
                    process(i,process_groups_index);
                }
            }

            void process(int process_index , int kit_index){
                ProcessVisualization::ProcessAnalysis process_unit = (*process_result_p)[process_index];
                
                JsonKit::JsonKitElement process_node("dist");
                int process_kit_index = json_kit_tree.add_node(kit_index,process_node);
                
                JsonKit::JsonKitElement layer("value","layer",0);
                json_kit_tree.add_node(process_kit_index,layer);

                JsonKit::JsonKitElement message("value" ,"message",process_unit.message );
                json_kit_tree.add_node(process_kit_index,message);

                JsonKit::JsonKitElement node_index("value","node_index",process_unit.node_index);
                json_kit_tree.add_node(process_kit_index,node_index);

                JsonKit::JsonKitElement process_type("value","process_type",process_unit.process_type);
                json_kit_tree.add_node(process_kit_index,process_type);
            }


        public:
            Timeline(vSyntacticTree *syntactic_analysis_tree_p, ProcessVisualization::vProcessAnalysis *process_result_p, ProcessVisualization::VariablePossessionUnion *variable_possession_union_p)
            {
                this->syntactic_analysis_tree_p = syntactic_analysis_tree_p;
                this->process_result_p = process_result_p;
                this->variable_possession_union_p = variable_possession_union_p;
                this->json_kit_tree = JsonKit::JsonKitTree();

                ProcessVisualization::mapVariableProcessEnumeration variable_enumeration_map = variable_possession_union_p->getVariableProcessEnumeration();
                this->layer_length = variable_enumeration_map.size();
            }

            string timelineArea()
            {
                printf("process_group\n");
                process_group();
                printf("parseJson\n");

                string process_data = json_kit_tree.parseJson();

                string text = "var process_data = " + process_data + ";";

                printf("timelineArea\n");
                return text;
                // return html_txt;
            }
        };
    }

};

#endif