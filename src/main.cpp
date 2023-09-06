#include "./lexical/lexical_analysis.hpp"
#include "definition.hpp"

#include "./LR_table/LR_table.hpp"
#include "./LR_table/LR_table_definition.hpp"
#include "./LR_table/LR_table_cell.hpp"
#include "./BNF/BNF.hpp"

int main()
{
    printf("start program\n");

    char *source_code = new char[source_code_size * sizeof(char)];
    loadText(source_code, "sample.txt", source_code_size);

    char **token_string = new char *[token_string_arr_size * sizeof(char *)];
    int *token_progression = new int[token_progression_arr_size * sizeof(int)];

    lexSyntax(source_code, token_string, token_progression);

    LRTableMakeGoto<LRTableGotoCell> LR_table_goto;
    LRTableMakeShift<LRTableShiftCell> LR_table_shift;
    LRTableMakeReduce<LRTableReduceCell> LR_table_reduce;
    LRTableMakeAccept<LRTableAcceptCell> LR_table_accept;

    // bnfMain(LR_table_goto, LR_table_shift, LR_table_reduce, LR_table_accept);

    free(source_code);
    // ソースコードは用済み
}