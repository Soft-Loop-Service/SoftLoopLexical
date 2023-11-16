
#ifndef __PRAD
#define __PRAD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "./../definition.hpp"

class ProcessAnalysis;
typedef std::vector<ProcessAnalysis> vProcessAnalysis;

struct ProcessAnalysis
{
    string message;               // 表示message
    string relationship_variable; // 関連変数
    // string value;
};

template <typename T>
class VariablePossession
{
private:
    vector<T> variable = {};

public:
    VariablePossession()
    {
        variable = {};
    }

    void add(T value, int &address, int &size)
    {
        variable.push_back(value);

        address = variable.size() - 1;
        size = 1;
        return;
    }
    void get(int index, T &data)
    {
        data = variable[index];
    }
};

class VariablePossessionControl
{
private:
    VariablePossession<int> *vp_int;
    VariablePossession<string> *vp_string;

public:
    VariablePossessionControl()
    {
        vp_int = new VariablePossession<int>();
        vp_string = new VariablePossession<string>();
    }
    void getPointer(VariablePossession<int> *pointer)
    {
        *pointer = *vp_int;
    }
    void getPointer(VariablePossession<string> *pointer)
    {
        *pointer = *vp_string;
    }
};

#endif