
#ifndef __PRA
#define __PRA
#include "./../definition.hpp"
#include "./../DFA/dfa.hpp"
#include "./../syntactic/syntactic_analysis.hpp"

namespace ProcessVisualization
{
    class ProcessAnalysis;
    typedef std::vector<ProcessAnalysis> vProcessAnalysis;
    class ProcessAnalysisTimeline;

    struct Argument;
    typedef std::vector<Argument> vArgument;

    struct VariableProcessEnumeration;
    typedef std::vector<VariableProcessEnumeration> vVariableProcessEnumeration;
    typedef std::map<int, VariableProcessEnumeration> mapVariableProcessEnumeration;
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

    class ProcessAnalysis
    {
    public:
        string process_type; // 0:None(非表示無効) 1:input 2:output 3:error 4:logic
        string message;      // 表示message
        int depth;
        int node_index;

        ProcessAnalysis(string process_type, string message, int depth, int node_index);
    };

    class ProcessAnalysisTimeline
    {
    private:
        vProcessAnalysis process_result;

    public:
        ProcessAnalysisTimeline();
        void pushProcessAnalysis(ProcessAnalysis pr);
        vProcessAnalysis getProcessResult();
    };
    ;

    class ProcessScope
    {
    private:
        vmap_str_vint layer_scope;

        bool has(int scope, string value_name);

    public:
        ProcessScope();
        void put(string value_name, int layer);
        vint searchAll(string value_name);
        int searchDeep(int search_layer);
        int search(string value_name);
        int searchLast(string value_name);
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

    public:
        VariablePossession();
        string getType(int layer);
        void add(int layer, int value);
        void get(int layer, int &data);
        void add(int layer, string value);
        void get(int layer, string &data);
    };

    class VariablePossessionUnion
    {
    private:
        mp_i_s value_type_table;       // その変数がどんな型なのかを管理する
        mp_i_vint pointer_value_table; // ポインタとポインタ|変数の関係性を指し示す

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
        VariablePossessionUnion();
        mapVariableProcessEnumeration getVariableProcessEnumeration();
        int searchDeep(string value_name);
        int getDepth();
        void deep();
        void shallow();
        int newPointer();
        vint newArray(int array_pointer, int len);
        vint getArrayPointers(int array_pointer);
        int getArrayPointer(string array_name);
        void newPointerValue(string name, int pointer, int definition_node);
        template <typename T>
        void newLinkPointerValue(int pointer, T element);

        template <typename T>
        void newValue(string name, T element, int definition_node);
        bool hasLayer(string name);
        string getType(string name);
        string getType(int layer);
        int getLayer(string name);
        template <typename T>
        void updateValue(string name, T element);
        template <typename T>
        void updateValueNoCheck(int layer, T element);
        template <typename T>
        void updateValue(int layer, T element);

        template <typename T>
        void getValue(string name, T &element);
        template <typename T>
        bool getValue(int layer, T &element);


    };

    // void debugProcessResult(ProcessAnalysisTimeline process_timeline);
    // void processAnalysis(Syntactic::vSyntacticTree syntactic_analysis_tree, LexicalAnalysis::vLexicalToken token_string_vector);
};

#endif