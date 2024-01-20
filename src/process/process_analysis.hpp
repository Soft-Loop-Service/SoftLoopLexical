
#ifndef __PRA
#define __PRA
#include "./../definition.hpp"
#include "./../DFA/dfa.hpp"
#include "./../syntactic/syntactic_analysis.hpp"

namespace ProcessVisualization
{
    class ProcessAnalysis;
    class VariablePossession;
    class VariablePossessionUnion;
    typedef std::vector<ProcessAnalysis> vProcessAnalysis;
    class ProcessAnalysisTimeline;

    struct Argument;
    typedef std::vector<Argument> vArgument;

    struct VariableProcessEnumeration;
    typedef std::vector<VariableProcessEnumeration> vVariableProcessEnumeration;
    typedef std::map<int, VariableProcessEnumeration> mapVariableProcessEnumeration;

    class FunctionUnit;
    typedef vector<FunctionUnit> vFunctionUnit;
    typedef map<int, FunctionUnit> mapFunctionUnit;

    const int is_id_timeline_magic_number_layer = 0;

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

    void debugProcessResult(ProcessAnalysisTimeline process_timeline);

    // 引数用
    struct Argument
    {
        string type;
        string name;
    };

    //
    struct VariableProcessEnumeration
    {
        string type;
        string name;
        int layer;
        int definition_node;
    };

    class ProcessAnalysis
    {
    public:
        string process_type; // 0:None(非表示無効) 1:input 2:output 3:error 4:logic
        string message;      // 表示message
        int depth;
        int node_index;
        mp_i_vint pointer_value_table;

        VariablePossession *variable_possession;
        ProcessAnalysis(string process_type, string message, int depth, int node_index);
        void setVariablePossession(VariablePossession &vp);
        void setPointerValueTable(mp_i_vint pvt);
    };

    class ProcessAnalysisTimeline
    {
    private:
        vProcessAnalysis process_result;
        VariablePossession *variable_possession;
        VariablePossessionUnion *variable_possession_union;

    public:
        ProcessAnalysisTimeline(VariablePossessionUnion &vpu, VariablePossession &vp);
        void pushProcessAnalysis(ProcessAnalysis pr);
        vProcessAnalysis getProcessResult();
    };

    class ProcessScope
    {
    private:
        vmap_str_vint layer_scope;
        // スコープ - 変数名 - {layer}

        bool has(int scope, string value_name);

    public:
        ProcessScope();
        void put(string value_name, int layer);

        // 変数名からすべてのlayerを取得する
        vint searchAll(string value_name);

        // layerがどの深さにいるか調べる
        int searchDeep(int search_layer);

        // layerを調べる
        int search(string value_name);

        // 最深layerにいるか調べる
        int searchLast(string value_name);

        vint getLayerLast();

        void deep();
        void shallow();
    };

    class FunctionUnit;
    typedef vector<FunctionUnit> vFunctionUnit;
    typedef map<int, FunctionUnit> mapFunctionUnit;

    class FunctionMessagePassingUnit
    {
    private:
        string function_name;
        vstring types;

    public:
    };

    class FunctionUnit
    {
    private:
        string function_name;
        string return_type;
        vArgument argument_value;
        int function_node;

    public:
        FunctionUnit();
        FunctionUnit(string function_name, string return_type, vArgument argument_value, int function_node);
        void addArgumentValue(string type, string name);
        int getFunctionNode();
        string getFunctionName();
        string getReturnType();
        vArgument getArgumentValue();
        bool isMatchType(vstring match_argument_value);
        vstring isMatchType(vArgument match_argument_value);
    };

    class FunctionPossession
    {
    private:
        mapFunctionUnit function_set;

    public:
        FunctionPossession();
        void add(int address, FunctionUnit value);
        void get(int address, FunctionUnit &data);
    };

    class FunctionPossessionUnion
    {
    private:
        int max_function_address = 1;
        ProcessScope *function_scope;
        FunctionPossession *function_possession;

    public:
        FunctionPossessionUnion();
        void addFunction(FunctionUnit af);
        bool hasFunction(string function_name);
        int hasFunction(string function_name, vstring function_types);
        FunctionUnit getFunction(string function_name, vstring function_types);
        void deep();
        void shallow();
    };

