
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "./softj.hpp"

namespace LanguageSpecifications
{
    namespace SoftjLanguage
    {
        Softj::Softj(Syntactic::vSyntacticTree &syntactic_analysis_tree, ProcessVisualization::ProcessAnalysisTimeline &process_timeline, ProcessVisualization::VariablePossessionUnion &vpu, ProcessVisualization::FunctionPossessionUnion &fpu)
        {
            this->function_message_passing_map = {};
            this->syntactic_analysis_tree = &syntactic_analysis_tree;
            this->process_timeline = &process_timeline;
            this->vpu = &vpu;
            this->fpu = &fpu;
        }

        void Softj::calc()
        {
            preparationTree();
            recursion(0);
        };
    }
};
