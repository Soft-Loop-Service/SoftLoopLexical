
#ifndef __SOFTJ
#define __SOFTJ

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
#include "./tree.hpp"
#include "./definition.hpp"
#include "./calc.hpp"

namespace LanguageSpecifications
{
    namespace SoftjLanguage
    {
            vSyntacticTree *syntactic_analysis_tree;
            bool is_action_return = false;

        class Softj
        {

        private:

        public:
            Softj(vSyntacticTree &syntactic_analysis_tree, ProcessVisualization::vProcessAnalysis &process_result, ProcessVisualization::VariablePossessionUnion &vpu, ProcessVisualization::FunctionPossessionUnion &fpu)
            {
                this->function_message_passing_map = {};
                this->syntactic_analysis_tree = &syntactic_analysis_tree;
                this->process_result = &process_result;
                this->vpu = &vpu;
                this->fpu = &fpu;
                preparationTree();
                recursion(0);
            }
        };
    }}
#endif