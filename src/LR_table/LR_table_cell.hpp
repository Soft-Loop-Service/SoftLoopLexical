

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

class LRTableLoad
{
private:
    vector<string> result;
    int point = 0;

public:
    LRTableLoad(string table_string)
    {
        string temp = "";
        for (int i = 0; i < table_string.size(); i++)
        {
            if (table_string[i] == ' ')
            {
                result.push_back(temp);
                temp = "";
                continue;
            }
            temp += table_string[i];
        }
        result.push_back(temp);
    }

    string road_token()
    {
        string text = result[point];
        point++;
        return text;
    }
};

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
    string getCellString()
    {
        return to_string(next_state);
    }

    void parseStringCell(LRTableLoad *loader)
    {
        next_state = stoi(loader->road_token());

        is_valid = next_state == -1 ? false : true;
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
    string getCellString()
    {
        return to_string(next_state);
    }
    void parseStringCell(LRTableLoad *loader)
    {
        string next = loader->road_token();
        next_state = stoi(next);
        is_valid = next == "-1" ? false : true;
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

public:
    void setCell(string token_left, vDeploymentTokenStruct token_vector)
    {
        this->reduce_formula = ReduceFormula{token_left, token_vector};
        this->is_valid = true;
    };

    void parseStringCell(LRTableLoad *loader)
    {
        string text_left = loader->road_token();
        is_valid = text_left == "-1" ? false : true;
        // printf("parseStringCell text_left %s\n",text_left.c_str());

        if (!is_valid)
        {
            return;
        }

        int token_vector_size = stoi(loader->road_token());

        vDeploymentTokenStruct token_vector;

        for (int i = 0; i < token_vector_size; i++)
        {

            int label = stoi(loader->road_token());

            string token_str = loader->road_token();

            token_vector.push_back(DeploymentTokenStruct{token_str, label});
        }

        this->reduce_formula = ReduceFormula{text_left, token_vector};
    }

    string getCellString()
    {
        if (!is_valid)
        {
            return "-1";
        }

        // 前から順に token_left ,

        string text = "";
        text += reduce_formula.token_left;
        text += " ";
        text += to_string(reduce_formula.token_vector.size());
        for (int i = 0; i < reduce_formula.token_vector.size(); i++)
        {
            text += " ";
            text += to_string(reduce_formula.token_vector[i].label);
            text += " ";
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
    string getCellString()
    {
        return to_string(is_valid);
    }
    void parseStringCell(LRTableLoad *loader)
    {
        is_valid = loader->road_token() == "1" ? true : false;
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