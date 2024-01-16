
#ifndef __SOFTJTREE
#define __SOFTJTREE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "./../../src/syntactic/syntactic_analysis_tree.hpp"
#include "./../../src/process/process_analysis_definition.hpp"
#include "./../../src/process/process_analysis_function.hpp"
#include "./../../src/process/process_analysis_value.hpp"

// #include "./calc.hpp"
// #include "./expr.hpp"
// #include "./extract.hpp"
// #include "./function.hpp"
// #include "./logic.hpp"
// #include "./preparation.hpp"
// #include "./recursion.hpp"
// #include "./resolution.hpp"

namespace LanguageSpecifications
{
    namespace SoftjLanguage
    {
        struct ValueEnumeration;
        struct FunctionMessagePassing;
        typedef vector<ValueEnumeration> vValueEnumeration;
        typedef vector<FunctionMessagePassing> vFunctionMessagePassing;
        typedef map<int, FunctionMessagePassing> m_i_FunctionMessagePassing;

        struct ValueEnumeration
        {
            string type;

            int node_index;
            string token;
        };

        struct FunctionMessagePassing
        {
            string function_name;
            int node_index;
            vValueEnumeration argument;
        };

        class Softj
        {

        private:
            vSyntacticTree *syntactic_analysis_tree;
            ProcessVisualization::vProcessAnalysis *process_result;
            ProcessVisualization::VariablePossessionUnion *vpu;
            ProcessVisualization::FunctionPossessionUnion *fpu;

            m_i_FunctionMessagePassing function_message_passing_map;

            bool is_action_return = false;

            bool getBool(int val)
            {
                return val > 0;
            }

        public:
            int equal(int node_index);
            string text_join(string left, string right,int node_index);
            int addition(int left, int right, int node_index);
            int subtraction(int left, int right, int node_index);
            int multiplication(int left, int right, int node_index);
            int division(int left, int right, int node_index);
            int less(int left, int right, int node_index);
            int less_equal(int left, int right, int node_index);
            int greater(int left, int right, int node_index);
            int greater_equal(int left, int right, int node_index);
            int equality(int left, int right, int node_index);
            int equality(string left, string right, int node_index);
            void assExpr(int left_index, int right_index);
            ProcessVisualization::Argument extractValueDefinition(int node_index);
            void extractArgument(int node_index, ProcessVisualization::vArgument &extract_args);
            ProcessVisualization::FunctionUnit searchFunctionMessagePassing(int node_index);
            int whileCalc(int node_index);
            int ifCalc(int node_index);
            void preparationValueEnumeration(int node_index, vValueEnumeration &args_type);
            void preparationFunctionMessagePassing(int node_index);
            void preparationFunction(int node_index);
            void recursion(int);
            void preparationTree();
            
            void resolutionFunctionMessagePassing(ProcessVisualization::FunctionUnit function_unit, FunctionMessagePassing fmp);
            void resolutionCalcFunction(int node_index);
            string resolutionCalcString(int node_index);
            int resolutionCalcInt(int node_index);

            string resolutionTreeCalcString(int node_index);
            int resolutionTreeCalcInt(int node_index);


            template <typename T>
            bool resolutionCalcValue(int node_index, T &rv_value);
            
        public:
            Softj(vSyntacticTree &syntactic_analysis_tree, ProcessVisualization::vProcessAnalysis &process_result, ProcessVisualization::VariablePossessionUnion &vpu, ProcessVisualization::FunctionPossessionUnion &fpu)
            {
                this->function_message_passing_map = {};
                this->syntactic_analysis_tree = &syntactic_analysis_tree;
                this->process_result = &process_result;
                this->vpu = &vpu;
                this->fpu = &fpu;
                
            }

            void calc(){
                preparationTree();
                recursion(0);
            }
        };
    };
};

#endif