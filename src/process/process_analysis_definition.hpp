
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
    typedef std::map<int, VariableProcessEnumeration> mapVariableProcessEnumeration;

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
        int definition_node;
    };

    struct LayerQueuePoint
    {
        int layer;
        string text = "";
    };

    typedef vector<LayerQueuePoint> vLayerQueuePoint;
    

    class LayerQueue
    {
    private:
        vLayerQueuePoint layer_queue = {};

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
            struct LayerQueuePoint lqp = {layer};
            layer_queue.push_back(lqp);
        }
        void enqueueLayerQueue(int layer, int text_int)
        {
            string text = to_string(text_int);
            struct LayerQueuePoint lqp = {layer,text};
            layer_queue.push_back(lqp);
        }
        void enqueueLayerQueue(int layer, string text)
        {
            struct LayerQueuePoint lqp = {layer,text};
            layer_queue.push_back(lqp);
        }
        vLayerQueuePoint useLayerQueue()
        {
            vLayerQueuePoint rv = layer_queue;
            return rv;
        }
        vLayerQueuePoint useClearLayerQueue()
        {
            vLayerQueuePoint rv = layer_queue;
            clearlayerQueue();
            return rv;
        }
    };
    const int is_id_process_type_life_time_start = 1;
    const int is_id_process_type_life_time_end = 1;

    const int is_id_process_type_none = 100;
    const int is_id_process_type_input = 101;
    const int is_id_process_type_ouput = 102;
    const int is_id_process_type_logic = 103;
    const int is_id_process_type_function = 104;
    const int is_id_process_type_error = 400;
    const int is_id_process_type_warning = 401;
    const int is_id_process_type_language_error = 402;

    struct ProcessAnalysis
    {
        int process_type; // 0:None(非表示無効) 1:input 2:output 3:error 4:logic
        string message;   // 表示message
        vLayerQueuePoint layer = {};  // 0:指定なし -1:直前のlayerに合わせる -2:直後のレイヤーに合わせる

        int node_index;
    };

    class ProcessScope
    {
    private:
        vmap_str_vint layer_scope;

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
            layer_scope[last][value_name].push_back(layer);
        }

        vint searchAll(string value_name)
        {

            vint search = {};

            int size = layer_scope.size();
            int last = size - 1;

            for (int i = 0; i < size; i++)
            {
                int li = size - i - 1;

                if (has(li, value_name))
                {
                    vint layers = layer_scope[li][value_name];

                    for (int k = 0; k < layers.size(); k++)
                    {
                        search.push_back(layers[k]);
                    }
                }
            }
            return search;
        }

        int searchDeep(int search_layer)
        {
            int size = layer_scope.size();
            int last = size - 1;

            for (int i = 0; i < size; i++)
            {
                int li = size - i - 1;
                vstring name_keys = getMapKeyString(layer_scope[li]);

                for (int j = 0; j < name_keys.size(); j++)
                {

                    for (int k = 0; k < layer_scope[li][name_keys[j]].size(); k++)
                    {
                        if (layer_scope[li][name_keys[j]][k] == search_layer)
                        {
                            return i;
                        }
                    }
                }
            }

            return -1;
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
                    int layer = layer_scope[li][value_name][layer_scope[li][value_name].size() - 1];
                    return layer;
                }
            }

            return -1;
        }

        int searchLast(string value_name)
        {
            int size = layer_scope.size();
            int last = size - 1;

            if (has(last, value_name))
            {
                int layer = layer_scope[last][value_name][layer_scope[last][value_name].size() - 1];
                return layer;
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