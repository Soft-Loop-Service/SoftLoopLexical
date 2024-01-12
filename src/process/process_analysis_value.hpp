
#ifndef __PRAV
#define __PRAV

#include "./process_analysis_definition.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "./../definition.hpp"


namespace ProcessVisualization{

class VariablePossession
{
private:
    map<int, int> variable_int = {};
    map<int, string> variable_string = {};
    map<int , string >variable_type = {};

public:
    VariablePossession()
    {
        variable_int = {};
    }

    string getType(int layer){

        return variable_type[layer];
    }

    void add(int layer, int value)
    {
        variable_int[layer] = value;
        variable_type[layer] = "int";
        return;
    }
    void get(int layer, int &data)
    {
        data = variable_int[layer];
    }

    void add(int layer, string value)
    {
        variable_string[layer] = value;
        variable_type[layer] = "string";

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
    ProcessScope *variable_scope;
    mapVariableProcessEnumeration variable_enumeration_map;
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
        this->variable_enumeration_map = {};
        variable_possession = new VariablePossession();
        variable_scope = new ProcessScope();
    }

    mapVariableProcessEnumeration getVariableProcessEnumeration(){
        return this->variable_enumeration_map;
    }

    int searchDeep(string value_name){
        int layer = getLayer(value_name);
        int rv = variable_scope->searchDeep(layer);
        return rv;
    }


    void deep()
    {
        variable_scope->deep();
    }
    void shallow()
    {
        variable_scope->shallow();
    }

    template <typename T>
    void newValue(string name, T element , int definition_node)
    {

        if (variable_scope->searchLast(name) == -1)
        {
            // 存在しないとき、新規追加

            int current_layer = max_layer;
            max_layer++;

            this->variable_scope->put(name, current_layer);

            string type = parseType(element);
            setValueTypeTable(current_layer, type);
            updateValue(current_layer, element);

            struct VariableProcessEnumeration new_variable_enumeration = {type,name,definition_node};
            variable_enumeration_map[current_layer] = new_variable_enumeration;
        }
    }

    bool hasLayer(string name){
        int layer = variable_scope->search(name);
        return layer != -1;
    }

    string getType(string name)
    {
        int layer = variable_scope->search(name);
        string type = variable_possession->getType(layer);
        return type;
    }

    int getLayer(string name)
    {
        int layer = variable_scope->search(name);
        return layer;
    }

    template <typename T>
    void updateValue(string name, T element)
    {
        int layer = variable_scope->search(name);
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
        int layer = variable_scope->search(name);
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



};
#endif