
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

    const string is_id_process_type_life_time_start = "layer_unit_station_start";
    const string is_id_process_type_life_time_end = "layer_unit_station_end";
    const string is_id_process_type_true = "layer_unit_station_true";
    const string is_id_process_type_false = "layer_unit_station_false";
    const string is_id_process_type_none = "layer_unit_station_none";
    const string is_id_process_type_input = "layer_unit_station_input";
    const string is_id_process_type_ouput = "layer_unit_station_output";
    const string is_id_process_type_logic = "layer_unit_station_logic";
    const string is_id_process_type_function = "layer_unit_station_function";
    const string is_id_process_type_error = "layer_unit_station_error";
    const string is_id_process_type_warning = "layer_unit_station_warning";
    const string is_id_process_type_language_error = "layer_unit_station_language_error";

    struct ProcessAnalysis
    {
        string process_type; // 0:None(非表示無効) 1:input 2:output 3:error 4:logic
        string message;   // 表示message
        int depth;
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