
#ifndef __LRTABLE
#define __LRTABLE

#define LR_table_operation_none 'n'
#define LR_table_operation_shift 's'
#define LR_table_operation_reduce 'r'
#define LR_table_operation_accept 'a'
#define LR_table_operation_goto 'g'
#include "./../DFA/dfa.hpp"
#include "./../BNF/bnf.hpp"
#include "./../definition.hpp"
#include "./../symbol.hpp"
#include "./LR_table_definition.hpp"
#include "./LR_table_template.hpp"

namespace LRTable
{
    
};

#endif