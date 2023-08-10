

#ifndef __SYMBOL
#define __SYMBOL

#define is_id_Null 0                     // 0は原則として使用禁止
#define is_id_Unnecessary 100            // 不必要記号(無視)
#define is_id_NonterminalSymbol 110      // 非末端記号
#define is_id_NonterminalSymbolLeft 111  // 左辺定義 非末端記号
#define is_id_NonterminalSymbolRight 112 // 右辺定義 非末端記号
#define is_id_DefinitionSymbol 120       // 定義記号 ::=
#define is_id_VerticalLine 130           // | この縦棒記号。条件分岐に用いる
#define is_id_TerminalSymbol 140         // 末端記号(TerminalSymbol)
#define is_id_Token 141                  // 通常トークン。原則使わず、末端記号(TerminalSymbol)を使う
#define is_id_Escape 200                 // イコール記号
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

#define is_id_CurlyBracket 250     // 中かっこ
#define is_id_CurlyBracketLeft 251 // 左中かっこ
#define is_id_CurlyBracketRight 252

#define is_id_Addition 1100       // 足し算記号
#define is_id_Subtraction 1101    // 引き算記号
#define is_id_Multiplication 1110 // 掛け算記号
#define is_id_Division 1111       // 割り算記号

bool is_symbol_parentheses_left(int t)
{
    return t == is_id_ParenthesisLeft || t == is_id_BracketLeft || t == is_id_CurlyBracketLeft;
}

bool is_symbol_parentheses_right(int t)
{
    return t == is_id_ParenthesisRight || t == is_id_BracketRight || t == is_id_CurlyBracketRight;
}

bool is_symbol_operator(int t)
{
    switch (t)
    {
    case is_id_Addition:
    case is_id_Subtraction:
    case is_id_Multiplication:
    case is_id_Division:
    {
        return true;
    }

    default:
        return false;
    }
}

bool is_for_automaton(int t)
{
    switch (t)
    {
    case is_id_VerticalLine:
    case is_id_ParenthesisLeft:
    case is_id_BracketLeft:
    case is_id_CurlyBracketLeft:
    case is_id_ParenthesisRight:
    case is_id_BracketRight:
    case is_id_CurlyBracketRight:
    case is_id_Addition:
    case is_id_Subtraction:
    case is_id_Multiplication:
    case is_id_Division:
    {
        return true;
    }

    default:
        return false;
    }
}

#endif