

#ifndef __HTML_KIT
#define __HTML_KIT
#include "./../definition.hpp"
#include "./../DFA/dfa.hpp"
#include "./../process/process_analysis.hpp"
#include "./../syntactic/syntactic_analysis.hpp"
#include "./../lexical/lexical_analysis.hpp"

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
            mapstr event;
            HtmlKitElement();
            HtmlKitElement(string e_tag);
            void addEClass(string e);
            void addEvent(string n, string e);
            void setEId(string e_id);
            void setElement(string element);
            void add_children(int index);
            string parseHtmlStartTag();
            string parseHtmlElement();
            string parseHtmlEndTag();
        };

        class HtmlKitTree
        {

        private:
            vHtmlKitElement html_kit_element;
            string recursionParseHtml(int node);

        public:
            HtmlKitTree();
            int add_node(int parent_node, HtmlKitElement node_element);
            string parseHtml();
        };
    }
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
            bool isValue();
            bool isArray();
            bool isDist();

        public:
            vint children;
            JsonKitElement();
            JsonKitElement(string type);
            JsonKitElement(string type, string name);
            JsonKitElement(string type, string name, string e);
            JsonKitElement(string type, string name, int e);
            void add_children(int index);
            void set_element(string element);
            void set_element(int element);
            string parseJsonStart();
            string parseJsonEnd();
            string parseJsonElement();
        };

        class JsonKitTree
        {

        private:
            vJsonKitElement json_kit_element;
            string recursionParseJson(int node);

        public:
            JsonKitTree();
            int add_node(int parent_node, JsonKitElement node_element);
            string parseJson();
        };

    };

    namespace Conversion
    {
        class SourceCodeView
        {
        private:
            Syntactic::vSyntacticTree *syntactic_analysis_tree_p;
            ProcessVisualization::vProcessAnalysis *process_result_p;
            ProcessVisualization::VariablePossessionUnion *variable_possession_union_p;
            HTMLKit::HtmlKitTree html_kit_tree;
            LexicalAnalysis::vLexicalToken *token_string_vector_p;

            void tokenConversion(int parent_index);
            int codelineBlock(int parent_index);
            void tokenBlock(int token_index, int parent_index, LexicalAnalysis::LexicalToken lexical_token);

        public:
            SourceCodeView(Syntactic::vSyntacticTree *syntactic_analysis_tree_p, ProcessVisualization::vProcessAnalysis *process_result_p, ProcessVisualization::VariablePossessionUnion *variable_possession_union_p, LexicalAnalysis::vLexicalToken *token_string_vector_p);
            string getBody();
        };

        class Timeline
        {

        private:
            Syntactic::vSyntacticTree *syntactic_analysis_tree_p;
            ProcessVisualization::vProcessAnalysis *process_result_p;
            ProcessVisualization::VariablePossessionUnion *variable_possession_union_p;
            JsonKit::JsonKitTree json_kit_tree_process;
            JsonKit::JsonKitTree json_kit_tree_meta;

            HTMLKit::HtmlKitTree html_kit_tree;
            LexicalAnalysis::vLexicalToken *token_string_vector_p;
            ProcessVisualization::mapVariableProcessEnumeration variable_enumeration_map;

            int depth_length;
            void timelineLeftArea(int process_order, int html_parent_node, ProcessVisualization::ProcessAnalysis process);
            void timelineRightArea(int process_order, int html_parent_node, ProcessVisualization::ProcessAnalysis process);
            int timelineCommonArea(int process_order, int html_parent_node, ProcessVisualization::ProcessAnalysis process);
            void timelineMessageArea(int html_parent_node, ProcessVisualization::ProcessAnalysis process);
            void timelineLineColumnArea(int html_parent_node, ProcessVisualization::ProcessAnalysis process);
            void timelineLayerArea(int html_parent_node, ProcessVisualization::ProcessAnalysis process);
            void timelineLayerInputArea(int html_parent_node, ProcessVisualization::ProcessAnalysis process, int unit_num);
            int timelineLayerUnitArea(int html_parent_node, ProcessVisualization::ProcessAnalysis process, int unit_num);
            void timelineLayerUnitStationArea(int html_parent_node, ProcessVisualization::ProcessAnalysis process, HTMLKit::HtmlKitElement layer_unit_station_area);
            void meta_data();
            void process_group();
            void process(int process_index, int kit_index);

        public:
            Timeline(Syntactic::vSyntacticTree *syntactic_analysis_tree_p, ProcessVisualization::vProcessAnalysis *process_result_p, ProcessVisualization::VariablePossessionUnion *variable_possession_union_p, LexicalAnalysis::vLexicalToken *token_string_vector_p);
            string getBody();
            string getJson();
        };
    }
    void outputHtml(Syntactic::vSyntacticTree syntactic_analysis_tree, ProcessVisualization::ProcessAnalysisTimeline process_timeline, ProcessVisualization::VariablePossessionUnion variable_possession_union, LexicalAnalysis::vLexicalToken token_string_vector);

};

#endif