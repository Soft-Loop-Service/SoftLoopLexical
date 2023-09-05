

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
protected:
    char operation = LR_table_operation_none;

public:
    // virtual void setCell(int next_state);
    // virtual void debugCell();
};

class LRTableGotoCell : public LRTableCell
{
private:
    char operation = LR_table_operation_goto;

public:
    int next_state = -1;
    void setCell(int next_state)
    {
        this->next_state = next_state;
    };
    void debugCell()
    {
        if (next_state == -1)
        {
            printf("     ");
            return;
        }
        printf("%5d", next_state);
    }
};

class LRTableShiftCell : public LRTableCell
{
private:
    char operation = LR_table_operation_shift;

public:
    int next_state = -1;
    void setCell(int next_state)
    {
        this->next_state = next_state;
    };
    void debugCell()
    {
        if (next_state == -1)
        {
            printf("     ");
            return;
        }
        printf("%5d", next_state);
    }
};

class LRTableReduceCell : public LRTableCell
{
private:
    char operation = LR_table_operation_reduce;

    string token_left;
    vDeploymentTokenStruct token_vector;
    bool apply_flag = false;
    int formula_expansion_label;

public:
    void setCell(string token_left, vDeploymentTokenStruct token_vector, int formula_expansion_label)
    {
        this->token_left = token_left;
        this->token_vector = token_vector;
        this->apply_flag = true;
        this->formula_expansion_label = formula_expansion_label;
    };
    void debugCell()
    {
        if (!apply_flag)
        {
            printf("     ");
            return;
        }
        printf("%5d", formula_expansion_label);
    }
};

class LRTableAcceptCell : public LRTableCell
{
private:
    char operation = LR_table_operation_accept;
    bool accept = false;

public:
    void
    setCell(bool accept)
    {
        this->accept = accept;
    };
};

#endif