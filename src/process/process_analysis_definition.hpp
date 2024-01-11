
#ifndef __PRAD
#define __PRAD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "./../definition.hpp"

namespace ProcessVisualization
{
    struct ProcessAnalysis;
    typedef std::vector<ProcessAnalysis> vProcessAnalysis;

    struct Argument;
    typedef std::vector<Argument> vArgument;

    struct VariableProcessEnumeration;
    typedef std::vector<VariableProcessEnumeration> vVariableProcessEnumeration;
    typedef std::map<string, VariableProcessEnumeration> mapVariableProcessEnumeration;

    const int is_id_timeline_magic_number_layer = 0;

    struct Argument
    {
        string type;
        string name;
    };

    struct VariableProcessEnumeration
    {
        string type;
        string name;
        string definition_node;
    };

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

    class ProcessScope
    {
    private:
        vmap_str_int layer_scope;

        bool has(int scope, string value_name)
        {
            return this->layer_scope[scope].find(value_name) != this->layer_scope[scope].end();
        }

    public:
        ProcessScope()
        {
            layer_scope = {{}};
        }

        void put(string value_name, int layer)
        {
            int last = layer_scope.size() - 1;
            layer_scope[last][value_name] = layer;
        }

        int search(string value_name)
        {
            int size = layer_scope.size();
            int last = size - 1;

            for (int i = 0; i < size; i++)
            {
                int li = size - i - 1;

                if (has(li, value_name))
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

};
#endif