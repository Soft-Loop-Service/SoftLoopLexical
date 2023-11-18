#include "./lexical/lexical_analysis.hpp"
#include "./syntactic/syntactic_analysis.hpp"
#include "./syntactic/syntactic_analysis_tree.hpp"
#include "./syntactic/syntactic_parse_tree.hpp"

#include "./process/process_analysis.hpp"

#include "definition.hpp"
#include "./LR_table/LR_table.hpp"
#include "./LR_table/LR_table_definition.hpp"
#include "./LR_table/LR_table_cell.hpp"
#include "./BNF/BNF.hpp"

int inputTable(string table_file, LRTableMultilayer &LR_table_multilayer)
{
    std::ifstream ifs(table_file);
    printf("inputTable\n");

    string table_accept_string;
    string table_goto_string;
    string table_reduce_string;
    string table_shift_string;
    if (ifs.fail())
    {
        std::cout << "Failed to open file." << std::endl;
        return -1;
    }
    getline(ifs, table_accept_string);

    printf("%s\n", table_accept_string.c_str());

    getline(ifs, table_goto_string);
    printf("%s\n", table_goto_string.c_str());

    getline(ifs, table_reduce_string);
    printf("%s\n", table_reduce_string.c_str());

    getline(ifs, table_shift_string);
    printf("%s\n", table_shift_string.c_str());

    LR_table_multilayer = LRTableMultilayer{
        LRTableMakeGoto<LRTableGotoCell>(table_goto_string),
        LRTableMakeShift<LRTableShiftCell>(table_shift_string),
        LRTableMakeReduce<LRTableReduceCell>(table_reduce_string),
        LRTableMakeAccept<LRTableAcceptCell>(table_accept_string)};

    // LR_table_multilayer.LR_table_goto.debug();
    // LR_table_multilayer.LR_table_shift.debug();
    LR_table_multilayer.LR_table_reduce.debug();
    // LR_table_multilayer.LR_table_accept.debug();

    printf("inputTable end\n");
}