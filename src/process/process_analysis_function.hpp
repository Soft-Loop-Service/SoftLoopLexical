
#ifndef __PRAF
#define __PRAF

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "./../definition.hpp"

namespace ProcessVisualization{


class LayerQueue
{
private:
    vint layer_queue = {};

public:
    LayerQueue()
    {
        layer_queue = {};
    }

    void clearlayerQueue()
    {
        layer_queue = {};
    }
    void enqueueLayerQueue(int layer)
    {
        layer_queue.push_back(layer);
    }
    vint useLayerQueue()
    {
        vint rv = layer_queue;
        return rv;
    }
    vint useClearLayerQueue()
    {
        vint rv = layer_queue;
        clearlayerQueue();
        return rv;
    }
};


const int is_id_process_type_none = 0;
const int is_id_process_type_input = 1;
const int is_id_process_type_ouput = 2;
const int is_id_process_type_logic = 3;

const int is_id_process_type_error = 400;
const int is_id_process_type_warning = 401;
const int is_id_process_type_language_error = 402;



struct ProcessAnalysis
{
    int process_type; // 0:None(非表示無効) 1:input 2:output 3:error 4:logic 
    string message;   // 表示message
    vint layer = {};  // 0:指定なし -1:直前のlayerに合わせる -2:直後のレイヤーに合わせる

    int node_index;
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
        int last = size - 1;

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


    void deep()
    {
        variable_scope->deep();
    }
    void shallow()
    {
        variable_scope->shallow();
    }

    template <typename T>
    void newValue(string name, T element)
    {

        if (variable_scope->searchLayer(name) == -1)
        {
            // 存在しないとき、新規追加

            int current_layer = max_layer;
            max_layer++;

            this->variable_scope->putLayer(name, current_layer);

            string type = parseType(element);
            setValueTypeTable(current_layer, type);
            updateValue(current_layer, element);
        }
    }

    bool hasLayer(string name){
        int layer = variable_scope->searchLayer(name);
        return layer != -1;
    }

    int getLayer(string name)
    {
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


};
#endif