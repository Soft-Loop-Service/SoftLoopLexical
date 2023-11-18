

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
    bool is_valid = false;
    int next_state = -1;


public:
    void setCell(int next_state)
    {
        this->next_state = next_state;
        this->is_valid = true;
    };
    string getCellString(){
        return to_string(next_state);
    }

    int getCell()
    {
        return this->next_state;
    }
    int getValid()
    {
        return this->is_valid;
    }
    void debugCell()
    {
        if (next_state == -1)
        {
            printf("%10s", "");
            return;
        }
        printf("%10d", next_state);
    }
};

class LRTableShiftCell : public LRTableCell
{
private:
    char operation = LR_table_operation_shift;
    bool is_valid = false;

public:
    int next_state = -1;
    void setCell(int next_state)
    {
        this->next_state = next_state;
        this->is_valid = true;
    };
    string getCellString(){
        return to_string(next_state);
    }


    bool getValid()
    {
        return this->is_valid;
    }
    
    int getCell()
    {
        return this->next_state;
    }
    void debugCell()
    {
        if (next_state == -1)
        {
            printf("%10s", "");
            return;
        }
        printf("%10d", next_state);
    }
};

struct ReduceFormula // 構文解析用
{
    string token_left;                   // 左辺
    vDeploymentTokenStruct token_vector; // 展開したBNFの右辺
};
typedef vector<ReduceFormula> vReduceFormula;

class LRTableReduceCell : public LRTableCell
{
private:
    char operation = LR_table_operation_reduce;

    struct ReduceFormula reduce_formula;
    bool is_valid = false;
    int formula_expansion_label;

public:
    void setCell(string token_left, vDeploymentTokenStruct token_vector, int formula_expansion_label)
    {
        this->reduce_formula = ReduceFormula{token_left, token_vector};
        this->is_valid = true;
        this->formula_expansion_label = formula_expansion_label;
    };
    string getCellString(){
        string text = "";
        text += reduce_formula.token_left;
        text += ",";
        text += to_string(reduce_formula.token_vector.size());
        for (int i = 0; i < reduce_formula.token_vector.size();i++){
            text += ",";
            text += to_string(reduce_formula.token_vector[i].label);
            text += ",";
            text += reduce_formula.token_vector[i].token_str;
        }

        return text;
    }
    ReduceFormula getCell()
    {
        return this->reduce_formula;
    }
    bool getValid()
    {
        return this->is_valid;
    }
    void debugCell()
    {
        if (!is_valid)
        {
            printf("%10s", "");
            return;
        }
        printf("%10s", reduce_formula.token_left.c_str());
    }
};

class LRTableAcceptCell : public LRTableCell
{
private:
    char operation = LR_table_operation_accept;
    bool is_valid = false;

public:
    string getCellString(){
        return to_string(is_valid);
    }

    void setCell(bool is_valid)
    {
        this->is_valid = is_valid;
    };
    bool getValid()
    {
        return this->is_valid;
    }
    void debugCell()
    {
        if (!is_valid)
        {
            printf("%10s", "");
            return;
        }
        printf("%10s", "acc");
    }
};

#endif