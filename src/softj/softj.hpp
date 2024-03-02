
#ifndef __SOFTJ
#define __SOFTJ

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "./../definition.hpp"
#include "./../syntactic/syntactic_analysis.hpp"
#include "./../lexical/lexical_analysis.hpp"
#include "./../process/process_analysis.hpp"
namespace LanguageSpecifications
{
    namespace SoftjLanguage
    {
        struct ValueEnumeration;
        struct FunctionMessagePassing;
        class ReturnBaton;
        struct FunctionBaton;
        typedef vector<ValueEnumeration> vValueEnumeration;
        typedef vector<FunctionMessagePassing> vFunctionMessagePassing;
        typedef map<int, FunctionMessagePassing> m_i_FunctionMessagePassing;
        typedef vector<ReturnBaton> vReturnBaton;
        typedef vector<FunctionBaton> vFunctionBaton;

        class Softj
        {

        private:
            Syntactic::vSyntacticTree *syntactic_analysis_tree;
            ProcessVisualization::ProcessAnalysisTimeline *process_timeline;
            ProcessVisualization::VariablePossessionUnion *vpu;
            ProcessVisualization::FunctionPossessionUnion *fpu;
            m_i_FunctionMessagePassing function_message_passing_map;
            vReturnBaton return_baton;
            vFunctionBaton function_bation;

            int recursion_processing_depth = 0;

            bool is_action_return = false;

            bool getBool(int val)
            {
                return val > 0;
            }

        public:
            FunctionMessagePassing getFunctionMessagePassingMap(int index);
            Syntactic::SyntacticTreeNode getTreeNode(int node_index);
            int equal(int node_index);
            string text_join(string left, string right, int node_index);
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
            int remainder(int left, int right, int node_index);
            int inequality(int left, int right, int node_index);
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
            void resolutionFunctionExecution(ProcessVisualization::FunctionUnit function_unit, FunctionMessagePassing fmp);
            void resolutionCalcFunction(int node_index);
            string resolutionCalcString(int node_index);
            int resolutionCalcInt(int node_index);

            string resolutionTreeCalcString(int node_index);
            int resolutionTreeCalcInt(int node_index);

            void resolutionCalcArray(int node_index, int &pointer);
            void resolutionCalcNewArray(int node_index, int pointer);
            int resolutionTreeCalcArray(int node_index);
            void resolutionCalcArrayLength(int node_index, vint &length_list);
            void resolutionCalcMakeArray(int pointer, vint &length_list, string array_type, int depth);

            void setupBuidInFunction();
            void callBuildInFcuntion(ProcessVisualization::FunctionUnit function_unit, FunctionMessagePassing fmp);
            void randomFunction(ProcessVisualization::FunctionUnit function_unit, FunctionMessagePassing fmp);

            void recursionDeep();
            void recursionShallow();
            int getRecursionDeep();

            template <typename T>
            bool resolutionCalcValue(int node_index, T &rv_value)
            {
                Syntactic::SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];

                //printf("変数の解決 %s %d\n", current_node.token.c_str(), node_index);

                string value_name = current_node.token;
                //printf("cal get %s\n", value_name.c_str());
                T val;
                vpu->getValue(value_name, val);

                bool hasLayer = vpu->hasLayer(value_name);

                if (!hasLayer)
                {
                    ProcessVisualization::ProcessAnalysis pr(ProcessVisualization::is_id_process_type_error, "未定義変数のアクセス", {}, node_index);
                    process_timeline->pushProcessAnalysis(pr);
                    return false;
                }

                rv_value = val;
                return true;
            }

        public:
            Softj(Syntactic::vSyntacticTree &syntactic_analysis_tree, ProcessVisualization::ProcessAnalysisTimeline &process_timeline, ProcessVisualization::VariablePossessionUnion &vpu, ProcessVisualization::FunctionPossessionUnion &fpu);
            void calc();
        };
    };
};

struct LanguageSpecifications::SoftjLanguage::ValueEnumeration
{
    string type;
    int node_index;
    string token;
};

struct LanguageSpecifications::SoftjLanguage::FunctionMessagePassing
{
    string function_name;
    int node_index;
    vValueEnumeration argument;
};

class LanguageSpecifications::SoftjLanguage::ReturnBaton
{
private:
    string return_type;
    int return_value_int;
    // int return_value_pointer;
    string return_value_string;

public:
    string getType()
    {
        return return_type;
    }
    int getValueInt()
    {
        return return_value_int;
    }
    string getValueString()
    {
        return return_value_string;
    }
    void setValue(int val)
    {
        return_type = "int";
        return_value_int = val;
    }
    void setValue(string val)
    {
        return_type = "string";
        return_value_string = val;
    }
};
struct LanguageSpecifications::SoftjLanguage::FunctionBaton
{
    string return_type;
};
#endif