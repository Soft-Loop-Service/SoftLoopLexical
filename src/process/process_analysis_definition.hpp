
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
    int layer = 0;                  // 0:指定なし -1:直前のlayerに合わせる -2:直後のレイヤーに合わせる
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

        return -1;
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

class VariablePossession
{
private:
    map<int, int> variable_int = {};
    map<int, string> variable_string = {};

public:
    VariablePossession()
    {
        variable_int = {};
    }

    void add(int layer, int value)
    {
        variable_int[layer] = value;
        return;
    }
    void get(int layer, int &data)
    {
        data = variable_int[layer];
    }

    void add(int layer, string value)
    {
        variable_string[layer] = value;
        return;
    }
    void get(int layer, string &data)
    {
        data = variable_string[layer];
    }
};

class VariablePossessionUnion
{
private:
    mp_i_s value_type_table; // その変数がどんな型なのかを管理する
    VariablePossession *variable_possession;
    VariableScope *variable_scope;
    int max_layer = 1;

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
        variable_possession = new VariablePossession();
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

    int getLayer(string name){
        int layer = variable_scope->searchLayer(name);
        return layer;
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
            variable_possession->add(layer, element);
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

        variable_possession->get(layer, element);
    }
};

#endif