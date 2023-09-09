
#ifndef __CLS_EXP
#define __CLS_EXP

#include "./dfa_calc.hpp"
#include "./lr_item.hpp"

#include "./../definition.hpp"
#include "./../symbol.hpp"
#include "./../BNF/bnf_struct.hpp"
#include "./../BNF/bnf_right.hpp"
#include "./../BNF/bnf_deployment.hpp"

#include "./../item_set/item_set.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

/*
dot と tokenの関係は以下の通り
  token0 token1 token2 token3 ・・・
dot0   dot1  dot2   dot3・・・
*/

/*
novelty 新規追加であるかどうか
search_key 展開したい展開式の左辺
LR_formula_expansion_vector_index 展開したい展開式の右辺整理番号 search_keyとセット
first_set 親によって作成されたfirst_set集合
*/
struct ClosureExpansionQueueStruct
{
    bool novelty;
    string search_key;
    int LR_formula_expansion_vector_index;
    vDeploymentTokenStruct first_set;
};

typedef queue<ClosureExpansionQueueStruct> qClosureExpansionQueueStruct;

class ClosureExpansion
{
private:
    DeploymentStruct deployment_syntax;

    // 一つのアイテム集合内に、同じ展開式が重複して登録されないようにする,式番号:挿入位置
    mp_i_i already_explored_formula_expansion = {};

    // どの式がどの式に影響を及ぼしているか調べる 隣接リスト表現 式番号:[影響がある式番号]
    mp_i_vstring derivative_formula_expansion = {};

    // int dot = -1;

public:
    ClosureExpansion(DeploymentStruct &deployment_syntax)
    {
        this->deployment_syntax = deployment_syntax;
        // this->dot = dot;
    }
    void nodeClosureExpansion(LRItemStruct &lr_item)
    {
        // already_explored = {};
        already_explored_formula_expansion = {};
        derivative_formula_expansion = {};

        vstring LR_formula_map_keys = getMapKeyString(lr_item.LR_formula_map);

        for (int i = 0; i < LR_formula_map_keys.size(); i++)
        {
            string key = LR_formula_map_keys[i];

            for (int j = 0; j < lr_item.LR_formula_map[key].LR_formula_expansion_vector.size(); j++)
            {
                int dot = lr_item.LR_formula_map[key].LR_formula_expansion_vector[j].dot;

                int la_size = lr_item.LR_formula_map[key].LR_formula_expansion_vector[j].lookAhead.size();
                for (int k = 0; k < la_size; k++)
                {
                    vDeploymentTokenStruct first_set = getLatterFirstSet(lr_item.LR_formula_map[key].LR_formula_expansion_vector[j], dot, lr_item.LR_formula_map[key].LR_formula_expansion_vector[j].lookAhead[k]);
                    loopNodeClosureExpansion(lr_item, key, j, first_set);
                }
            }
        }
    }

    void nodeClosureExpansion(LRItemStruct &lr_item, string search_key)
    {
        // already_explored = {};
        already_explored_formula_expansion = {};
        derivative_formula_expansion = {};
        for (int j = 0; j < lr_item.LR_formula_map[search_key].LR_formula_expansion_vector.size(); j++)
        {
            int dot = lr_item.LR_formula_map[search_key].LR_formula_expansion_vector[j].dot;
            int la_size = lr_item.LR_formula_map[search_key].LR_formula_expansion_vector[j].lookAhead.size();
            for (int k = 0; k < la_size; k++)
            {
                vDeploymentTokenStruct first_set = getLatterFirstSet(lr_item.LR_formula_map[search_key].LR_formula_expansion_vector[j], dot, lr_item.LR_formula_map[search_key].LR_formula_expansion_vector[j].lookAhead[k]);
                loopNodeClosureExpansion(lr_item, search_key, j, first_set);
            }
        }
    }

private:
    // dotの後ろにある末端記号・非末端記号と、先読み記号を合体させる
    vDeploymentTokenStruct getLatterToken(LRItemFormulaExpansionStruct LR_formula_expansion, int dot, DeploymentTokenStruct lookAhead_token)
    {
        vDeploymentTokenStruct latter_token = {};
        for (int i = dot + 1; i < LR_formula_expansion.token_vector.size(); i++)
        {
            latter_token.push_back(LR_formula_expansion.token_vector[i]);
        }

        // for (int i = 0; i < LR_formula_expansion.lookAhead.size(); i++)
        // {
        latter_token.push_back(lookAhead_token);
        // findFirstSetVectorに対してはvDeploymentTokenStructの形で渡さねばならぬが、これが阻んでいる
        // }

        return latter_token;
    }

