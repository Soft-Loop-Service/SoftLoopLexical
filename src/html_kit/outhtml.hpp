
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

        Timeline::Timeline html_timeline(&syntactic_analysis_tree, &process_result , &variable_possession_union);
        string javascript_element = "";
        javascript_element +=  "<script type=\"text/javascript\"> " + html_timeline.timelineArea() + " </script>";

        string html_meta = "<!DOCTYPE html><html lang=\"ja\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>プログラムの可視化</title></head>";
        string html_header = css_style + javascript_element;

        string html_body = "";

        writing_file << html_meta << endl;
        writing_file << html_header << endl;
        writing_file << html_body << endl;

        writing_file.close();
    }
}

#endif