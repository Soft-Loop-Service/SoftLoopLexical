#include "./lexical/lexical_analysis.hpp"
#include "./analysis/table_analysis.hpp"

#include "./syntactic/syntactic_analysis_tree.hpp"
#include "./syntactic/syntactic_parse_tree.hpp"

#include "./process/process_analysis.hpp"

#include "definition.hpp"
#include "./LR_table/LR_table.hpp"
#include "./LR_table/LR_table_definition.hpp"
#include "./LR_table/LR_table_cell.hpp"
#include "./BNF/BNF.hpp"
#include <fstream>

// 第一引数 : 構文定義ファイル
int main(int argc, char *argv[])
{
    LRTableMultilayer LR_table_multilayer;
    bnfMain(argv[1], LR_table_multilayer);

    LRTable table_accept = LR_table_multilayer.LR_table_accept;
    LRTable table_goto = LR_table_multilayer.LR_table_goto;
    LRTable table_reduce = LR_table_multilayer.LR_table_reduce;
    LRTable table_shift = LR_table_multilayer.LR_table_shift;

    string table_accept_string = table_accept.outputTable();
    string table_goto_string = table_goto.outputTable();
    string table_reduce_string = table_reduce.outputTable();
    string table_shift_string = table_shift.outputTable();

    std::ofstream writing_file;
    std::string filename = "table.txt";
    writing_file.open(filename, std::ios::out);

    writing_file << table_accept_string << endl;
    writing_file << table_goto_string << endl;
    writing_file << table_reduce_string << endl;
    writing_file << table_shift_string << endl;

    writing_file.close();
}