// Shunting yard algorithm

#ifndef __SHUNTING_ALGO
#define __SHUNTING_ALGO

#include "./../definition.hpp"
#include "./../symbol.hpp"
#include "./../symbol_priority.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

//操車場アルゴリズム
//https://www.pandanoir.info/entry/2017/07/05/190000

void loop_shunting_yard_algorithm(stint &yard_stack, vint &output_queue, int current_label)
{

    if (current_label == is_id_TerminalSymbol || current_label == is_id_NonterminalSymbolRight)
    {
        output_queue.push_back(current_label);
    }

    //トークンが演算子のとき
    if (is_symbol_operator(current_label))
    {
        for (int ai = 0; ai < yard_stack.size(); ai++)
        {
            int pop_label = yard_stack.top();
            yard_stack.pop();

            if (is_symbol_operator(pop_label))
            {
                if(is_over_symbol_priority(current_label,pop_label)){
                    return;
                }

                if (get_join_symbol_priority(current_label) && is_and_over_symbol_priority(current_label,pop_label)){
                    return;
                }

            }
            else{
                return;
            }

            output_queue.push_back(pop_label);
            
        }

        return;
    }

    if (is_symbol_parentheses_left(current_label))
    {
        yard_stack.push(current_label);
        return;
    }

    if (is_symbol_parentheses_right(current_label))
    {

        for (int ai = 0; ai < yard_stack.size(); ai++)
        {
            int pop_label = yard_stack.top();

            // 左括弧をスタックからポップするが、出力には追加せずに捨てる。
            if (is_symbol_parentheses_left(pop_label))
            {
                return;
            }

            output_queue.push_back(pop_label);
            yard_stack.pop();
        }
    }
}

void shunting_yard_algorithm(int *label, int len)
{
    stint yard_stack;
    vint output_queue;

    for (int i = 0; i < len; i++)
    {
        int current_label = label[i];
        loop_shunting_yard_algorithm(yard_stack , output_queue ,current_label);
    }

    for (int i = 0; i < yard_stack.size();i++){
        int pop = yard_stack.top();
        output_queue.push_back(pop);
        yard_stack.pop();
    }

    printf("shunting_yard_algorithm : \n");
    for (int i = 0; i < output_queue.size();i++){
        printf(" %d",output_queue[i]);
    }
    printf("\n");
}

#endif