    vDeploymentTokenStruct getLatterFirstSet(LRItemFormulaExpansionStruct LR_formula_expansion, int dot, DeploymentTokenStruct lookAhead_token)
    {

        NullSetClass cnull_set_class = NullSetClass(this->deployment_syntax);
        FirstSetClass cfirst_set_class = FirstSetClass(this->deployment_syntax, cnull_set_class.findNullsSet());

        vDeploymentTokenStruct latter_token = getLatterToken(LR_formula_expansion, dot, lookAhead_token);
        vDeploymentTokenStruct first_set = cfirst_set_class.findFirstSetVector(latter_token);

        // printf("latter_token , getLatterFirstSet %ld %ld\n", latter_token.size(), first_set.size());
        // for (int la = 0; la < latter_token.size(); la++)
        // {
        //     printf("latter_token %s\n", latter_token[la].token_str.c_str());
        // }
        // for (int la = 0; la < first_set.size(); la++)
        // {
        //     printf("getLatterFirstSet %s\n", first_set[la].token_str.c_str());
        // }

        return first_set;
    }

    /// @brief
    /// @param lr_item
    /// @param search_key 展開したい展開式の左辺
    /// @param LR_formula_expansion_vector_index 展開したい展開式の右辺整理番号 search_keyとセット
    /// @param first_set 先読み記号用。
    void loopNodeClosureExpansion(LRItemStruct &lr_item, string search_key, int LR_formula_expansion_vector_index, vDeploymentTokenStruct first_set)
    {
        qClosureExpansionQueueStruct que = {};

        printf("loopNodeClosureExpansion \n");

        struct ClosureExpansionQueueStruct f_closure_expansion_queue_struct = {true, search_key, LR_formula_expansion_vector_index, first_set};
        que.push(f_closure_expansion_queue_struct);
        do
        {
            ClosureExpansionQueueStruct front = que.front();

            front.novelty ? noveltyNodeClosureExpansion(que, lr_item, front) : preexistNodeClosureExpansion(que, lr_item, front);
            // noveltyNodeClosureExpansion(que, lr_item, front);

            que.pop();

            printf("\r quesize : %ld", que.size());
        } while (que.size() > 0);
        printf("\n");
    }

