#include "./lexical/lexical_analysis.hpp"
#include "./syntactic/syntactic_analysis.hpp"
#include "./process/process_analysis.hpp"
#include "definition.hpp"
#include "./LR_table/LR_table.hpp"
#include "./BNF/BNF.hpp"

int main(int argc, char *argv[])
{
    LRTable::LRTableMultilayer LR_table_multilayer;
    BNFParse::bnfMain(argv[1], LR_table_multilayer);

    LRTable::LRTable table_accept = LR_table_multilayer.LR_table_accept;
    LRTable::LRTable table_goto = LR_table_multilayer.LR_table_goto;
    LRTable::LRTable table_reduce = LR_table_multilayer.LR_table_reduce;
    LRTable::LRTable table_shift = LR_table_multilayer.LR_table_shift;

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