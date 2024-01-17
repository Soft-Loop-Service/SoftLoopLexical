#include "./process_analysis.hpp"
namespace ProcessVisualization
{

    VariablePossession::VariablePossession()
    {
        variable_int = {};
    }

    string VariablePossession::getType(int layer)
    {
        return variable_type[layer];
    }

    void VariablePossession::add(int layer, int value)
    {
        variable_int[layer] = value;
        variable_type[layer] = "int";
        return;
    }
    void VariablePossession::get(int layer, int &data)
    {
        data = variable_int[layer];
    }

    void VariablePossession::add(int layer, string value)
    {
        variable_string[layer] = value;
        variable_type[layer] = "string";

        return;
    }
    void VariablePossession::get(int layer, string &data)
    {
        data = variable_string[layer];
    };

    void VariablePossessionUnion::setValueTypeTable(int layer, string type)
    {
        this->value_type_table[layer] = type;
    }
    string VariablePossessionUnion::getValueTypeTable(int layer)
    {
        return this->value_type_table[layer];
    }
    bool VariablePossessionUnion::hasValueTypeTable(int layer)
    {
        return this->value_type_table.find(layer) != this->value_type_table.end();
    }

    string VariablePossessionUnion::parseType(string element)
    {
        return "string";
    }

    bool VariablePossessionUnion::isType(string type, string element)
    {
        return type == "string";
    }
    string VariablePossessionUnion::parseType(int element)
    {
        return "int";
    }

    bool VariablePossessionUnion::isType(string type, int element)
    {
        return type == "int";
    }

    VariablePossessionUnion::VariablePossessionUnion()
    {
        this->value_type_table = {};
        this->pointer_value_table = {};
        this->variable_enumeration_map = {};
        variable_possession = new VariablePossession();
        variable_scope = new ProcessScope();

        this->depth = 0;
    }

    mapVariableProcessEnumeration VariablePossessionUnion::getVariableProcessEnumeration()
    {
        return this->variable_enumeration_map;
    }

    int VariablePossessionUnion::searchDeep(string value_name)
    {
        int layer = getLayer(value_name);
        int rv = variable_scope->searchDeep(layer);
        return rv;
    }

    int VariablePossessionUnion::getDepth()
    {
        return this->depth;
    }
    void VariablePossessionUnion::deep()
    {
        variable_scope->deep();
        this->depth++;
    }
    void VariablePossessionUnion::shallow()
    {
        variable_scope->shallow();
        this->depth = max(depth - 1, 0);
    }

    // int linkPointerValue(int pointer , int value){
    //     pointer_value_table[pointer].push_back(value);
    // }

    int VariablePossessionUnion::newPointer()
    {
        int current_pointer = max_layer;
        max_layer++;
        string type = "pointer";
        setValueTypeTable(current_pointer, type);

        return current_pointer;
    }

    vint VariablePossessionUnion::newArray(int array_pointer, int len)
    {
        vint child_pointers = {};

        for (int i = 0; i < len; i++)
        {
            int child_current_pointer = max_layer;
            child_pointers.push_back(child_current_pointer);
            max_layer++;
        }
        pointer_value_table[array_pointer] = child_pointers;
        printf("newArray %d %d\n", array_pointer, child_pointers.size());

        return child_pointers;
    }

    vint VariablePossessionUnion::getArrayPointers(int array_pointer)
    {
        return pointer_value_table[array_pointer];
    }

    int VariablePossessionUnion::getArrayPointer(string array_name)
    {
        int pointer = this->variable_scope->search(array_name);
        return pointer;
    }

    void VariablePossessionUnion::newPointerValue(string name, int pointer, int definition_node)
    {

        if (variable_scope->searchLast(name) == -1)
        {
            int current_layer = max_layer;
            max_layer++;

            this->variable_scope->put(name, current_layer);

            string type = "pointer";
            setValueTypeTable(current_layer, type);
            updateValue(current_layer, pointer);

            struct VariableProcessEnumeration new_variable_enumeration = {type, name, definition_node};
            variable_enumeration_map[current_layer] = new_variable_enumeration;
        }
    }

    bool VariablePossessionUnion::hasLayer(string name)
    {
        int layer = variable_scope->search(name);
        return layer != -1;
    }

    string VariablePossessionUnion::getType(string name)
    {
        int layer = variable_scope->search(name);
        string type = variable_possession->getType(layer);
        return type;
    }

    string VariablePossessionUnion::getType(int layer)
    {
        string type = variable_possession->getType(layer);
        return type;
    }

    int VariablePossessionUnion::getLayer(string name)
    {
        int layer = variable_scope->search(name);
        return layer;
    }


};
