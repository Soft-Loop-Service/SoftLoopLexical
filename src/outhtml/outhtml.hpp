
#ifndef __OHTML
#define __OHTML

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
namespace HTMLParse
{
    namespace HTMLKit
    {
        class HtmlKitElement;
        typedef vector<HtmlKitElement> vHtmlKitElement;
        class HtmlKitElement
        {
        public:
            string e_tag;
            string e_id;
            vstring e_class;
            string element;
            vint children;

            HtmlKitElement()
            {
                this->e_tag = "div";
                this->e_id = "";
                this->e_class = {};
                this->children = {};
            }

            HtmlKitElement(string e_tag)
            {
                this->e_tag = e_tag;
                this->e_id = "";
                this->e_class = {};
                this->children = {};
            }

            void addEClass(string e)
            {
                this->e_class.push_back(e);
            }

            void setEId(string e_id)
            {
                this->e_id = e_id;
            }

            void setElement(string element)
            {
                this->element = element;
            }
            void add_children(int index)
            {
                children.push_back(index);
            }
            string parseHtmlStartTag()
            {

                string text = "";

                text += "<";
                text += e_tag;
                text += " ";

                if (1 <= e_class.size())
                {
                    text += "class=";
                    text += "\"";

                    for (int i = 0; i < e_class.size(); i++)
                    {
                        text += " ";
                        text += e_class[i];
                    }

                    text += "\"";
                }

                if (e_id != "")
                {
                    text += "id=";
                    text += e_id;
                    text += " ";
                }
                text += ">";
                return text;
            }
            string parseHtmlElement()
            {
                string text = "";
                text += element;
                return text;
            }
            string parseHtmlEndTag()
            {
                string text = "";
                text += "<";
                text += "/";
                text += e_tag;
                text += ">";
                return text;
            }
        };

        class HtmlKitTree
        {

        private:
            vHtmlKitElement html_kit_element;

            string recursionParseHtml(int node)
            {
                string text = "";

                string text_start = html_kit_element[node].parseHtmlStartTag();
                string text_end = html_kit_element[node].parseHtmlEndTag();

                string text_children = "";

                for (int i = 0; i < html_kit_element[node].children.size(); i++)
                {
                    int child_node = html_kit_element[node].children[i];
                    text_children += " ";
                    text_children += recursionParseHtml(child_node);
                }

                string text_element = html_kit_element[node].parseHtmlElement();

                text += text_start;
                text += " ";
                text += text_element;
                text += " ";
                text += text_children;
                text += " ";
                text += text_end;

                return text;
            }

        public:
            HtmlKitTree()
            {
                html_kit_element = {};
                HtmlKitElement h;
                html_kit_element.push_back(h);
            }

            int add_node(int parent_node, HtmlKitElement node_element)
            {
                html_kit_element.push_back(node_element);

                int node_index = html_kit_element.size() - 1;
                html_kit_element[parent_node].add_children(node_index);
                return node_index;
            }

            string parseHtml()
            {
                string text = recursionParseHtml(0);
                return text;
            }
        };

    }
    namespace Timeline
    {

        class HtmlTimeLine
        {

        private:
            vSyntacticTree *syntactic_analysis_tree_p;
            ProcessVisualization::vProcessAnalysis *process_result_p;
            ProcessVisualization::VariablePossessionUnion *variable_possession_union_p;
            HTMLKit::HtmlKitTree html_kit_tree;

            int layer_length = 10;

            void timelineLeftArea(int html_parent_node, ProcessVisualization::ProcessAnalysis process)
            {
                int process_node_index = timelineCommonArea(html_parent_node, process);
                timelineMessageArea(process_node_index, process);
                timelineLineColumnArea(process_node_index, process);
            }
            void timelineRightArea(int html_parent_node, ProcessVisualization::ProcessAnalysis process)
            {
                int process_node_index = timelineCommonArea(html_parent_node, process);
                timelineLayerArea(process_node_index, process);
            }
            int timelineCommonArea(int html_parent_node, ProcessVisualization::ProcessAnalysis process)
            {
                HTMLKit::HtmlKitElement process_area("div");
                process_area.addEClass("process");

                int process_node_index = html_kit_tree.add_node(html_parent_node, process_area);

                HTMLKit::HtmlKitElement process_connection_area("div");
                process_connection_area.addEClass("process_connection");
                int layer_horizontal_connection = html_kit_tree.add_node(html_parent_node, process_connection_area);

                return process_node_index;
            }

