#include "./process_analysis.hpp"
namespace ProcessVisualization
{

    FunctionUnit::FunctionUnit()
    {
        argument_value = {{}};
        function_node = -1;
    }
    FunctionUnit::FunctionUnit(string function_name, string return_type, vArgument argument_value, int function_node)
    {
        this->function_name = function_name;
        this->return_type = return_type;
        this->argument_value = argument_value;
        this->function_node = function_node;

        printf("FunctionUnit  %s %s %d arg :", function_name.c_str(), return_type.c_str(), function_node);

        for (int i = 0; i < argument_value.size(); i++)
        {
            printf("%s %s ,", argument_value[i].name.c_str(), argument_value[i].type.c_str());
        }
        printf("\n");
    }
    void FunctionUnit::addArgumentValue(string type, string name)
    {
        this->argument_value.push_back({type, name});
    }

    int FunctionUnit::getFunctionNode()
    {
        return this->function_node;
    }
    string FunctionUnit::getFunctionName()
    {
        return this->function_name;
    }
    string FunctionUnit::getReturnType()
    {
        return this->return_type;
    }
    vArgument FunctionUnit::getArgumentValue()
    {
        return this->argument_value;
    }
    bool FunctionUnit::isMatchType(vstring match_argument_value)
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

    vstring FunctionUnit::isMatchType(vArgument match_argument_value)
    {
        vstring types = {};

        for (int i = 0; i < match_argument_value.size(); i++)
        {
            types.push_back(match_argument_value[i].type);
        }

        return types;
    };

    FunctionPossession::FunctionPossession()
    {
        function_set = {};
    }

    void FunctionPossession::add(int address, FunctionUnit value)
    {
        function_set[address] = value;
        return;
    }
    void FunctionPossession::get(int address, FunctionUnit &data)
    {
        data = function_set[address];
    }

    FunctionPossessionUnion::FunctionPossessionUnion()
    {
        function_scope = new ProcessScope();
        function_possession = new FunctionPossession();
    }

    void FunctionPossessionUnion::addFunction(FunctionUnit af)
    {
        int current_function_address = max_function_address;
        function_possession->add(current_function_address, af);
        function_scope->put(af.getFunctionName(), current_function_address);
        max_function_address++;
    }

    bool FunctionPossessionUnion::hasFunction(string function_name)
    {
        vint function_address_vector = function_scope->searchAll(function_name);
        return function_address_vector.size() > 0;
    }

    int FunctionPossessionUnion::hasFunction(string function_name, vstring function_types)
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

    FunctionUnit FunctionPossessionUnion::getFunction(string function_name, vstring function_types)
    {
        int address = hasFunction(function_name, function_types);
        FunctionUnit function_unit;
        function_possession->get(address, function_unit);
        return function_unit;
    }

    void FunctionPossessionUnion::deep()
    {
        function_scope->deep();
    }
    void FunctionPossessionUnion::shallow()
    {
        function_scope->shallow();
    }

};
