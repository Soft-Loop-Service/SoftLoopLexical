
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

    string process_analysis_type = "analysis";

public:
    ProcessAnalysis(){};
    virtual void set(){};
    virtual void process(){};
    virtual void process(string operation){};

    bool isAnalysisType(string text)
    {
        return text == process_analysis_type;
    }

    void setVariable(ProcessVariable variable_left, ProcessVariable var1, ProcessVariable var2)
    {

        this->variable_left = variable_left;
        this->variable_right = {};
        this->variable_right.push_back(var1);
        this->variable_right.push_back(var2);
    }
    void setVariable(ProcessVariable variable_left, ProcessVariable var1)
    {

        this->variable_left = variable_left;
        this->variable_right = {};
        this->variable_right.push_back(var1);
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
};

class ProcessAnalysisCalculation : public ProcessAnalysis
{

public:
    void set(string operation)
    {
        process_analysis_type = "calculation";
        this->operation = operation;
    }
    void process() override
    {
        printf("%s : %s %s %s\n", this->variable_left.get_string().c_str(), variable_right[0].get_string().c_str(), operation.c_str(), variable_right[1].get_string().c_str());
    }
};
class ProcessAnalysisEqual : public ProcessAnalysis
{
public:
    void set() override
    {
        process_analysis_type = "equal";
        this->operation = "=";
    }
    void process() override
    {
        printf("%s = %s\n", this->variable_left.get_string().c_str(), variable_right[0].get_string().c_str());
    }
};
class ProcessAnalysisNewVal : public ProcessAnalysis
{

public:
    void set()
    {
        process_analysis_type = "newval";
        this->operation = "newval";
    }
    void set(string operation){};
    void process()
    {
        printf("%s %s\n", this->variable_left.get_string().c_str(), variable_right[0].get_string().c_str());
    }
};
#endif