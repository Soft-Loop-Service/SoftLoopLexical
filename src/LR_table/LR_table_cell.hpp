

#ifndef __LRTABLECELL
#define __LRTABLECELL

#include "./../definition.hpp"
#include "./../symbol.hpp"
#include "./../BNF/bnf_struct.hpp"
#include "./../BNF/bnf_right.hpp"

#include "./../item_set/item_set.hpp"
#include "./../DFA/dfa_calc.hpp"
#include "./../DFA/lr_item.hpp"
#include "./../DFA/closure_expansion.hpp"
#include "./../DFA/dfa.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <map>

#define LR_table_operation_none 'n'
#define LR_table_operation_shift 's'
#define LR_table_operation_reduce 'r'
#define LR_table_operation_accept 'a'
#define LR_table_operation_goto 'g'

class LRTableCell
{
private:
    char operation = LR_table_operation_none;

public:
    // virtual void setCell();
    // virtual string debugCell();
};

class LRTableGotoCell : LRTableCell
{
private:
    char operation = LR_table_operation_goto;

public:
    void setCell();
};

class LRTableShiftCell : LRTableCell
{
private:
    char operation = LR_table_operation_shift;

public:
    void setCell();
};

class LRTableReduceCell : LRTableCell
{
private:
    char operation = LR_table_operation_reduce;

public:
    void setCell();
};

class LRTableAcceptCell : LRTableCell
{
private:
    char operation = LR_table_operation_accept;

public:
    void setCell();
};

#endif