    void noveltyNodeClosureExpansion(qClosureExpansionQueueStruct &que, LRItemStruct &lr_item, ClosureExpansionQueueStruct current_closure_expansion_queue_struct)
    {
        string search_key = current_closure_expansion_queue_struct.search_key;
        int LR_formula_expansion_vector_index = current_closure_expansion_queue_struct.LR_formula_expansion_vector_index;
        vDeploymentTokenStruct first_set = current_closure_expansion_queue_struct.first_set;
        LRItemFormulaStruct lr_item_formula = lr_item.LR_formula_map[search_key];
        vLRItemFormulaExpansionStruct LR_formula_expansion_vector = lr_item_formula.LR_formula_expansion_vector;
        LRItemFormulaExpansionStruct LR_formula_expansion = LR_formula_expansion_vector[LR_formula_expansion_vector_index];
        vDeploymentTokenStruct token_vector = LR_formula_expansion.token_vector;

        if (LR_formula_expansion.dot >= token_vector.size())
        {
            return;
        }

        DeploymentTokenStruct token = token_vector[LR_formula_expansion.dot];
        // 展開しなければならないkey(右辺)
        // これをもとに、左辺を呼び出して展開する

        if (token.label == is_id_TerminalSymbol)
        {
            return;
        }

        LRItemFormulaStruct *current_LR_formula = &(lr_item.LR_formula_map[token.token_str]);

        // データの移譲
        vDeploymentFormulaExpansionStruct dfexp = deployment_syntax.formula_map[token.token_str].formula_expansion_vector;
        for (int k = 0; k < dfexp.size(); k++)
        {
            if (hasKeyMap(getMapKeyString(already_explored_formula_expansion), dfexp[k].formula_expansion_label))
            {
                // すでに対象の構文が存在するとき、同じ条件でクロージャー先読み記号を展開するように要求する
                struct ClosureExpansionQueueStruct c_closure_expansion_queue_struct = {false, token.token_str, LR_formula_expansion_vector_index, first_set};
                que.push(c_closure_expansion_queue_struct);
                continue;
            }
            struct LRItemFormulaExpansionStruct new_lrf_exp;
            new_lrf_exp.token_vector = dfexp[k].token_vector;
            new_lrf_exp.formula_expansion_label = dfexp[k].formula_expansion_label;
            new_lrf_exp.lookAhead = first_set;
            new_lrf_exp.dot = 0;

            current_LR_formula->LR_formula_expansion_vector.push_back(new_lrf_exp);

            int push_index = current_LR_formula->LR_formula_expansion_vector.size() - 1;

            already_explored_formula_expansion[new_lrf_exp.formula_expansion_label] = push_index;

            derivative_formula_expansion[LR_formula_expansion_vector_index].push_back(token.token_str);

            // ここから、次に展開すべき式をキューに挿入する処理

            int la_size = new_lrf_exp.lookAhead.size();

            for (int t = 0; t < la_size; t++)
            {
                // 次に展開したい（先ほど追加された式）式について、すでに存在するならばクロージャー展開の先読み記号を追加展開するようにする
                // bool next_b = !(hasKeyMap(getMapKeyString(already_explored_formula_expansion), new_lrf_exp.formula_expansion_label));
                vDeploymentTokenStruct new_first_set = getLatterFirstSet(new_lrf_exp, new_lrf_exp.dot, new_lrf_exp.lookAhead[t]);
                struct ClosureExpansionQueueStruct n_closure_expansion_queue_struct = {true, token.token_str, push_index, new_first_set};
                que.push(n_closure_expansion_queue_struct);
            }
        }
    }

