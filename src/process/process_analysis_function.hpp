
#ifndef __PRAF
#define __PRAF

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "./../definition.hpp"

namespace ProcessVisualization
{
    class FunctionUnit
    {
    private:
        string function_name;
        string return_type;
        vArgument argument_value;
        int function_node;

    public:
        FunctionUnit()
        {
            argument_value = {{}};
        }
        FunctionUnit(string function_name, string return_type, vArgument argument_value, int function_node)
        {
            this->function_name = function_name;
            this->return_type = return_type;
            this->argument_value = argument_value;
            this->function_node = function_node;
        }
        void addArgumentValue(string type, string name)
        {
            this->argument_value.push_back({type, name});
        }

        bool isMatchType(vArgument match_argument_value)
        {
            if (this->argument_value.size() != match_argument_value.size())
            {
                return false;
            }

            for (int i = 0; i < match_argument_value.size(); i++)
            {
                if (this->argument_value[i].type != match_argument_value[i].type)
                {
                    return false;
                }
            }

            return true;
        }
    };

    class FunctionPossessionUnion
    {
        private:

        public:
        FunctionPossessionUnion(){

        }
    };

};
#endif