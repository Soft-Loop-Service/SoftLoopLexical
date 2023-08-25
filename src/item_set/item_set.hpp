
#ifndef __AUTOMATONIS
#define __AUTOMATONIS
#include "./item_set_calc.hpp"
#include "./../definition.hpp"
#include "./../symbol.hpp"
#include "./../BNF/bnf_struct.hpp"
#include "./../BNF/bnf_right.hpp"
#include "./../BNF/bnf_vector.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

/*
null_set    : Nulls集合     vstring
first_set   : First集合     mp_s_vstring
follow_set  : Follows集合   mp_s_vstring
*/
struct ItemSetStruct
{
    vstring null_set;
    mp_s_vstring first_set;
    mp_s_vstring follow_set;
};

/// @brief
/// @param bnf_token_p
/// @param bnf_symbol_p
/// @param nonterminal_symbol_left
/// @param nonterminal_symbol_right
/// @param terminal_symbol
/// @return
ItemSetStruct generateItemSet(DeploymentStruct deployment_syntax)
{

    printf("再帰探索 a\n");
    NullSetClass null_set_class = NullSetClass(deployment_syntax);
    vstring null_set = null_set_class.findNullsSet();

    FirstSetClass first_set_class = FirstSetClass(deployment_syntax, null_set);
    mp_s_vstring first_set = first_set_class.findFirstSet();

    FollowSetClass folllow_set_class = FollowSetClass(deployment_syntax, null_set, first_set);
    mp_s_vstring folllow_set = folllow_set_class.findFolllowSet();

    struct ItemSetStruct item_set = {null_set, first_set, folllow_set};

    printf("再帰探索 b\n");

    return item_set;
    // recursionItemSet(item_set, bnf_token_p, symbols, 1);
}

#endif