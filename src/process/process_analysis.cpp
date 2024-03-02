#include "./process_analysis.hpp"
namespace ProcessVisualization
{

    ProcessAnalysis::ProcessAnalysis(string process_type, string message, int depth, int node_index)
    {
        this->process_type = process_type;
        this->message = message;
        this->depth = depth;
        this->node_index = node_index;
    }

    map<int, string> VariablePossession::getVariableType()
    {
        return variable_type;
    }
    map<int, string> VariablePossession::getVariableString()
    {
        return variable_string;
    }
    map<int, int> VariablePossession::getVariableInt()
    {
        return variable_int;
    }
    void ProcessAnalysis::setVariablePossession(VariablePossession &vp)
    {
        this->variable_possession = new VariablePossession();
        this->variable_possession->setVariablePossession(vp);
    }

    void ProcessAnalysis::setPointerValueTable(mp_i_vint pvt)
    {
        this->pointer_value_table = pvt;
    }

    ProcessAnalysisTimeline::ProcessAnalysisTimeline(VariablePossessionUnion &vpu, VariablePossession &vp)
    {
        variable_possession_union = &vpu;
        variable_possession = &vp;
        process_result = {};
    }
    void ProcessAnalysisTimeline::pushProcessAnalysis(ProcessAnalysis pr)
    {
        VariablePossession vp;
        mp_i_vint pointer_value_table;
        if (process_result.size() == 0)
        {
            vp = variable_possession->copy();
            pointer_value_table = variable_possession_union->getPointerValueTable();
        }
        else
        {
            vp = variable_possession->getUpdateVariable();
            vint update_pointer_value_table = variable_possession_union->getUpdatePointerValueTable();
            mp_i_vint all_pointer = variable_possession_union->getPointerValueTable();
            for (int i = 0; i < update_pointer_value_table.size(); i++)
            {
                int up = update_pointer_value_table[i];
                pointer_value_table[up] = all_pointer[up];
            }
        }

        pr.setPointerValueTable(pointer_value_table);
        pr.setVariablePossession(vp);
        process_result.push_back(pr);
    }
    vProcessAnalysis ProcessAnalysisTimeline::getProcessResult()
    {
        return process_result;
    }

    bool ProcessScope::has(int scope, string value_name)
    {
        return this->layer_scope[scope].find(value_name) != this->layer_scope[scope].end();
    }

    ProcessScope::ProcessScope()
    {
        layer_scope = {{}};
    }

    void ProcessScope::put(string value_name, int layer)
    {
        int last = layer_scope.size() - 1;
        layer_scope[last][value_name].push_back(layer);
    }

    vint ProcessScope::searchAll(string value_name)
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

    int ProcessScope::searchDeep(int search_layer)
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

    vint ProcessScope::getLayerLast()
    {
        int size = layer_scope.size();
        int last = size - 1;

        vint layers = {};

        for (int i = 0; i < last; i++)
        {
            vstring value_list = getMapKeyString(layer_scope[last]);
            for (int j = 0; j < value_list.size(); j++)
            {
                vint scope_layers = layer_scope[i][value_list[j]];

                for (int k = 0; k < scope_layers.size(); k++)
                {
                    layers.push_back(scope_layers[k]);
                }
            }
        }

        return layers;
    }

    int ProcessScope::search(string value_name)
    {
        int size = layer_scope.size();
        int last = size - 1;

        for (int i = 0; i < size; i++)
        {
            int li = size - i - 1;

            if (has(li, value_name))
            {
                int v = layer_scope[li][value_name].size() - 1;
                int layer = layer_scope[li][value_name][v];
                //printf("search layer : %d %d %s %d %d\n", layer, li, value_name.c_str(), v, layer_scope[li][value_name].size());
                return layer;
            }
        }

        return -1;
    }

    int ProcessScope::searchLast(string value_name)
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

    void ProcessScope::deep()
    {
        layer_scope.push_back({});
    }
    void ProcessScope::shallow()
    {
        layer_scope.pop_back();
    };

    void debugProcessResult(ProcessAnalysisTimeline process_timeline)
    {
        vProcessAnalysis process_result = process_timeline.getProcessResult();

        for (int i = 0; i < process_result.size(); i++)
        {
            ProcessAnalysis current = process_result[i];

            //print("%d : %2s %s : ", i, current.process_type.c_str(), current.message.c_str());
            //print("\n");
        }
    }

};
