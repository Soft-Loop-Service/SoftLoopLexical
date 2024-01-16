
#ifndef __SOURCE_CODE
#define __SOURCE_CODE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#include "./../../../bnf_syntax/softj/softj_tree.hpp"
#include "./../../process/process_analysis_definition.hpp"
#include "./../../lexical/lexical_analysis_definition.hpp"

#include "./../kit/json_kit.hpp"
#include "./../kit/html_kit.hpp"

namespace HTMLParse
{

    namespace Conversion
    {
        class SourceCodeView
        {
        private:
            vSyntacticTree *syntactic_analysis_tree_p;
            ProcessVisualization::vProcessAnalysis *process_result_p;
            ProcessVisualization::VariablePossessionUnion *variable_possession_union_p;
            HTMLKit::HtmlKitTree html_kit_tree;
            vLexicalToken *token_string_vector_p;

            void tokenConversion(int parent_index)
            {
                int line = -1;
                int line_index;
                for (int i = 0; i < token_string_vector_p->size() - 1; i++)
                {
                    LexicalToken current_token = (*token_string_vector_p)[i];

                    if (line < current_token.source_code_line){
                        line = current_token.source_code_line;
                        line_index = codelineBlock(parent_index );
                    }

                    tokenBlock(i,line_index,current_token);
                }
            }
            int codelineBlock(int parent_index)
            {
                HTMLKit::HtmlKitElement codeline_area("div");
                codeline_area.addEClass("codeline");
                int codeline_index = html_kit_tree.add_node(parent_index, codeline_area);
                return codeline_index;
            }
            void tokenBlock(int token_index,int parent_index,LexicalToken lexical_token)
            {
                HTMLKit::HtmlKitElement token_area("div");
                token_area.addEClass("token");
                token_area.setElement(lexical_token.token);

                string e_id = "token" + to_string(token_index);
                token_area.setEId(e_id);
                html_kit_tree.add_node(parent_index, token_area);   
                
            }
        public:
            SourceCodeView(vSyntacticTree *syntactic_analysis_tree_p, ProcessVisualization::vProcessAnalysis *process_result_p, ProcessVisualization::VariablePossessionUnion *variable_possession_union_p, vLexicalToken *token_string_vector_p)
            {
                this->syntactic_analysis_tree_p = syntactic_analysis_tree_p;
                this->process_result_p = process_result_p;
                this->variable_possession_union_p = variable_possession_union_p;
                this->html_kit_tree = HTMLKit::HtmlKitTree();
                this->token_string_vector_p = token_string_vector_p;
                ProcessVisualization::mapVariableProcessEnumeration variable_enumeration_map = variable_possession_union_p->getVariableProcessEnumeration();
            }

            string getBody()
            {
                HTMLKit::HtmlKitElement source_code_area("div");
                source_code_area.addEClass("source_code_view");
                int source_code_area_index = html_kit_tree.add_node(0, source_code_area);

                HTMLKit::HtmlKitElement source_code_scroll_area("div");
                source_code_scroll_area.addEClass("source_code_view_scroll");
                int source_code_scroll_area_index = html_kit_tree.add_node(source_code_area_index, source_code_scroll_area);

                tokenConversion(source_code_scroll_area_index);
                string html_txt = html_kit_tree.parseHtml();
                return html_txt;
            }
        };
    }
};

#endif