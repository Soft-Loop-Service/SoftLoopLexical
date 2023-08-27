
#ifndef __DFA_CALC
#define __DFA_CALC

#include "./../definition.hpp"
#include "./../symbol.hpp"
#include "./../BNF/bnf_struct.hpp"
#include "./../BNF/bnf_right.hpp"
#include "./../BNF/bnf_vector.hpp"

#include "./../item_set/item_set.hpp"
#include "./../item_set/item_set_calc.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

typedef std::vector<DfaNode> vDfaNode;

class DfaNode
{
private:
    mapDeploymentFormulaStruct formula_map;
    ItemSetStruct item_set;
    LRItemStruct lr_set;

    int dot;

public:
    DfaNode(mapDeploymentFormulaStruct formula_map, ItemSetStruct item_set, LRItemStruct lr_set, int dot)
    {
        this->formula_map = formula_map;
        this->item_set = item_set;
        this->dot = dot;
        this->lr_set = lr_set;
    }
    void nodeClosureExpansion(string search_key)
    {
    }

private:
    void recursionNodeClosureExpansion(string parent_key, string current_key)
    {
    }
};

#endif