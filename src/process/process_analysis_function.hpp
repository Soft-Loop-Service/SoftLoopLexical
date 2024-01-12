
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
        FunctionUnit()
        {
            argument_value = {{}};
            function_node = -1;
        }
        FunctionUnit(string function_name, string return_type, vArgument argument_value, int function_node)
        {
            this->function_name = function_name;
            this->return_type = return_type;
            this->argument_value = argument_value;
            this->function_node = function_node;

            printf("FunctionUnit  %s %s %d arg :",function_name.c_str() , return_type.c_str() , function_node);

            for (int i = 0 ; i < argument_value.size() ; i++){
                printf("%s %s ,",argument_value[i].name.c_str(),argument_value[i].type.c_str());
            }
            printf("\n");
        }
        void addArgumentValue(string type, string name)
        {
            this->argument_value.push_back({type, name});
        }

        int getFunctionNode()
        {
            return this->function_node;
        }
        string getFunctionName()
        {
            return this->function_name;
        }
        string getReturnType()
        {
            return this->return_type;
        }
        vArgument getArgumentValue()
        {
            return this->argument_value;
        }
        bool isMatchType(vstring match_argument_value)
        {
            if (this->argument_value.size() != match_argument_value.size())
            {
                return false;
            }

            for (int i = 0; i < match_argument_value.size(); i++)
            {
                if (this->argument_value[i].type != match_argument_value[i])
                {
                    return false;
                }
            }

            return true;
        }

        vstring isMatchType(vArgument match_argument_value)
        {
            vstring types = {};

            for (int i = 0; i < match_argument_value.size(); i++)
            {
                types.push_back(match_argument_value[i].type);
            }

            return types;
        }
    };

    class FunctionPossession
    {
    private:
        mapFunctionUnit function_set;

    public:
        FunctionPossession()
        {
            function_set = {};
        }

        void add(int address, FunctionUnit value)
        {
            function_set[address] = value;
            return;
        }
        void get(int address, FunctionUnit &data)
        {
            data = function_set[address];
        }
    };

    class FunctionPossessionUnion
    {
    private:
        int max_function_address = 1;
        ProcessScope *function_scope;
        FunctionPossession *function_possession;

    public:
        FunctionPossessionUnion()
        {
            function_scope = new ProcessScope();
            function_possession = new FunctionPossession();
        }

        void addFunction(FunctionUnit af)
        {
            int current_function_address = max_function_address;
            function_possession->add(current_function_address, af);
            function_scope->put(af.getFunctionName(), current_function_address);
            max_function_address++;
        }

        bool hasFunction(string function_name)
        {
            vint function_address_vector = function_scope->searchAll(function_name);
            return function_address_vector.size() > 0;
        }

        int hasFunction(string function_name, vstring function_types)
        {
            vint function_address_vector = function_scope->searchAll(function_name);

            for (int i = 0; i < function_address_vector.size(); i++)
            {
                int address = function_address_vector[i];

                FunctionUnit function_unit;
                function_possession->get(address, function_unit);

                if (function_unit.isMatchType(function_types))
                {
                    return address;
                }
            }

            return -1;
        }

        FunctionUnit getFunction(string function_name, vstring function_types)
        {
            int address = hasFunction(function_name, function_types);
            FunctionUnit function_unit;
            function_possession->get(address, function_unit);
            return function_unit;
        }

        void deep()
        {
            function_scope->deep();
        }
        void shallow()
        {
            function_scope->shallow();
        }
    };

};
#endif