    void preexistNodeClosureExpansion(qClosureExpansionQueueStruct &que, LRItemStruct &lr_item, ClosureExpansionQueueStruct current_closure_expansion_queue_struct)
    {

        printf("\npreexistNodeClosureExpansion\n");
        string search_key = current_closure_expansion_queue_struct.search_key;
        int LR_formula_expansion_vector_index = current_closure_expansion_queue_struct.LR_formula_expansion_vector_index;
        vDeploymentTokenStruct first_set = current_closure_expansion_queue_struct.first_set;

        LRItemFormulaStruct lr_item_formula = lr_item.LR_formula_map[search_key];
        vLRItemFormulaExpansionStruct LR_formula_expansion_vector = lr_item_formula.LR_formula_expansion_vector;
        LRItemFormulaExpansionStruct LR_formula_expansion = LR_formula_expansion_vector[LR_formula_expansion_vector_index];

        int target_index = already_explored_formula_expansion[LR_formula_expansion_vector_index];
        vstring target_children = derivative_formula_expansion[LR_formula_expansion_vector_index];

        vDeploymentTokenStruct *lookAhead = &(lr_item.LR_formula_map[search_key].LR_formula_expansion_vector[LR_formula_expansion_vector_index].lookAhead);
        int lookAhead_size = lookAhead->size();
        bool change = false;
        for (int i = 0; i < lookAhead_size; i++)
        {
            for (int j = 0; j < first_set.size(); j++)
            {
                if ((*lookAhead)[i].token_str != first_set[j].token_str)
                {
                    lookAhead->push_back(first_set[i]);
                    change = true;
                }
            }
        }

        if (!change)
        {
            return;
        }

        lookAhead_size = lookAhead->size();

        for (int i = 0; i < target_children.size(); i++)
        {

            string current_child_key = target_children[i];
            LRItemFormulaStruct next_lr_item_formula = lr_item.LR_formula_map[current_child_key];
            for (int t = 0; t < lookAhead_size; t++)
            {
                for (int j = 0; j < next_lr_item_formula.LR_formula_expansion_vector.size(); j++)
                {
                    // 次に展開したい（先ほど追加された式）式について、すでに存在するならばクロージャー展開の先読み記号を追加展開するようにする
                    // bool next_b = !(hasKeyMap(getMapKeyString(already_explored_formula_expansion), new_lrf_exp.formula_expansion_label));
                    vDeploymentTokenStruct new_first_set = getLatterFirstSet(LR_formula_expansion, LR_formula_expansion.dot, (*lookAhead)[t]);
                    struct ClosureExpansionQueueStruct n_closure_expansion_queue_struct = {false, current_child_key, next_lr_item_formula.LR_formula_expansion_vector[j].formula_expansion_label, new_first_set};
                    que.push(n_closure_expansion_queue_struct);
                }
            }
        }
    }
};
// // search_key : 展開したいkey(左辺key)
// // 展開した式ごとに関数を実行する
// void recursionNodeClosureExpansion(qClosureExpansionQueueStruct &que, LRItemStruct &lr_item, ClosureExpansionQueueStruct current_closure_expansion_queue_struct)
// {
//     string search_key = current_closure_expansion_queue_struct.search_key;
//     int LR_formula_expansion_vector_index = current_closure_expansion_queue_struct.LR_formula_expansion_vector_index;
//     vDeploymentTokenStruct first_set = current_closure_expansion_queue_struct.first_set;
//     LRItemFormulaStruct lr_item_formula = lr_item.LR_formula_map[search_key];
//     vLRItemFormulaExpansionStruct LR_formula_expansion_vector = lr_item_formula.LR_formula_expansion_vector;

//     LRItemFormulaExpansionStruct LR_formula_expansion = LR_formula_expansion_vector[LR_formula_expansion_vector_index];
//     vDeploymentTokenStruct token_vector = LR_formula_expansion.token_vector;

//     if (LR_formula_expansion.dot >= token_vector.size())
//     {
//         return;
//     }

//     DeploymentTokenStruct token = token_vector[LR_formula_expansion.dot];
//     // 展開しなければならないkey(右辺)
//     // これをもとに、左辺を呼び出して展開する

//     if (token.label == is_id_TerminalSymbol)
//     {
//         return;
//     }

//     // データの移譲
//     vDeploymentFormulaExpansionStruct dfexp = deployment_syntax.formula_map[token.token_str].formula_expansion_vector;

//     for (int k = 0; k < dfexp.size(); k++)
//     {

//         if (!hasKeyMap(getMapKeyString(already_explored_formula_expansion), dfexp[k].formula_expansion_label))
//         {
//             struct LRItemFormulaExpansionStruct new_lrf_exp;
//             new_lrf_exp.token_vector = dfexp[k].token_vector;
//             new_lrf_exp.formula_expansion_label = dfexp[k].formula_expansion_label;
//             new_lrf_exp.lookAhead = first_set;
//             new_lrf_exp.dot = 0;

//             // printf("クロージャー展開新規追加 %s %d\n", token.token_str.c_str(), new_lrf_exp.lookAhead.size());

//             // for (int la = 0; la < new_lrf_exp.lookAhead.size(); la++)
//             // {
//             //     printf("先読み記号 %s\n", new_lrf_exp.lookAhead[la].token_str.c_str());
//             // }

//             lr_item.LR_formula_map[token.token_str].LR_formula_expansion_vector.push_back(new_lrf_exp);
//             already_explored_formula_expansion[new_lrf_exp.formula_expansion_label] = lr_item.LR_formula_map[token.token_str].LR_formula_expansion_vector.size() - 1;

