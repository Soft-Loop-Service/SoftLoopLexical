#include "./../html_kit.hpp"

namespace HTMLParse
{
    namespace HTMLKit
    {

        HtmlKitElement::HtmlKitElement()
        {
            this->e_tag = "";
            this->e_id = "";
            this->e_class = {};
            this->children = {};
            this->event = {};
        }

        HtmlKitElement::HtmlKitElement(string e_tag)
        {
            this->e_tag = e_tag;
            this->e_id = "";
            this->e_class = {};
            this->children = {};
            this->event = {};
        }

        void HtmlKitElement::addEClass(string e)
        {
            this->e_class.push_back(e);
        }
        void HtmlKitElement::addEvent(string n, string e)
        {
            this->event[n] = e;
        }

        void HtmlKitElement::setEId(string e_id)
        {
            this->e_id = e_id;
        }

        void HtmlKitElement::setElement(string element)
        {
            this->element = element;
        }
        void HtmlKitElement::add_children(int index)
        {
            children.push_back(index);
        }
        string HtmlKitElement::parseHtmlStartTag()
        {
            if (e_tag == "")
            {
                return "";
            }

            string text = "";

            text += "<";
            text += e_tag;
            text += " ";

            vstring event_keys = getMapKeyString(event);
            for (int i = 0; i < event_keys.size(); i++)
            {
                text += event_keys[i];
                text += "=";
                text += event[event_keys[i]];
                text += " ";
            }

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
                text += "\"";
                text += e_id;
                text += "\"";
                text += " ";
            }
            text += ">";
            return text;
        }
        string HtmlKitElement::parseHtmlElement()
        {
            if (e_tag == "")
            {
                return "";
            }
            string text = "";
            text += element;
            return text;
        }
        string HtmlKitElement::parseHtmlEndTag()
        {
            if (e_tag == "")
            {
                return "";
            }
            string text = "";
            text += "<";
            text += "/";
            text += e_tag;
            text += ">";
            return text;
        }

        string HtmlKitTree::recursionParseHtml(int node)
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

        HtmlKitTree::HtmlKitTree()
        {
            html_kit_element = {};
            HtmlKitElement h;
            html_kit_element.push_back(h);
        }

        int HtmlKitTree::add_node(int parent_node, HtmlKitElement node_element)
        {
            html_kit_element.push_back(node_element);

            int node_index = html_kit_element.size() - 1;
            html_kit_element[parent_node].add_children(node_index);
            return node_index;
        }

        string HtmlKitTree::parseHtml()
        {
            string text = recursionParseHtml(0);
            return text;
        }
    };

}
