

#ifndef __SYMBOLP
#define __SYMBOLP

#include "./symbol.hpp"
#include "definition.hpp"

// 演算子優先順位定義ファイル

// 演算子優先順位
// https://programming-place.net/ppp/contents/c/appendix/operation.html
// https://programming-place.net/ppp/contents/cpp2/appendix/operator.html

#define left_join 1  // 左から右
#define right_join 2 // 右から左

v2int symbol_priority = {
    // 1
    {left_join,
     is_id_Parenthesis,
     is_id_ParenthesisLeft,
     is_id_ParenthesisRight,
     is_id_Bracket,
     is_id_BracketLeft,
     is_id_BracketRight},

    // 2
    {right_join},

    // 3
    {right_join},

    // 4
    {left_join, is_id_Multiplication, is_id_Division},

    // 5
    {left_join, is_id_Addition, is_id_Subtraction},

    // 6
    {left_join},

    // 7
    {left_join},

    // 8
    {left_join},

    // 9
    {left_join},

    // 10
    {left_join},

    // 11
    {left_join},

    // 12
    {left_join},

    // 13
    {left_join,is_id_VerticalLine},

    // 14
    {right_join},

    // 15
    {right_join, is_id_Escape},

    // 16
    {left_join},
};

int search_symbol_priority(int search_symbol)
{
    int index = -1;

    for (int i = 0; i < symbol_priority.size(); i++)
    {
        for (int j = 1; j < symbol_priority[i].size(); j++)
        {
            if (symbol_priority[i][j] == search_symbol){
                return i;
            }
        }
    }

    return index;
}

/*
is_over_symbol_priority
symbol_a と symbol_bの二つの引数をとり、symbol_aの方がより大きければ、trueを返す
どちらかが存在すればtrueとなり、どちらも存在しなければfalseとなる。
*/
int is_over_symbol_priority(int symbol_a, int symbol_b)
{
    int index_symbol_a = search_symbol_priority(symbol_a);
    int index_symbol_b = search_symbol_priority(symbol_b);

    return index_symbol_a > index_symbol_b;
}
int is_and_over_symbol_priority(int symbol_a, int symbol_b)
{
    int index_symbol_a = search_symbol_priority(symbol_a);
    int index_symbol_b = search_symbol_priority(symbol_b);

    return index_symbol_a >= index_symbol_b;
}

int get_join_symbol_priority(int symbol){
    int index = search_symbol_priority(symbol);
    if (index == -1){
        return -1;
    }
    return symbol_priority[index][0];
}

#endif