    class VariablePossession
    {
    private:
        map<int, int> variable_int = {};
        map<int, string> variable_string = {};
        map<int, string> variable_type = {};
        vint update_variable = {};

    public:
        VariablePossession();
        void setVariablePossession(VariablePossession copy_vp)
        {
            this->variable_int = copy_vp.variable_int;
            this->variable_string = copy_vp.variable_string;
            this->variable_type = copy_vp.variable_type;
            this->update_variable = copy_vp.update_variable;
        };

        string getType(int layer);
        void add(int layer, int value);
        void get(int layer, int &data);
        void add(int layer, string value);
        void get(int layer, string &data);
        string getString(int layer);
        int getInt(int layer);

        VariablePossession copy()
        {
            return *this;
        }
        map<int, string> getVariableType();
        map<int, string> getVariableString();
        map<int, int> getVariableInt();
        VariablePossession getUpdateVariable();
    };

    class VariablePossessionUnion
    {
    private:
        mp_i_s value_type_table;       // その変数がどんな型なのかを管理する
        mp_i_vint pointer_value_table; // ポインタとポインタ|変数の関係性を指し示す
        vint update_pointer_value_table;

        VariablePossession *variable_possession;
        ProcessScope *variable_scope;
        mapVariableProcessEnumeration variable_enumeration_map;
        int max_layer = 1;
        int depth = 0;

        void setValueTypeTable(int layer, string type);
        string getValueTypeTable(int layer);
        bool hasValueTypeTable(int layer);
        string parseType(string element);
        bool isType(string type, string element);
        string parseType(int element);
        bool isType(string type, int element);

    public:
        VariablePossessionUnion(VariablePossession &vp);
        mapVariableProcessEnumeration getVariableProcessEnumeration();

        void setPointerValueTable(int pointer, vint children_pointer);
        void putPointerValueTable(int pointer, int child_pointer);
        vint getUpdatePointerValueTable();
        mp_i_vint getPointerValueTable();

        int searchDeep(string value_name);
        int getDepth();
        void deep();
        void shallow();
        int newPointer();
        vint newArray(int array_pointer, int len);
        vint getArrayPointers(int array_pointer);
        bool hasArrayPointer(int array_pointer);
        int getArrayPointer(string array_name);
        void newPointerValue(string name, int pointer, int definition_node);

        template <typename T>
        void newLinkPointerValue(int pointer, T element)
        {

            int current_layer = pointer;
            string type = parseType(element);
            setValueTypeTable(current_layer, type);
            updateValue(current_layer, element);
        }

        template <typename T>
        void newValue(string name, T element, int definition_node)
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

                struct VariableProcessEnumeration new_variable_enumeration = {type, name, current_layer, definition_node};
                variable_enumeration_map[current_layer] = new_variable_enumeration;
            }
        }

        bool hasLayer(string name);
        string getType(string name);
        string getType(int layer);
        int getLayer(string name);

        template <typename T>
        void updateValue(string name, T element)
        {
            int layer = variable_scope->search(name);
            updateValue(layer, element);
        }
        template <typename T>
        void updateValueNoCheck(int layer, T element)
        {
            string type = getValueTypeTable(layer);
            variable_possession->add(layer, element);
            printf("updateValueNoCheck\n");
        }

        template <typename T>
        void updateValue(int layer, T element)
        {
            if (hasValueTypeTable(layer))
            {
                updateValueNoCheck(layer, element);
            }
        }

        bool getPointer(string name, int &pointer)
        {
            int layer = variable_scope->search(name);

            if (!hasValueTypeTable(layer))
            {
                return false;
            }
            string type = getValueTypeTable(layer);
            if (type != "pointer")
            {
                return false;
            }
            int p;
            variable_possession->get(layer, p);
            pointer = p;
            return true;
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

            return true;
        };
    };

    // void debugProcessResult(ProcessAnalysisTimeline process_timeline);
    // void processAnalysis(Syntactic::vSyntacticTree syntactic_analysis_tree, LexicalAnalysis::vLexicalToken token_string_vector);
};

#endif