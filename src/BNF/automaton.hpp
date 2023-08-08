
#ifndef __AUTOMATON
#define __AUTOMATON

#include "./../definition.hpp"
#include "./automaton_definition.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>


class Automaton
{
private:
    int referenceIndex;
    int adjacent_state; //正規表現 (regular_expression) の状態番号
    vint adjacent = {}; //次に想定するnode。つまり有向グラフにおいて接続する点
    vint previous = {}; //上向き構文解析用
public:
    //Automaton() //new配列で一度に確保するため、コンストラクタが使えない
    // ~Automaton();
    
    void setAdjacentState(int arg){
        adjacent_state = arg;
    }

    void connectAdjacent(int arg){
        adjacent.push_back(arg);
    }

    void connectPrevious(int arg){
        previous.push_back(arg);
    }
    

};



int connectAutomaton(Automaton *automaton_graph,int current_node , int sub_node){
    automaton_graph[current_node].connectAdjacent(sub_node);
    automaton_graph[sub_node].connectPrevious(current_node);
}

int parseRightSide(Automaton *automaton_graph, char **symbol_string, int *symbol_table){
    // for (int i= 0; i < token_len ; i++){
    //     int current_token_label = token_label[i];

    //     if(current_token_label == is_id_NonterminalSymbolLeft){  // 左辺定義 非末端記号
            
    //     }
    // }
}

int generateAutomaton(Automaton *automaton_graph, char **symbol_string, int *symbol_table, int *token_label, int token_len, int symbol_len)
{
    for (int i= 0; i < token_len ; i++){
        int current_token_label = token_label[i];

        if(current_token_label == is_id_NonterminalSymbolLeft){  // 左辺定義 非末端記号
            
        }
    }
}

#endif
