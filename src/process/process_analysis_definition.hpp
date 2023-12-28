
#ifndef __PRAD
#define __PRAD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "./../definition.hpp"

struct ProcessAnalysis;
class VariableAddress;
typedef std::vector<ProcessAnalysis> vProcessAnalysis;
typedef vector<VariableAddress> vVariableAddress;

struct VariableList
{
    /* data */
};

struct ProcessAnalysis
{
    string message;               // 表示message
    string relationship_variable; // 関連変数
    // string value;
};

class VariableAddress
{
    mp_s_i address_table;

private:
public:
    VariableAddress()
    {
        address_table = {};
    }
    void put(string value_name, int address)
    {
        this->address_table[value_name] = address;
    }
    void get(string value_name, int &address)
    {
        address = this->address_table[value_name];
    }
    vector<string> get_keys(string value_name)
    {
        vector<string> keys;
        for (auto it = address_table.begin(); it != address_table.end(); it++)
        {
            keys.push_back(it->first);
        }
        return keys;
    }
    bool has_keys(string value_name)
    {
        for (auto it = address_table.begin(); it != address_table.end(); it++)
        {
            string key = it->first;
            if (key == value_name)
            {
                return true;
            }
        }
        return false;
    }
};

class VariableScope
{
private:
    int depth = 0;
    vVariableAddress address_table;

public:
    VariableScope()
    {
        address_table = {};
    }
    void deep()
    {
        depth++;
        VariableAddress va;
        this->address_table.push_back(va);
    }
    void shallow()
    {
        depth--;
        this->address_table.pop_back();
    }

    // 格納先を決める
    void add(string value_name, int &address)
    {
        int table_size = address_table.size();
        address_table[table_size - 1].put(value_name, address);
    }

    // 格納先を走査する
    void inquiry(string value_name, int &address)
    {
        address = -1;
        for (int i = 0; i < this->address_table.size(); i++)
        {
            int li = this->address_table.size() - i - 1;
            bool has_key = address_table[li].has_keys(value_name);

            if (has_key)
            {
                address_table[li].get(value_name, address);
                printf("inquiry haskey %d \n", address);

                return;
            }
        }

        return;
    }
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
    void get(int address, T &data)
    {
        data = variable[address];
    }
};

class VariablePossessionUnion
{
private:
    VariablePossession<int> *vp_int;
    VariablePossession<string> *vp_string;
    VariableScope *variable_scope;

public:
    VariablePossessionUnion()
    {
        vp_int = new VariablePossession<int>();
        vp_string = new VariablePossession<string>();
        variable_scope = new VariableScope();
        variable_scope->deep();
    }

    void add(int value, string value_name, int &size)
    {
        int address;
        vp_int->add(value, address, size);

        this->variable_scope->add(value_name, address);
    }
    void add(string value, string value_name, int &size)
    {
        int address;
        vp_string->add(value, address, size);

        this->variable_scope->add(value_name, address);
    }
    void get(string value_name, int &data)
    {
        int address;
        this->variable_scope->inquiry(value_name, address);
        vp_int->get(address, data);
    }
    void get(string value_name, string &data)
    {
        int address;
        this->variable_scope->inquiry(value_name, address);
        vp_string->get(address, data);
    }
};

#endif