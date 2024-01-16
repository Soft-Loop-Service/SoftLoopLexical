
#ifndef __JSONKIT
#define __JSONKIT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>


#include "./../../../bnf_syntax/softj/softj_tree.hpp"
#include "./../../process/process_analysis_definition.hpp"

namespace HTMLParse
{
    namespace JsonKit
    {
        class JsonKitElement;
        typedef vector<JsonKitElement> vJsonKitElement;

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
            JsonKitElement() {
                this->e_type = "";
                this->e_name = "";
                this->element = "";
                this->children = {};
            }
            JsonKitElement(string type)
            {
                this->e_type = type;
                this->e_name = "";
                this->element = "";
                this->children = {};
            }

            JsonKitElement(string type, string element)
            {
                this->e_type = type;
                this->e_name = "";
                this->element = element;
                this->children = {};
            }

            JsonKitElement(string type, int element)
            {
                this->e_type = type;
                this->e_name = "";
                this->element = to_string(element);
                this->children = {};
            }

            JsonKitElement(string type, string name, string e)
            {
                this->e_type = type;
                this->e_name = name;
                this->element = e;
                this->children = {};
            }
            JsonKitElement(string type, string name, int e)
            {
                this->e_type = type;
                this->e_name = name;
                this->element = to_string(e);
                this->children = {};
            }

            void add_children(int index)
            {
                children.push_back(index);
            }
            string parseJsonStart()
            {
                if (isArray())
                {
                    return "[";
                }
                if (isDist())
                {
                    return "{";
                }
                return "";
            }
            string parseJsonEnd()
            {
                if (isArray())
                {
                    return "]";
                }
                if (isDist())
                {
                    return "}";
                }
                return "";
            }
            string parseJsonElement()
            {
                if (isValue())
                {
                    if(e_name == ""){
                        return "\"" +  element + "\"";
                    }
                    return "\"" + e_name + "\""+ " : " + "\""+ element + "\"";
                }
                if (isArray())
                {
                    return "";
                }
                if (isDist())
                {
                    return "";
                }
                return "";
            }
        };
        class JsonKitTree
        {

        private:
            vJsonKitElement json_kit_element;

            string recursionParseJson(int node)
            {
                printf("recursionParseJson %d\n",node);
                string text = "";

                string text_start = json_kit_element[node].parseJsonStart();
                string text_end = json_kit_element[node].parseJsonEnd();

                string text_children = "";

                int size = json_kit_element[node].children.size();
                for (int i = 0; i < size; i++)
                {
                    int child_node = json_kit_element[node].children[i];
                    text_children += " ";
                    text_children += recursionParseJson(child_node);

                    if (i < size - 1)
                    {
                        text_children += ",";
                    }
                }

                string text_element = json_kit_element[node].parseJsonElement();

                text += text_start;
                text += " ";
                text += text_element;
                text += " ";
                text += text_children;
                text += " ";
                text += text_end;

                printf("recursionParseJson(戻) %s\n",text.c_str() );

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

            string parseJson()
            {
                string text = recursionParseJson(0);
                return text;
            }
        };

    };
}

#endif