
#ifndef __PRAD
#define __PRAD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "./../definition.hpp"

class ProcessVariable;
class ProcessAnalysis;
typedef std::vector<ProcessVariable> vProcessVariable;
typedef std::vector<ProcessAnalysis> vProcessAnalysis;

class ProcessVariable
{
protected:
    string variable;
    int variable_int;
    bool is_int = false;

public:
    ProcessVariable() { printf("ProcessVariable null\n"); };
    ProcessVariable(string variable_string)
    {
        printf("ProcessVariable %s\n", variable_string.c_str());
        this->variable = variable_string;
    }
    void set(string variable_string)
    {
        this->variable = variable_string;
    }

    string get_string()
    {
        return variable;
    }
    string get() // オーバーライド用
    {
        return variable;
    }
    bool isType(string test)
    {
        return true;
    }
    bool isType(int test)
    {
        return is_int;
    }
};

class ProcessVariableInt : public ProcessVariable
{
    void set(int variable_int)
    {
        this->variable = to_string(variable_int);
        this->variable_int = variable_int;
        this->is_int = true;
    }
    int get()
    {
        return variable_int;
    }
};

class ProcessAnalysis
{
protected:
    string operation;

    ProcessVariable variable_left;
    vProcessVariable variable_right;

public:
    ProcessAnalysis(){

    };
    // void process();

    void setVariable(ProcessVariable variable_left, ProcessVariable var1, ProcessVariable var2)
    {

        this->variable_left = variable_left;
        this->variable_right = {};
        this->variable_right.push_back(var1);
        this->variable_right.push_back(var2);
    }
    void setVariableLeft(ProcessVariable variable_left)
    {
        this->variable_left = variable_left;
    }
    void setVariableRight(ProcessVariable var1, ProcessVariable var2)
    {
        this->variable_right = {};
        this->variable_right.push_back(var1);
        this->variable_right.push_back(var2);
    };

    void processAsmd()
    {
        printf("%s : %s %s %s\n", this->variable_left.get_string().c_str(), variable_right[0].get_string().c_str(), operation.c_str(), variable_right[1].get_string().c_str());
    }
};

// #define is_id_Addition 1100       // 足し算記号
// #define is_id_Subtraction 1101    // 引き算記号
// #define is_id_Multiplication 1110 // 掛け算記号
// #define is_id_Division 1111       // 割り算記号
class ProcessAnalysisCalculation : public ProcessAnalysis
{
public:
    ProcessAnalysisCalculation();
    ProcessAnalysisCalculation(string operation)
    {
        this->operation = operation;
    }
};
#endif