            void timelineMessageArea(int html_parent_node, ProcessVisualization::ProcessAnalysis process)
            {
                HTMLKit::HtmlKitElement message_area("div");
                message_area.addEClass("message");

                if (process.process_type == ProcessVisualization::is_id_process_type_error)
                {
                    message_area.addEClass("message_error");
                }
                if (process.process_type == ProcessVisualization::is_id_process_type_warning)
                {
                    message_area.addEClass("message_warning");
                }
                if (process.process_type == ProcessVisualization::is_id_process_type_language_error)
                {
                    message_area.addEClass("message_language_error");
                }

                int message_node_index = html_kit_tree.add_node(html_parent_node, message_area);
                HTMLKit::HtmlKitElement message_text_area("span");
                message_text_area.addEClass("message_text");
                message_text_area.setElement(process.message);
                html_kit_tree.add_node(message_node_index, message_text_area);
            }

            void timelineLineColumnArea(int html_parent_node, ProcessVisualization::ProcessAnalysis process)
            {
                HTMLKit::HtmlKitElement line_column_area("div");
                line_column_area.addEClass("source_code_position");
                int line_column_area_index = html_kit_tree.add_node(html_parent_node, line_column_area);

                HTMLKit::HtmlKitElement line_area("div");
                line_area.addEClass("source_code_position_line");
                int line_area_index = html_kit_tree.add_node(line_column_area_index, line_area);

                HTMLKit::HtmlKitElement column_area("div");
                column_area.addEClass("source_code_position_column");
                int column_area_index = html_kit_tree.add_node(html_parent_node, line_column_area);

                int source_code_line = (*syntactic_analysis_tree_p)[process.node_index].source_code_line;
                int source_code_column = (*syntactic_analysis_tree_p)[process.node_index].source_code_column;

                HTMLKit::HtmlKitElement source_code_position_line_text_area("span");
                source_code_position_line_text_area.addEClass("source_code_position_text");
                source_code_position_line_text_area.setElement(to_string(source_code_line));
                html_kit_tree.add_node(line_area_index, source_code_position_line_text_area);

                HTMLKit::HtmlKitElement source_code_position_column_text_area("span");
                source_code_position_column_text_area.addEClass("source_code_position_text");
                source_code_position_column_text_area.setElement(to_string(source_code_column));
                html_kit_tree.add_node(column_area_index, source_code_position_column_text_area);
            }

            void timelineLayerArea(int html_parent_node, ProcessVisualization::ProcessAnalysis process)
            {
                HTMLKit::HtmlKitElement layer_area("div");
                layer_area.addEClass("layer");
                int layer_area_index = html_kit_tree.add_node(html_parent_node, layer_area);

                HTMLKit::HtmlKitElement layer_horizontal_area("div");
                layer_horizontal_area.addEClass("layer_horizontal");

                int layer_node_index = html_kit_tree.add_node(layer_area_index, layer_horizontal_area);

                // int layer_node_index_output_index = html_kit_tree.add_node(layer_area_index, layer_horizontal_area);

                for (int i = 0; i < layer_length; i++)
                {
                    timelineLayerInputArea(layer_node_index, process, i);
                }
            }

            void timelineLayerInputArea(int html_parent_node, ProcessVisualization::ProcessAnalysis process, int unit_num)
            {
                int layer_unit_node_index = timelineLayerUnitArea(html_parent_node, process, unit_num);

                HTMLKit::HtmlKitElement layer_unit_station_area("div");
                layer_unit_station_area.addEClass("layer_unit_station");
                int station_area_index;
                string text;

                for (int i = 0; i < process.layer.size(); i++)
                {
                    if (process.layer[i].layer != unit_num)
                    {
                        continue;
                    }
                    if (process.process_type == ProcessVisualization::is_id_process_type_input)
                    {
                        station_area_index = timelineLayerUnitStationInputArea(layer_unit_node_index, layer_unit_station_area);
                        text = process.layer[i].text;
                        break;
                    }
                    if (process.process_type == ProcessVisualization::is_id_process_type_ouput)
                    {
                        station_area_index = timelineLayerUnitStationOutputArea(layer_unit_node_index, layer_unit_station_area);
                        text = process.layer[i].text;
                        break;
                    }
                    if (process.process_type == ProcessVisualization::is_id_process_type_logic)
                    {
                        station_area_index = timelineLayerUnitStationLogicArea(layer_unit_node_index, layer_unit_station_area);
                        text = process.layer[i].text;
                        break;
                    }
                    return;
                }


                HTMLKit::HtmlKitElement station_message("span");
                station_message.addEClass("station_message");
                station_message.setElement(text);
                html_kit_tree.add_node(station_area_index, station_message);
            }

