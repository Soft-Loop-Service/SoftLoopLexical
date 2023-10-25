#include "./lexical/lexical_analysis.hpp"
#include "./syntactic/syntactic_analysis.hpp"
#include "./syntactic/syntactic_purse_tree.hpp"

#include "definition.hpp"

#include "./LR_table/LR_table.hpp"
#include "./LR_table/LR_table_definition.hpp"
#include "./LR_table/LR_table_cell.hpp"
#include "./BNF/BNF.hpp"

int main(int argc, char *argv[])
{
    printf("start program\n");

    char *source_code = new char[source_code_size * sizeof(char)];
    loadText(source_code, "sample.txt", source_code_size);

    char **token_string = new char *[token_string_arr_size * sizeof(char *)];
    int *token_progression = new int[token_progression_arr_size * sizeof(int)];

    lexSyntax(source_code, token_string, token_progression);
    vstring token_string_vector = getTokenString(token_string, token_progression);

    delete source_code;
    delete token_string;
    delete token_progression;
    output_vector("token_string_vector", token_string_vector);

    LRTableMultilayer LR_table_multilayer;

    bnfMain(argv[1], LR_table_multilayer);
    vReduceFormula ans_analysis = syntacticAnalysis(LR_table_multilayer, token_string_vector);

    // ソースコードは用済み
}