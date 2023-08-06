
#ifndef __BNFDE
#define __BNFDE

#include "./../definition.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

#define bnf_token_len 100 //BNFトークンの最大長

#define is_id_Null 0
#define is_id_Unnecessary 100            // 不必要記号(無視)
#define is_id_NonterminalSymbol 110      // 非末端記号
#define is_id_NonterminalSymbolLeft 111  // 左辺定義 非末端記号
#define is_id_NonterminalSymbolRight 112 // 右辺定義 非末端記号
#define is_id_DefinitionSymbol 120       // 定義記号 ::=
#define is_id_VerticalLine 130           // | この縦棒記号。条件分岐に用いる
#define is_id_TerminalSymbol 140         // 末端記号(TerminalSymbol)
#define is_id_Token 141                  // 通常トークン。原則使わず、末端記号(TerminalSymbol)を使う
#define is_id_Escape 200
#define is_id_SingleQuotation 210
#define is_id_SingleQuotationLeft 211
#define is_id_SingleQuotationRight 212
#define is_id_DoubleQuotation 220
#define is_id_DoubleQuotationLeft 221
#define is_id_DoubleQuotationRight 222
#define is_id_Parenthesis 230      // まるかっこ
#define is_id_ParenthesisLeft 231  // まるかっこ左
#define is_id_ParenthesisRight 232 // まるかっこ右
#define is_id_Bracket 240          // しかくかっこ
#define is_id_BracketLeft 241      // しかくかっこ左
#define is_id_BracketRight 242     // しかくかっこ右

// 1000番台はそれぞれの記号の優先度を計算するために定義する
#define is_id_Addition 1100;       // 足し算記号
#define is_id_Subtraction 1101;    // 引き算記号
#define is_id_Multiplication 1110; // 掛け算記号
#define is_id_Division 1111;       // 割り算記号

#endif
