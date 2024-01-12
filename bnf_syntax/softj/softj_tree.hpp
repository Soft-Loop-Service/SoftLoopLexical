
#ifndef __SOFTJTREE
#define __SOFTJTREE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "./../../src/syntactic/syntactic_analysis_tree.hpp"
#include "./../../src/process/process_analysis_definition.hpp"
#include "./../../src/process/process_analysis_function.hpp"
#include "./../../src/process/process_analysis_value.hpp"
namespace LanguageSpecifications
{

    class SoftjTree
    {

    private:
        vSyntacticTree *syntactic_analysis_tree;
        ProcessVisualization::vProcessAnalysis *process_result;
        ProcessVisualization::VariablePossessionUnion *vpu;
        ProcessVisualization::FunctionPossessionUnion *fpu;

        ProcessVisualization::LayerQueue input_layer_queue;
        ProcessVisualization::LayerQueue output_layer_queue;

        void assExpr(int left_index, int right_index)
        {

            SyntacticTreeNode current_node = (*syntactic_analysis_tree)[left_index];

            if (current_node.token == "<value_definition>")
            {
                printf("assExpr %d %d %d %s\n", left_index, current_node.children[0], current_node.children[1], current_node.token.c_str());

                SyntacticTreeNode child_left = (*syntactic_analysis_tree)[current_node.children[0]];
                SyntacticTreeNode child_right = (*syntactic_analysis_tree)[current_node.children[1]];

                string value_type = child_left.token;
                string value_name = child_right.token;

                if (vpu->hasLayer(value_name))
                {
                    int layer = vpu->getLayer(value_name);
                    struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_error, "定義済み変数名の再宣言", {layer}, left_index};
                    process_result->push_back(pr);
                    return;
                }

                string value_ans = "";

                if (value_type == "string")
                {
                    string value_string = resolution_calc_string(right_index);
                    vpu->newValue(value_name, value_string, left_index);
                    value_ans = value_string;
                }

                if (value_type == "int")
                {
                    int value_int = resolution_calc_int(right_index);
                    vpu->newValue(value_name, value_int, left_index);
                    value_ans = to_string(value_int);
                }

                printf("d\n");

                string message = "変数定義代入 " + child_right.token + " " + value_ans;

                int layer = vpu->getLayer(value_name);
                output_layer_queue.enqueueLayerQueue(layer);
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_ouput, message, output_layer_queue.useClearLayerQueue(), left_index};
                process_result->push_back(pr);

                return;
            }

            if (current_node.parent_token == "<value_name>")
            {

                string value_name = current_node.token;


                if (!(vpu->hasLayer(value_name)))
                {
                    int layer = vpu->getLayer(value_name);
                    struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_error, "未定義変数への代入", {layer}, left_index};
                    process_result->push_back(pr);
                    return;
                }

                string value_type = vpu->getType(value_name);
                string value_ans = "";

                if (value_type == "string")
                {
                    string value_string = resolution_calc_string(right_index);
                    vpu->updateValue(value_name, value_string);
                    value_ans = value_string;
                }

                if (value_type == "int")
                {
                    int value_int = resolution_calc_int(right_index);
                    vpu->updateValue(value_name, value_int);
                    value_ans = to_string(value_int);
                }

