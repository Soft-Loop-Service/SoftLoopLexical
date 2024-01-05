
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
typedef std::vector<ProcessAnalysis> vProcessAnalysis;

struct ProcessAnalysis
{
    string message;               // 表示message
    string relationship_variable; // 関連変数
    int layer;
    // string value;
};

class VariableScope
{
private:
    vmap_str_int layer_scope;

    bool hasLayer(int scope, string value_name)
    {
        return this->layer_scope[scope].find(value_name) != this->layer_scope[scope].end();
    }

public:
    VariableScope()
    {
        layer_scope = {{}};
    }

    void putLayer(string value_name, int layer)
    {
        int last = layer_scope.size() - 1;

        layer_scope[last][value_name] = layer;
    }

    int searchLayer(string value_name)
    {
        int size = layer_scope.size();
        int last = layer_scope.size() - 1;

        for (int i = 0; i < size; i++)
        {
            int li = size - i - 1;

            if (hasLayer(li, value_name))
            {
                int layer = layer_scope[li][value_name];
                return layer;
            }
        }

        return - 1;
    }

    void deep()
    {
        layer_scope.push_back({});
    }
    void shallow()
    {
        layer_scope.pop_back();
    }
};

template <typename T>
class VariablePossession
{
private:
    map<int, T> variable = {};

public:
    VariablePossession()
    {
        variable = {};
    }

    void add(int layer, T value)
    {
        variable[layer] = value;
        return;
    }
    void get(int layer, T &data)
    {
        data = variable[layer];
    }
};

class VariablePossessionUnion
{
private:
    mp_i_s value_type_table; // その変数がどんな型なのかを管理する
    VariablePossession<int> *vp_int;
    VariablePossession<string> *vp_string;
    VariableScope *variable_scope;
    int max_layer = 0;

    void setValueTypeTable(int layer, string type)
    {
        this->value_type_table[layer] = type;
    }
    string getValueTypeTable(int layer)
    {
        return this->value_type_table[layer];
    }
    bool hasValueTypeTable(int layer)
    {
        return this->value_type_table.find(layer) != this->value_type_table.end();
    }

    string parseType(string element)
    {
        return "string";
    }

    bool isType(string type, string element)
    {
        return type == "string";
    }
    string parseType(int element)
    {
        return "int";
    }

    bool isType(string type, int element)
    {
        return type == "int";
    }

public:
    VariablePossessionUnion()
    {
        this->value_type_table = {};
        vp_int = new VariablePossession<int>();
        vp_string = new VariablePossession<string>();
        variable_scope = new VariableScope();
    }

    template <typename T>
    void newValue(string name, T element)
    {

        if (variable_scope->searchLayer(name) == -1)
        {
            // 存在しないとき、新規追加できる

            int current_layer = max_layer;
            max_layer++;

            this->variable_scope->putLayer(name, current_layer);

            string type = parseType(element);
            setValueTypeTable(current_layer, type);
            updateValue(current_layer, element);
        }
    }

    template <typename T>
    void updateValue(string name, T element)
    {
        int layer = variable_scope->searchLayer(name);
        updateValue(layer, element);
    }
    template <typename T>
    void updateValue(int layer, T element)
    {
        if (hasValueTypeTable(layer))
        {

            string type = getValueTypeTable(layer);

            if (type == "string")
            {
                vp_string->add(layer, element);
            }
            if (type == "int")
            {
                vp_int->add(layer, element);
            }
        }
    }

    template <typename T>
    void getValue(string name, T &element)
    {
        int layer = variable_scope->searchLayer(name);
        getValue(layer, element);
    }
    template <typename T>
    bool getValue(int layer, T &element)
    {
        if (!hasValueTypeTable(layer))
        {
            return false;
        }
        string type = getValueTypeTable(layer);
        if (!isType(type, element))
        {
            return false;
        }
        if (type == "string")
        {
            vp_string->get(layer, element);
        }
        if (type == "int")
        {
            vp_int->get(layer, element);
        }
    }
};

#endif