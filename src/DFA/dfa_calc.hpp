
#ifndef __DFA_CALC
#define __DFA_CALC

#include "./../definition.hpp"
#include "./../symbol.hpp"
#include "./../BNF/bnf_struct.hpp"
#include "./../BNF/bnf_right.hpp"
#include "./../BNF/bnf_deployment.hpp"
#include "./lr_item.hpp"

#include "./../item_set/item_set.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
// class DfaNode;
// typedef std::vector<DfaNode> vDfaNode;

    typedef std::queue<LRItemStruct> quLRItemStruct;

#endif