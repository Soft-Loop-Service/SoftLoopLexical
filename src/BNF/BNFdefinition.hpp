
#ifndef __BNFDE
#define __BNFDE

#include "./../definition.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

#define is_id_Null 0
#define is_id_Unnecessary 100
#define is_id_NonterminalSymbol 101
#define is_id_DefinitionSymbol 102
#define is_id_VerticalLine 103
#define is_id_Token 104
#define is_id_Escape 200
#define is_id_SingleQuotation 201
#define is_id_DoubleQuotation 202
#define is_id_Parenthesis 203      // まるかっこ
#define is_id_ParenthesisLeft 204  // まるかっこs
#define is_id_ParenthesisRight 205 // まるかっこe
#define is_id_Bracket 206          // しかくかっこ
#define is_id_BracketLeft 207      // しかくかっこs
#define is_id_BracketRight 208     // しかくかっこe

#endif
