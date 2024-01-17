
#ifndef __PRAS
#define __PRAS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "./../definition.hpp"
#include "./process_analysis_space.hpp"

namespace ProcessVisualization
{

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


    struct Argument;
    typedef std::vector<Argument> vArgument;

    struct VariableProcessEnumeration;
    typedef std::vector<VariableProcessEnumeration> vVariableProcessEnumeration;
    typedef std::map<int, VariableProcessEnumeration> mapVariableProcessEnumeration;

    class ProcessAnalysis;
    typedef std::vector<ProcessAnalysis> vProcessAnalysis;
        class VariablePossession;

    class VariablePossessionUnion;

    class ProcessAnalysisTimeline;
    class ProcessScope;
    class FunctionMessagePassingUnit;
    class FunctionUnit;

    typedef vector<FunctionUnit> vFunctionUnit;
    typedef map<int, FunctionUnit> mapFunctionUnit;

    class FunctionPossession;
    class FunctionPossessionUnion;

    inline void debugProcessResult(ProcessAnalysisTimeline process_timeline);

};

#endif