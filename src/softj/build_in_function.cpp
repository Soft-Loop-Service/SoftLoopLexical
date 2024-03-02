
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "./softj.hpp"
#include <random>

namespace LanguageSpecifications
{
    namespace SoftjLanguage
    {
        void Softj::setupBuidInFunction()
        {
            ProcessVisualization::Argument rn1 = {"int", "min"};
            ProcessVisualization::Argument rn2 = {"int", "max"};
            ProcessVisualization::vArgument v_rn = {rn1, rn2};

            ProcessVisualization::FunctionUnit fu_random("RANDOM", "int", v_rn);
            fu_random.setBuiltInFunction(1);
            fpu->addFunction(fu_random);
        }

        void Softj::callBuildInFcuntion(ProcessVisualization::FunctionUnit function_unit, FunctionMessagePassing fmp)
        {

            int function_id = function_unit.getBuiltInFunction();

            if (function_id == 1)
            {
                randomFunction(function_unit, fmp);
            }
        }

        void Softj::randomFunction(ProcessVisualization::FunctionUnit function_unit, FunctionMessagePassing fmp)
        {
            int min;
            int max;
            vpu->getValue("min", min);
            vpu->getValue("max", max);
            //printf("min max %d %d %d\n", min, max);

            std::random_device rd;
            std::default_random_engine eng(rd());
            std::uniform_int_distribution<int> distr(min, max);

            int rn_int = distr(eng);
            //printf("min max rn_int %d %d %d\n", min, max, rn_int);

            ReturnBaton rb;
            rb.setValue(rn_int);
            return_baton.push_back({rb});
        }
    }
};
