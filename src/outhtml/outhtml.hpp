
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
                e_tag = "root";
                e_id = "";
                e_class = "";
                children = {};
            }

            HtmlKitElement(string e_tag)
            {
                e_tag = e_tag;
                e_id = "";
                e_class = "";
                children = {};
            }

            void setEClass(string e_class)
            {
                e_class = e_class;
            }

            void setEId(string e_id)
            {
                e_id = e_id;
            }

            void setElement(string element)
            {
                element = element;
            }
            void add_children(int index)
            {
                children.push_back(index);
            }
            string parseHtml1()
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
                // "<div class=hoge id=hoge></div>"
            }
            string parseHtml2()
            {
                string text = "";
                text += element;
                return text;
            }
            string parseHtml3()
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

                string text1 = html_kit_element[node].parseHtml1();
                string text2 = html_kit_element[node].parseHtml2();

                string text_children = "";

                for (int i = 0; i < html_kit_element[node].children.size(); i++)
                {
                    int child_node = html_kit_element[node].children[i];
                    text_children += " ";
                    text_children += recursionParseHtml(child_node);
                }

                string text3 = html_kit_element[node].parseHtml3();

                text += text1;
                text += " ";
                text += text2;
                text += " ";
                text += text_children;
                text += " ";
                text += text3;

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
            vProcessAnalysis *process_result;
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
                int layer_node_index = html_kit_tree.add_node(html_parent_node, layer_area);

                for (int i = 0; i < layer_length; i++)
                {
                    timelineLayerUnitArea(layer_node_index, process, i);
                }
            }
            void timelineLayerUnitArea(int html_parent_node, ProcessAnalysis process, int unit_num)
            {
                HTMLKit::HtmlKitElement layer_unit_area("div");
                layer_unit_area.setEClass("layer_unit");
                int layer_unit_node_index = html_kit_tree.add_node(html_parent_node, layer_unit_area);

                if (process.output_layer == unit_num)
                {
                    timelineLayerUnitStationOutputArea(unit_num);
                    return;
                }

                for (int i = 0; i < process.input_layer.size(); i++)
                {

                    if (process.input_layer[i] == unit_num)
                    {
                        timelineLayerUnitStationInputArea(unit_num);
                        return;
                    }
                }
            }
            string timelineLayerUnitStationOutputArea(int html_parent_node)
            {
                HTMLKit::HtmlKitElement layer_unit_station_area("div");
                layer_unit_station_area.setEClass("layer_unit_station_output");
                int layer_unit_station_node_index = html_kit_tree.add_node(html_parent_node, layer_unit_station_area);
            }
            string timelineLayerUnitStationInputArea(int html_parent_node)
            {
                HTMLKit::HtmlKitElement layer_unit_station_area("div");
                layer_unit_station_area.setEClass("layer_unit_station_input");
                int layer_unit_station_node_index = html_kit_tree.add_node(html_parent_node, layer_unit_station_area);
            }

        public:
            HtmlTimeLine(vProcessAnalysis process_result)
            {
                this->process_result = &process_result;
                this->html_kit_tree = HTMLKit::HtmlKitTree();
                this->layer_length = 10;
            }

            string timelineArea()
            {
                for (int i = 0; i < process_result->size(); i++)
                {
                    ProcessAnalysis pr = (*this->process_result)[i];
                    timelineProcessArea(0, pr);
                }

                return html_kit_tree.parseHtml();
            }
        };
    }

    void outputHtml(vProcessAnalysis process_result)
    {
        std::ofstream writing_file;
        std::string filename = "test.html";
        writing_file.open(filename, std::ios::out);

        string text1 = "<!DOCTYPE html><html lang=\"ja\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>プログラムの可視化</title></head><body>";

        string text2 = "</body></html>";

        string div = "";

        Timeline::HtmlTimeLine html_timeline(process_result);

        string html_div = html_timeline.timelineArea();
        div += html_div;

        writing_file << text1 << endl;
        writing_file << div << endl;
        writing_file << text2 << endl;

        writing_file.close();
    }
}

#endif