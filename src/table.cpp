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

void tableout(){

}

int main(int argc, char *argv[])
{
    LRTableMultilayer LR_table_multilayer;
    bnfMain(argv[1], LR_table_multilayer);
}