//             int n_index = lr_item.LR_formula_map[token.token_str].LR_formula_expansion_vector.size() - 1;
//             int dot = lr_item.LR_formula_map[token.token_str].LR_formula_expansion_vector[n_index].dot;
//             int la_size = lr_item.LR_formula_map[token.token_str].LR_formula_expansion_vector[n_index].lookAhead.size();
//             for (int t = 0; t < la_size; t++)
//             {
//                 vDeploymentTokenStruct new_first_set = getLatterFirstSet(lr_item.LR_formula_map[token.token_str].LR_formula_expansion_vector[n_index], dot, t);
//                 // recursionNodeClosureExpansion(lr_item, token.token_str, n_index, new_first_set);
//                 struct ClosureExpansionQueueStruct n_closure_expansion_queue_struct = {token.token_str, n_index, new_first_set};
//                 que.push(n_closure_expansion_queue_struct);
//             }
//         }
//         else
//         { // 先読み記号だけ追加する
//             int formula_expansion_index = already_explored_formula_expansion[dfexp[k].formula_expansion_label];
//             vDeploymentTokenStruct lookAhead = lr_item.LR_formula_map[token.token_str].LR_formula_expansion_vector[formula_expansion_index].lookAhead;
//             int current_lookAhead_p_size = lookAhead.size();
//             for (int n = 0; n < first_set.size(); n++)
//             {
//                 bool flag = true;
//                 for (int s = 0; s < current_lookAhead_p_size; s++)
//                 {
//                     if (lookAhead[s].token_str == first_set[n].token_str)
//                     {
//                         flag = false;
//                         break;
//                     }
//                 }
//                 if (flag)
//                 {
//                     lookAhead.push_back(first_set[n]);

//                     int nfx_size = lr_item.LR_formula_map[token.token_str].LR_formula_expansion_vector.size();
//                     // printf("再帰展開 %d\n", nfx_size);
//                     for (int j = 0; j < nfx_size; j++)
//                     {
//                         int dot = lr_item.LR_formula_map[token.token_str].LR_formula_expansion_vector[j].dot;

//                         int la_size = lr_item.LR_formula_map[token.token_str].LR_formula_expansion_vector[j].lookAhead.size();
//                         for (int k = 0; k < la_size; k++)
//                         {

//                             vDeploymentTokenStruct new_first_set = getLatterFirstSet(lr_item.LR_formula_map[token.token_str].LR_formula_expansion_vector[j], dot, k);

//                             // recursionNodeClosureExpansion(lr_item, token.token_str, j, new_first_set);
//                             struct ClosureExpansionQueueStruct n_closure_expansion_queue_struct = {token.token_str, j, new_first_set};
//                             que.push(n_closure_expansion_queue_struct);
//                         }
//                     }
//                 }
//             }

//             lr_item.LR_formula_map[token.token_str].LR_formula_expansion_vector[formula_expansion_index].lookAhead = lookAhead;
//             // return;s
//         }
//     }

// if (hasKeyMap(this->already_explored, search_key))
// {
//     // printf("拒否 %s\n", search_key.c_str());
//     return;
// }
// this->already_explored.push_back(search_key);

// 展開した先でも非末端記号であれば再帰的に展開する
// int nfx_size = lr_item.LR_formula_map[token.token_str].LR_formula_expansion_vector.size();
// // printf("再帰展開 %d\n", nfx_size);
// for (int j = 0; j < nfx_size; j++)
// {
//     int dot = lr_item.LR_formula_map[token.token_str].LR_formula_expansion_vector[j].dot;

//     int la_size = lr_item.LR_formula_map[token.token_str].LR_formula_expansion_vector[j].lookAhead.size();
//     for (int k = 0; k < la_size; k++)
//     {
//         vDeploymentTokenStruct new_first_set = getLatterFirstSet(lr_item.LR_formula_map[token.token_str].LR_formula_expansion_vector[j], dot, k);
//         recursionNodeClosureExpansion(lr_item, token.token_str, j, new_first_set);
//     }
// }

// for (int k = 0; k < toke)

// }

#endif
