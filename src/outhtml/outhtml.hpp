
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

namespace Timeline
{
    class HtmlTimeLine
    {

    private:
        vProcessAnalysis *process_result;
        string timelineLayerBlockArea()
        {
        }

        string timelineLayerArea()
        {
        }

    public:
        HtmlTimeLine(vProcessAnalysis process_result)
        {
            this->process_result = &process_result;
        }

        string timelineArea()
        {
            for (int i = 0; i < process_result->size(); i++)
            {
                ProcessAnalysis pr = (*this->process_result)[i];
            }
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

#endif