                string message = "変数代入 " + current_node.token + " " + value_ans;
                int layer = vpu->getLayer(value_name);
                output_layer_queue.enqueueLayerQueue(layer);
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_ouput, message, output_layer_queue.useClearLayerQueue(), left_index};
                process_result->push_back(pr);
                return;
            }
        }

        void functionMessagePassing(int node_index){

        }

        bool getBool(int val)
        {
            return val > 0;
        }

        int functionCalc(int node_index)
        {
        }

        int whileCalc(int node_index)
        {
            SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
            SyntacticTreeNode child0 = (*syntactic_analysis_tree)[current_node.children[0]];
            // SyntacticTreeNode child1 = (*syntactic_analysis_tree)[current_node.children[1]];
            // SyntacticTreeNode child2 = (*syntactic_analysis_tree)[current_node.children[2]];

            int calc_ans = resolution_calc_int(current_node.children[1]);
            bool ifbool = getBool(calc_ans);

            while (ifbool)
            {
                output_layer_queue.enqueueLayerQueue(0);
                string message = "ループ条件式 true";
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_logic, message, output_layer_queue.useClearLayerQueue(), node_index};
                process_result->push_back(pr);

                vpu->deep();

                recursion(current_node.children[2]);
                calc_ans = resolution_calc_int(current_node.children[1]);
                ifbool = getBool(calc_ans);

                vpu->shallow();
            }

            string message = "ループ条件式 false";
            output_layer_queue.enqueueLayerQueue(0);
            struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_logic, message, output_layer_queue.useClearLayerQueue(), node_index};
            process_result->push_back(pr);
        }

        int ifCalc(int node_index)
        {
            printf("ifCalc\n");
            SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
            SyntacticTreeNode child0 = (*syntactic_analysis_tree)[current_node.children[0]];
            // SyntacticTreeNode child1 = (*syntactic_analysis_tree)[current_node.children[1]];
            // SyntacticTreeNode child2 = (*syntactic_analysis_tree)[current_node.children[2]];
            int calc_ans = resolution_calc_int(current_node.children[1]);

            bool ifbool = getBool(calc_ans);
            output_layer_queue.enqueueLayerQueue(0);

            if (ifbool)
            {
                string message = "条件式 true";
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_logic, message, output_layer_queue.useClearLayerQueue(), node_index};
                process_result->push_back(pr);

                if (current_node.children.size() >= 3)
                {
                    vpu->deep();

                    recursion(current_node.children[2]);

                    vpu->shallow();
                }
            }
            else
            {
                string message = "条件式 false";
                struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_logic, message, output_layer_queue.useClearLayerQueue(), node_index};
                process_result->push_back(pr);
            }
        }

        int equal(int node_index)
        {

            SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
            SyntacticTreeNode child_left = (*syntactic_analysis_tree)[current_node.children[0]];
            SyntacticTreeNode child_right = (*syntactic_analysis_tree)[current_node.children[1]];
            assExpr(current_node.children[0], current_node.children[1]);
        }
        string text_join(string left, string right)
        {
            string message = "文字列連結 " + left + " + " + right;
            struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, input_layer_queue.useClearLayerQueue()};
            process_result->push_back(pr);

            return left + right;
        }

        int addition(int left, int right, int node_index)
        {
            string message = "加算 " + to_string(left) + " + " + to_string(right);
            struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, input_layer_queue.useClearLayerQueue(), node_index};
            process_result->push_back(pr);

            return left + right;
        }
        int subtraction(int left, int right, int node_index)
        {
            string message = "減算 " + to_string(left) + " - " + to_string(right);
            struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, input_layer_queue.useClearLayerQueue(), node_index};
            process_result->push_back(pr);
            return left - right;
        }
        int multiplication(int left, int right, int node_index)
        {
            string message = "乗算 " + to_string(left) + " * " + to_string(right);
            struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, input_layer_queue.useClearLayerQueue(), node_index};
            process_result->push_back(pr);
            return left * right;
        }
        int division(int left, int right, int node_index)
        {
            string message = "割算 " + to_string(left) + " / " + to_string(right);
            struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, input_layer_queue.useClearLayerQueue(), node_index};
            process_result->push_back(pr);
            return left / right;
        }
        int less(int left, int right, int node_index)
        {
            string message = "比較 " + to_string(left) + " < " + to_string(right);
            struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, input_layer_queue.useClearLayerQueue(), node_index};
            process_result->push_back(pr);
            return left < right;
        }
        int less_equal(int left, int right, int node_index)

        {
            string message = "比較 " + to_string(left) + " <= " + to_string(right);
            struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, input_layer_queue.useClearLayerQueue(), node_index};
            process_result->push_back(pr);
            return left <= right;
        }
        int greater(int left, int right, int node_index)
        {
            string message = "比較 " + to_string(left) + " > " + to_string(right);
            struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, input_layer_queue.useClearLayerQueue(), node_index};
            process_result->push_back(pr);
            return left > right;
        }
        int greater_equal(int left, int right, int node_index)
        {
            string message = "比較 " + to_string(left) + " >= " + to_string(right);
            struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, input_layer_queue.useClearLayerQueue(), node_index};
            process_result->push_back(pr);
            return left >= right;
        }
        int equality(int left, int right, int node_index)
        {
            string message = "比較 " + to_string(left) + " == " + to_string(right);
            struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, input_layer_queue.useClearLayerQueue(), node_index};
            process_result->push_back(pr);
            return left == right;
        }
        int equality(string left, string right, int node_index)
        {
            string message = "比較 " + left + " == " + right;
            struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_input, message, input_layer_queue.useClearLayerQueue(), node_index};
            process_result->push_back(pr);
            return left == right;
        }

        string resolution_calc_string(int node_index)
        {
            SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
            if (current_node.children.size() == 1)
            {
                string r = resolution_calc_string(current_node.children[0]);
                return r;
            }
            if (current_node.token_label == is_id_TerminalSymbol)
            {
                input_layer_queue.enqueueLayerQueue(ProcessVisualization::is_id_timeline_magic_number_layer);
                return current_node.token;
            }

            SyntacticTreeNode child_left = (*syntactic_analysis_tree)[current_node.children[0]];
            SyntacticTreeNode child_right = (*syntactic_analysis_tree)[current_node.children[1]];

            string left;
            string right;
            string ans;

            left = resolution_calc_string(current_node.children[0]);
            right = resolution_calc_string(current_node.children[1]);
            string token = current_node.token;

            if (token == "+")
            {
                ans = text_join(left, right);
            }

            return ans;
        }
        int resolution_calc_int(int node_index)
        {

            SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];
            if (current_node.children.size() == 1)
            {
                int r = resolution_calc_int(current_node.children[0]);
                return r;
            }
            if (current_node.parent_token == "<value_name>")
            {
                string value_name = current_node.token;
                printf("cal get %s\n", value_name.c_str());
                int val;
                vpu->getValue(value_name, val);
                printf("cal get2 %d\n", val);

                bool hasLayer = vpu->hasLayer(value_name);

                if (!hasLayer)
                {
                    struct ProcessVisualization::ProcessAnalysis pr = {ProcessVisualization::is_id_process_type_error, "未定義変数のアクセス", {}, node_index};
                    process_result->push_back(pr);
                    return 0;
                }

                int layer = vpu->getLayer(value_name);
                input_layer_queue.enqueueLayerQueue(layer);

                return val;
            }

            if (current_node.parent_token == "<number>")
            {
                input_layer_queue.enqueueLayerQueue(ProcessVisualization::is_id_timeline_magic_number_layer);
                return stoi(current_node.token);
            }

            printf("calc %d -> %d %d\n", node_index, current_node.children[0], current_node.children[1]);

            SyntacticTreeNode child_left = (*syntactic_analysis_tree)[current_node.children[0]];
            SyntacticTreeNode child_right = (*syntactic_analysis_tree)[current_node.children[1]];

            int left;
            int right;

            left = resolution_calc_int(current_node.children[0]);
            right = resolution_calc_int(current_node.children[1]);
            string token = current_node.token;

            int ans;

            int bulletin_node_index = node_index;

            if (token == "+")
            {
                ans = addition(left, right, bulletin_node_index);
            }
            if (token == "-")
            {
                ans = subtraction(left, right, bulletin_node_index);
            }
            if (token == "*")
            {
                ans = multiplication(left, right, bulletin_node_index);
            }
            if (token == "/")
            {
                ans = division(left, right, bulletin_node_index);
            }
            if (token == "<")
            {
                ans = less(left, right, bulletin_node_index);
            }
            if (token == "<=")
            {
                ans = less_equal(left, right, bulletin_node_index);
            }
            if (token == ">")
            {
                ans = greater(left, right, bulletin_node_index);
            }
            if (token == ">=")
            {
                ans = greater_equal(left, right, bulletin_node_index);
            }
            if (token == "==")
            {
                ans = equality(left, right, bulletin_node_index);
            }
            printf("calcSoftjTree %d : %d %s %d\n", ans, left, token.c_str(), right);

            return ans;
        }

        void recursion(int node_index)
        {

            SyntacticTreeNode current_node = (*syntactic_analysis_tree)[node_index];

            // char *text = current_node.token.c_str();
            string token = current_node.token;
            const char *token_c = token.c_str();

            printf("recursion %s\n", token_c);

            if (token == "<if>")
            {
                ifCalc(node_index);
                return;
            }
            if (token == "<while>")
            {
                whileCalc(node_index);
                return;
            }
            if (token == "=")
            {
                equal(node_index);
                return;
            }
            if (token == "+" || token == "-" || token == "*" || token == "/" || token == "<" || token == "<=" || token == ">" || token == ">=" || token == "==")
            {
                resolution_calc_int(node_index);
                return;
            }

            for (int i = 0; i < current_node.children.size(); i++)
            {
                recursion(current_node.children[i]);
            }
        }

        ProcessVisualization::Argument extractValueDefinition(int node_index)
        {
            SyntacticTreeNode node = (*syntactic_analysis_tree)[node_index];
            SyntacticTreeNode node_left = (*syntactic_analysis_tree)[node.children[0]];
            SyntacticTreeNode node_right = (*syntactic_analysis_tree)[node.children[1]];
            printf("extractValueDefinition %s %s %d\n",node_left.token.c_str(),node_right.token.c_str(),node_index);

            struct ProcessVisualization::Argument rvarg = {node_left.token, node_right.token};

            return rvarg;
        }

        void extractArgument(int node_index, ProcessVisualization::vArgument &extract_args)
        {
            SyntacticTreeNode node = (*syntactic_analysis_tree)[node_index];

            for (int i = 0; i < node.children.size(); i++)
            {
                int child_node_index = node.children[i];
                SyntacticTreeNode child_node = (*syntactic_analysis_tree)[child_node_index];

                if (child_node.token == "<value_definition>")
                {
                    ProcessVisualization::Argument rvarg = extractValueDefinition(child_node_index);
                    extract_args.push_back(rvarg);
                    continue;
                }

                if (child_node.token_label != is_id_NonterminalSymbol)
                {
                    extractArgument(child_node_index, extract_args);
                }
            }
        }

        void preparationFunction(int node_index)
        {
            SyntacticTreeNode node = (*syntactic_analysis_tree)[node_index];
            ProcessVisualization::vArgument extract_args = {};

            ProcessVisualization::Argument function_definition = extractValueDefinition(node.children[0]);
            extractArgument(node.children[1], extract_args);


            printf("preparationFunction %s %s %d\n",function_definition.name.c_str(),function_definition.type.c_str(),node_index);
            ProcessVisualization::FunctionUnit function_unit(function_definition.name, function_definition.type, extract_args, node_index);
            fpu->addFunction(function_unit);
        }

        void preparationTree()
        {
            for (int i = 0; i < syntactic_analysis_tree->size(); i++)
            {
                SyntacticTreeNode node = (*syntactic_analysis_tree)[i];

                if (node.token == "<function>")
                {
                    preparationFunction(i);
                    // fpu->addFunction();
                }
            }
        }

    public:
        SoftjTree(vSyntacticTree &syntactic_analysis_tree, ProcessVisualization::vProcessAnalysis &process_result, ProcessVisualization::VariablePossessionUnion &vpu, ProcessVisualization::FunctionPossessionUnion &fpu)
        {

            this->syntactic_analysis_tree = &syntactic_analysis_tree;
            this->process_result = &process_result;
            this->vpu = &vpu;
            this->fpu = &fpu;
            preparationTree();

            recursion(0);
        }
    };

};

#endif