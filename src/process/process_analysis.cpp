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

    ProcessAnalysisTimeline::ProcessAnalysisTimeline()
    {
        process_result = {};
    }
    void ProcessAnalysisTimeline::pushProcessAnalysis(ProcessAnalysis pr)
    {
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

    int ProcessScope::search(string value_name)
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

            printf("%d : %2s %s : ", i, current.process_type.c_str(), current.message.c_str());

            // for (int j = 0 ; j < current.layer.size() ; j++){
            //     printf(" %d",current.layer[j].layer);
            // }

            printf("\n");
        }
    }

    void processAnalysis(Syntactic::vSyntacticTree syntactic_analysis_tree, LexicalAnalysis::vLexicalToken token_string_vector)
    {
        printf("processAnalysis\n");
        vint parent_stack = {};

        ProcessAnalysisTimeline process_timeline;

        VariablePossessionUnion variable_possession_union;
        FunctionPossessionUnion function_possession_union;
        LanguageSpecifications::SoftjLanguage::Softj softjtree(syntactic_analysis_tree, process_timeline, variable_possession_union, function_possession_union);
        softjtree.calc();

        debugProcessResult(process_timeline);
        HTMLParse::outputHtml(syntactic_analysis_tree, process_timeline, variable_possession_union, token_string_vector);
    }


};
