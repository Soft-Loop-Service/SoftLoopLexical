
#ifndef __OHTML
#define __OHTML

#include "./../LR_table/LR_table.hpp"
#include "./../LR_table/LR_table_definition.hpp"
#include "./../LR_table/LR_table_cell.hpp"
#include "./../analysis/common_analysis.hpp"
#include "./../analysis/common_analysis_tree.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#include "./../../bnf_syntax/softj/softj.hpp"
#include "./../../bnf_syntax/softj/softj_tree.hpp"

// #include "./process_analysis_operation.hpp"
#include "./../process/process_analysis_definition.hpp"

void outputHtml(vProcessAnalysis process_result)
{
    std::ofstream writing_file;
    std::string filename = "test.html";
    writing_file.open(filename, std::ios::out);

    string text1 = "<!DOCTYPE html><html lang=\"ja\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>プログラムの可視化</title></head><body>";

    string text2 = "</body></html>";

    string div = "";

    for (int i = 0; i < process_result.size(); i++)
    {
        string texta1 = "<div>";
        string texta2 = "</div>";

        div += texta1;
        div += process_result[i].message;
        div += texta2;
    }

    writing_file << text1 << endl;
    writing_file << div << endl;
    writing_file << text2 << endl;

    writing_file.close();
}

#endif