
#ifndef __JSONKIT
#define __JSONKIT

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
    namespace JsonKit
    {
        class JsonKitElement;
        class JsonKitTree;
        typedef vector<JsonKitElement> vJsonKitElement;


        class JsonKitTree
        {

        private:
            vJsonKitElement json_kit_element;

            string recursionParseJson(int node)
            {
                string text = "";

                string text_start = json_kit_element[node].parseJsonStart();
                string text_end = json_kit_element[node].parseJsonEnd();

                string text_children = "";

                for (int i = 0; i < json_kit_element[node].children.size(); i++)
                {
                    int child_node = json_kit_element[node].children[i];
                    text_children += " ";
                    text_children += recursionParseJson(child_node);
                }

                string text_element = json_kit_element[node].parseJsonElement();

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
            JsonKitTree()
            {
                json_kit_element = {};
                JsonKitElement h;
                json_kit_element.push_back(h);
            }

            int add_node(int parent_node, JsonKitElement node_element)
            {
                json_kit_element.push_back(node_element);

                int node_index = json_kit_element.size() - 1;
                json_kit_element[parent_node].add_children(node_index);
                return node_index;
            }

            string parseHtml()
            {
                string text = recursionParseJson(0);
                return text;
            }
        };


        class JsonKitElement
        {
        private:
            string e_name;
            string e_type;
            string element;

            bool isValue()
            {
                return e_type == "value" ? true : false;
            }
            bool isArray()
            {
                return e_type == "array" ? true : false;
            }
            bool isDist()
            {
                return e_type == "dist" ? true : false;
            }

        public:
            vint children;
            void add_children(int index)
            {
                children.push_back(index);
            }
            string parseJsonStart()
            {
                if (isArray())
                {
                    return "[";

                    if (isDist())
                    {
                        return "{";
                    }
                    return "";
                }
            }
            string parseJsonEnd()
            {
                if (isArray())
                {
                    return "]";

                    if (isDist())
                    {
                        return "}";
                    }
                    return "";
                }
            }
            string parseJsonElement()
            {
                if (isValue())
                {
                    return element;
                }
                if (isArray())
                {
                    return element;
                }
                if (isDist())
                {
                    return e_name + " : " + element;
                }
            }
        };
    };
}

#endif