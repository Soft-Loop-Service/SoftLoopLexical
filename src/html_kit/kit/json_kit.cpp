#include "./../html_kit.hpp"

namespace HTMLParse
{
    namespace JsonKit
    {

        bool JsonKitElement::isValue()
        {
            return e_type == "value" ? true : false;
        }
        bool JsonKitElement::isArray()
        {
            return e_type == "array" ? true : false;
        }
        bool JsonKitElement::isDist()
        {
            return e_type == "dist" ? true : false;
        }

        JsonKitElement::JsonKitElement()
        {
            this->e_type = "";
            this->e_name = "";
            this->element = "";
            this->children = {};
        }
        JsonKitElement::JsonKitElement(string type)
        {
            this->e_type = type;
            this->e_name = "";
            this->element = "";
            this->children = {};
        }

        JsonKitElement::JsonKitElement(string type, string name)
        {
            this->e_type = type;
            this->e_name = name;
            this->element = "";
            this->children = {};
        }

        JsonKitElement::JsonKitElement(string type, string name, string e)
        {
            this->e_type = type;
            this->e_name = name;
            this->element = e;
            this->children = {};
        }
        JsonKitElement::JsonKitElement(string type, string name, int e)
        {
            this->e_type = type;
            this->e_name = name;
            this->element = to_string(e);
            this->children = {};
        }

        void JsonKitElement::set_element(string e){
            this->element = e;
        }
        void JsonKitElement::set_element(int e){
            this->element = to_string(e);
        }

        void JsonKitElement::add_children(int index)
        {
            children.push_back(index);
        }
        string JsonKitElement::parseJsonStart()
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
        string JsonKitElement::parseJsonEnd()
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
        string JsonKitElement::parseJsonElement()
        {
            if (isValue())
            {
                if (element == "" && children.size() > 0)
                {
                    return "\"" + e_name + "\" :";
                }

                if (e_name == "")
                {
                    return "\"" + element + "\"";
                }
                return "\"" + e_name + "\"" + " : " + "\"" + element + "\"";
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

        string JsonKitTree::recursionParseJson(int node)
        {
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

            return text;
        }

        JsonKitTree::JsonKitTree()
        {
            json_kit_element = {};
            JsonKitElement h;
            json_kit_element.push_back(h);
        }

        int JsonKitTree::add_node(int parent_node, JsonKitElement node_element)
        {
            json_kit_element.push_back(node_element);
            int node_index = json_kit_element.size() - 1;
            json_kit_element[parent_node].add_children(node_index);
            return node_index;
        }

        string JsonKitTree::parseJson()
        {
            string text = recursionParseJson(0);
            return text;
        }

    };
}

