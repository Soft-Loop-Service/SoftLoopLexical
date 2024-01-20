
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
            this->return_baton = {};
            this->function_bation = {};
        }

        void Softj::calc()
        {
            try
            {
                preparationTree();
                printf("recursion start\n");
                recursion(0);
            }
            catch (...)
            {
                ProcessVisualization::ProcessAnalysis pr(ProcessVisualization::is_id_process_type_language_error, "言語処理系異常検出", vpu->getDepth(), 0);
                process_timeline->pushProcessAnalysis(pr);
                cout << "catch exception" << endl;
            }
        };
    }
};
