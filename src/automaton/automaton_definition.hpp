
#ifndef __AUTOMATON_DE
#define __AUTOMATON_DE

#include "./../definition.hpp"
#include "./automaton.hpp"

#define automaton_0or1 1      // ? 記号
#define automaton_asterisk 2  // * 記号
#define automaton_plus_sign 3 // + 記号

/*
bnf_right
children
dot
*/
struct ItemSetStruct
{
    v3int bnf_right;
    v2int children;
    // int dot;
};

typedef std::vector<ItemSetStruct> vItemSetTree;

#endif