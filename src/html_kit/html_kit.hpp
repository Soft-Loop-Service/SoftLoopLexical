
#ifndef __HTMLKIT
#define __HTMLKIT

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
}

#endif