            int timelineLayerUnitArea(int html_parent_node, ProcessVisualization::ProcessAnalysis process, int unit_num)
            {
                HTMLKit::HtmlKitElement layer_unit_area("div");
                layer_unit_area.addEClass("layer_unit");
                int layer_unit_node_index = html_kit_tree.add_node(html_parent_node, layer_unit_area);
                return layer_unit_node_index;
            }

            int timelineLayerUnitStationInputArea(int html_parent_node, HTMLKit::HtmlKitElement layer_unit_station_area)
            {
                layer_unit_station_area.addEClass("layer_unit_station_input");
                int layer_unit_station_node_index = html_kit_tree.add_node(html_parent_node, layer_unit_station_area);
                return layer_unit_station_node_index;
            }
            int timelineLayerUnitStationOutputArea(int html_parent_node, HTMLKit::HtmlKitElement layer_unit_station_area)
            {
                layer_unit_station_area.addEClass("layer_unit_station_output");
                int layer_unit_station_node_index = html_kit_tree.add_node(html_parent_node, layer_unit_station_area);
                return layer_unit_station_node_index;
            }
            int timelineLayerUnitStationLogicArea(int html_parent_node, HTMLKit::HtmlKitElement layer_unit_station_area)
            {
                layer_unit_station_area.addEClass("layer_unit_station_logic");
                int layer_unit_station_node_index = html_kit_tree.add_node(html_parent_node, layer_unit_station_area);
                return layer_unit_station_node_index;
            }

        public:
            HtmlTimeLine(vSyntacticTree *syntactic_analysis_tree_p, ProcessVisualization::vProcessAnalysis *process_result_p ,ProcessVisualization::VariablePossessionUnion *variable_possession_union_p)
            {
                this->syntactic_analysis_tree_p = syntactic_analysis_tree_p;
                this->process_result_p = process_result_p;
                this->variable_possession_union_p = variable_possession_union_p;
                this->html_kit_tree = HTMLKit::HtmlKitTree();

                ProcessVisualization::mapVariableProcessEnumeration  variable_enumeration_map = variable_possession_union_p->getVariableProcessEnumeration();
                this->layer_length = variable_enumeration_map.size();
            }

            string timelineArea()
            {
                printf("タイムライン木構造構築\n");

                HTMLKit::HtmlKitElement timeline_area("div");
                timeline_area.addEClass("timeline");
                int timeline_area_index = html_kit_tree.add_node(0, timeline_area);

                HTMLKit::HtmlKitElement timeline_left_area("div");
                timeline_left_area.addEClass("timeline_left");
                HTMLKit::HtmlKitElement timeline_right_area("div");
                timeline_right_area.addEClass("timeline_right");

                int timeline_left_index = html_kit_tree.add_node(timeline_area_index, timeline_left_area);
                int timeline_right_index = html_kit_tree.add_node(timeline_area_index, timeline_right_area);

                for (int i = 0; i < process_result_p->size(); i++)
                {
                    ProcessVisualization::ProcessAnalysis pr = (*process_result_p)[i];
                    timelineLeftArea(timeline_left_index , pr);
                }

                for (int i = 0; i < process_result_p->size(); i++)
                {
                    ProcessVisualization::ProcessAnalysis pr = (*process_result_p)[i];
                    timelineRightArea(timeline_right_index , pr);
                }

                printf("タイムライン木構造変換\n");

                string html_txt = html_kit_tree.parseHtml();
                printf("timeline area %s\n", html_txt.c_str());

                return html_txt;
            }
        };
    }

    void outputHtml(vSyntacticTree syntactic_analysis_tree, ProcessVisualization::vProcessAnalysis process_result , ProcessVisualization::VariablePossessionUnion variable_possession_union)
    {
        std::ofstream writing_file;
        std::string filename = "test.html";
        writing_file.open(filename, std::ios::out);

        std::ifstream css_include_template("./src/outhtml/include_template.css");
        std::string css_include_template_string((std::istreambuf_iterator<char>(css_include_template)), std::istreambuf_iterator<char>());

        string css_style = "<style>" + css_include_template_string + "</style>";

        string text1a = "<!DOCTYPE html><html lang=\"ja\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
        string text1b = "<title>プログラムの可視化</title></head><body>";

        string text1 = text1a + css_style + text1b;
        string text2 = "</body></html>";

        string div = "";

        printf("%s\n", "outputHtml");

        Timeline::HtmlTimeLine html_timeline(&syntactic_analysis_tree, &process_result , &variable_possession_union);
        printf("%s\n", "outputHtml 2");

        string html_div = html_timeline.timelineArea();
        printf("%s\n", "outputHtml 3");

        div += html_div;

        writing_file << text1 << endl;
        writing_file << div << endl;
        writing_file << text2 << endl;

        writing_file.close();
    }
}

#endif