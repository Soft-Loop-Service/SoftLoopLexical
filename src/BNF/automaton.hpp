
#ifndef __AUTOMATON
#define __AUTOMATON

#include "./../definition.hpp"
#include "./automaton_definition.hpp"
#include "./../symbol.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>



class Automaton
{
private:
    int referenceIndex;
    vint transition;      // 次に想定するnode。つまり有向グラフにおいて接続する点。遷移先
    vint previous;      // 上向き構文解析用
public:
    // Automaton() //new配列で一度に確保するため、コンストラクタが使えない
    //  ~Automaton();

    // void setTransitionState(int arg)
    // {
    //     transition_state = arg;
    // }

    void connectTransition(int arg)
    {
        transition.push_back(arg);
    }

    void connectPrevious(int arg)
    {
        previous.push_back(arg);
    }
};

int connectAutomaton(Automaton *automaton_graph, int current_node, int sub_node)
{
    automaton_graph[current_node].connectTransition(sub_node);
    automaton_graph[sub_node].connectPrevious(current_node);
}


int parseRightSide(Automaton *automaton_graph, BNFToken &bnf_token_p, BNFSymbol &bnf_symbol_p , sint &bnf_stack)
{
    for (int j= 0; j < bnf_token_p.token_len ; j++){
        int current_token_label = bnf_token_p.token_label_array[j];

        if(current_token_label == is_id_NonterminalSymbolLeft){  
            // 左辺定義 非末端記号
            // 次の 非末端記号 に到達すると終了する
            // return;
        }
    }
}

int generateAutomaton(Automaton *automaton_graph, BNFToken &bnf_token_p, BNFSymbol &bnf_symbol_p)
{

    sint bnf_stack;

    for (int i = 0; i < bnf_token_p.token_len; i++)
    {
        int current_token_label = bnf_token_p.token_label_array[i];

        if (current_token_label == is_id_NonterminalSymbolLeft)
        { // 左辺定義 非末端記号

        }
    }
}

#endif
