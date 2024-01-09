
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
            string e_class;
            string element;
            vint children;

            HtmlKitElement()
            {
                this->e_tag = "div";
                this->e_id = "";
                this->e_class = "root";
                this->children = {};
            }

            HtmlKitElement(string e_tag)
            {
                this->e_tag = e_tag;
                this->e_id = "";
                this->e_class = "";
                this->children = {};
            }

            void setEClass(string e_class)
            {
                this->e_class = e_class;
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

                if (e_class != "")
                {
                    text += "class=";
                    text += e_class;
                    text += " ";
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
            vProcessAnalysis *process_result_p;
            HTMLKit::HtmlKitTree html_kit_tree;

            int layer_length = 10;

            void timelineProcessArea(int html_parent_node, ProcessAnalysis process)
            {
                HTMLKit::HtmlKitElement process_area("div");
                process_area.setEClass("process");

                int process_node_index = html_kit_tree.add_node(html_parent_node, process_area);

                timelineMessageArea(process_node_index, process);
                timelineLayerArea(process_node_index, process);
            }

            void timelineMessageArea(int html_parent_node, ProcessAnalysis process)
            {
                HTMLKit::HtmlKitElement message_area("div");
                message_area.setEClass("message");
                int message_node_index = html_kit_tree.add_node(html_parent_node, message_area);
                HTMLKit::HtmlKitElement message_text_area("span");
                message_text_area.setEClass("message_text");
                message_text_area.setElement(process.message);
                html_kit_tree.add_node(message_node_index, message_text_area);
            }
            void timelineLayerArea(int html_parent_node, ProcessAnalysis process)
            {
                HTMLKit::HtmlKitElement layer_area("div");
                layer_area.setEClass("layer");
                int layer_area_index = html_kit_tree.add_node(html_parent_node, layer_area);

                HTMLKit::HtmlKitElement layer_horizontal_area("div");
                layer_horizontal_area.setEClass("layer_horizontal");

                int layer_node_index_input_index = html_kit_tree.add_node(layer_area_index, layer_horizontal_area);

                HTMLKit::HtmlKitElement layer_horizontal_connection_area("div");
                layer_horizontal_connection_area.setEClass("layer_horizontal_connection");
                int layer_horizontal_connection = html_kit_tree.add_node(layer_area_index, layer_horizontal_connection_area);

                int layer_node_index_output_index = html_kit_tree.add_node(layer_area_index, layer_horizontal_area);

                for (int i = 0; i < layer_length; i++)
                {
                    timelineLayerInputArea(layer_node_index_input_index, process, i);
                }

                for (int i = 0; i < layer_length; i++)
                {
                    timelineLayerOutputArea(layer_node_index_output_index, process, i);
                }
            }

            void timelineLayerInputArea(int html_parent_node, ProcessAnalysis process, int unit_num)
            {
                int layer_unit_node_index = timelineLayerUnitArea(html_parent_node, process, unit_num);

                for (int i = 0; i < process.input_layer.size(); i++)
                {
                    if (process.input_layer[i] == unit_num)
                    {
                        timelineLayerUnitStationInputArea(layer_unit_node_index);
                        return;
                    }
                }
            }
            void timelineLayerOutputArea(int html_parent_node, ProcessAnalysis process, int unit_num)
            {

                int layer_unit_node_index = timelineLayerUnitArea(html_parent_node, process, unit_num);

                for (int i = 0; i < process.output_layer.size(); i++)
                {
                    if (process.output_layer[i] == unit_num)
                    {
                        timelineLayerUnitStationOutputArea(layer_unit_node_index);
                        return;
                    }
                }

            }
            int timelineLayerUnitArea(int html_parent_node, ProcessAnalysis process, int unit_num)
            {
                HTMLKit::HtmlKitElement layer_unit_area("div");
                layer_unit_area.setEClass("layer_unit");
                int layer_unit_node_index = html_kit_tree.add_node(html_parent_node, layer_unit_area);

                return layer_unit_node_index;
            }

            void timelineLayerUnitStationInputArea(int html_parent_node)
            {
                HTMLKit::HtmlKitElement layer_unit_station_area("div");
                layer_unit_station_area.setEClass("layer_unit_station_input");
                int layer_unit_station_node_index = html_kit_tree.add_node(html_parent_node, layer_unit_station_area);
            }
            void timelineLayerUnitStationOutputArea(int html_parent_node)
            {
                HTMLKit::HtmlKitElement layer_unit_station_area("div");
                layer_unit_station_area.setEClass("layer_unit_station_output");
                int layer_unit_station_node_index = html_kit_tree.add_node(html_parent_node, layer_unit_station_area);
            }

        public:
            HtmlTimeLine(vProcessAnalysis *process_result_p)
            {
                this->process_result_p = process_result_p;
                this->html_kit_tree = HTMLKit::HtmlKitTree();
                this->layer_length = 10;
            }

            string timelineArea()
            {
                printf("タイムライン木構造構築\n");

                for (int i = 0; i < process_result_p->size(); i++)
                {
                    ProcessAnalysis pr = (*process_result_p)[i];
                    timelineProcessArea(0, pr);
                }

                printf("タイムライン木構造変換\n");

                string html_txt = html_kit_tree.parseHtml();
                printf("timeline area %s\n", html_txt.c_str());

                return html_txt;
            }
        };
    }

    void outputHtml(vProcessAnalysis process_result)
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

        Timeline::HtmlTimeLine html_timeline(&process_result);
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