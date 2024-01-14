
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

#include "./json_kit.hpp"

#include "./timeline.hpp"


namespace HTMLParse
{


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

        Timeline::Timeline html_timeline(&syntactic_analysis_tree, &process_result , &variable_possession_union);
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