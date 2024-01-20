#include "./../html_kit.hpp"

namespace HTMLParse
{

    namespace Conversion
    {

        void Timeline::timelineLeftArea(int process_order, int html_parent_node, ProcessVisualization::ProcessAnalysis process)
        {
            HTMLKit::HtmlKitElement process_area("div");
            process_area.addEClass("process_left");

            string e_id = "process" + to_string(process_order);
            process_area.setEId(e_id);
            process_area.addEvent("onclick", "\"messageClick(" + to_string(process_order) + ")\"");
            process_area.addEvent("onMouseOver", "\"messageHover(" + to_string(process_order) + ")\"");
            process_area.addEvent("onMouseOut", "\"messageHoverOut(" + to_string(process_order) + ")\"");

            int process_node_index = html_kit_tree.add_node(html_parent_node, process_area);

            timelineMessageArea(process_order, process_node_index, process);
            // timelineLineColumnArea(process_node_index, process);
        }
        void Timeline::timelineRightArea(int process_order, int html_parent_node, ProcessVisualization::ProcessAnalysis process)
        {
            HTMLKit::HtmlKitElement process_area("div");
            process_area.addEClass("process_right");
            int process_node_index = html_kit_tree.add_node(html_parent_node, process_area);

            timelineLayerArea(process_order, process_node_index, process);
        }
        // int Timeline::timelineCommonArea(int process_order, int html_parent_node, ProcessVisualization::ProcessAnalysis process)
        // {

        //     return process_node_index;
        // }
        void Timeline::timelineMessageContextArea(string process_order, string source_code_line, string source_code_column, string message, int message_node_index)
        {
            HTMLKit::HtmlKitElement order_message_text_area("span");
            order_message_text_area.addEClass("message_order_text");
            order_message_text_area.setElement(process_order);
            html_kit_tree.add_node(message_node_index, order_message_text_area);

            HTMLKit::HtmlKitElement line_message_text_area("span");
            line_message_text_area.addEClass("message_line_text");
            line_message_text_area.setElement(source_code_line);
            html_kit_tree.add_node(message_node_index, line_message_text_area);

            HTMLKit::HtmlKitElement column_message_text_area("span");
            column_message_text_area.addEClass("message_column_text");
            column_message_text_area.setElement(source_code_column);
            html_kit_tree.add_node(message_node_index, column_message_text_area);

            HTMLKit::HtmlKitElement message_text_area("span");
            message_text_area.addEClass("message_text");
            message_text_area.setElement(message);
            html_kit_tree.add_node(message_node_index, message_text_area);
        }
        void Timeline::timelineMessageArea(int process_order, int html_parent_node, ProcessVisualization::ProcessAnalysis process)
        {
            HTMLKit::HtmlKitElement message_area("div");
            message_area.addEClass("message");

            if (process.process_type == ProcessVisualization::is_id_process_type_error)
            {
                message_area.addEClass("message_error");
            }
            if (process.process_type == ProcessVisualization::is_id_process_type_warning)
            {
                message_area.addEClass("message_warning");
            }
            if (process.process_type == ProcessVisualization::is_id_process_type_language_error)
            {
                message_area.addEClass("message_language_error");
            }

            int source_code_line = (*syntactic_analysis_tree_p)[process.node_index].source_code_line;
            int source_code_column = (*syntactic_analysis_tree_p)[process.node_index].source_code_column;

            int message_node_index = html_kit_tree.add_node(html_parent_node, message_area);

            timelineMessageContextArea(to_string(process_order), to_string(source_code_line), to_string(source_code_column), process.message, message_node_index);
        }

        void Timeline::timelineLineColumnArea(int html_parent_node, ProcessVisualization::ProcessAnalysis process)
        {
            HTMLKit::HtmlKitElement line_column_area("div");
            line_column_area.addEClass("source_code_position");
            int line_column_area_index = html_kit_tree.add_node(html_parent_node, line_column_area);

            HTMLKit::HtmlKitElement line_area("div");
            line_area.addEClass("source_code_position_line");
            int line_area_index = html_kit_tree.add_node(line_column_area_index, line_area);

            HTMLKit::HtmlKitElement column_area("div");
            column_area.addEClass("source_code_position_column");
            int column_area_index = html_kit_tree.add_node(html_parent_node, line_column_area);

            int source_code_line = (*syntactic_analysis_tree_p)[process.node_index].source_code_line;
            int source_code_column = (*syntactic_analysis_tree_p)[process.node_index].source_code_column;

            HTMLKit::HtmlKitElement source_code_position_line_text_area("span");
            source_code_position_line_text_area.addEClass("source_code_position_text");
            source_code_position_line_text_area.setElement(to_string(source_code_line));
            html_kit_tree.add_node(line_area_index, source_code_position_line_text_area);

            HTMLKit::HtmlKitElement source_code_position_column_text_area("span");
            source_code_position_column_text_area.addEClass("source_code_position_text");
            source_code_position_column_text_area.setElement(to_string(source_code_column));
            html_kit_tree.add_node(column_area_index, source_code_position_column_text_area);
        }

        void Timeline::timelineLayerArea(int process_order, int html_parent_node, ProcessVisualization::ProcessAnalysis process)
        {
            HTMLKit::HtmlKitElement layer_area("div");
            layer_area.addEClass("layer");
            int layer_area_index = html_kit_tree.add_node(html_parent_node, layer_area);

            HTMLKit::HtmlKitElement layer_horizontal_area("div");
            layer_horizontal_area.addEClass("layer_horizontal");

            int layer_node_index = html_kit_tree.add_node(layer_area_index, layer_horizontal_area);

            // int layer_node_index_output_index = html_kit_tree.add_node(layer_area_index, layer_horizontal_area);

            for (int i = 0; i < depth_length; i++)
            {
                timelineLayerInputArea(layer_node_index, process, i);
            }
        }

        void Timeline::timelineLayerInputArea(int html_parent_node, ProcessVisualization::ProcessAnalysis process, int unit_num)
        {
            int layer_unit_node_index = timelineLayerUnitArea(html_parent_node, process, unit_num);

            HTMLKit::HtmlKitElement layer_unit_station_area("div");
            layer_unit_station_area.addEClass("layer_unit_station");
            if (process.depth != unit_num)
            {
                return;
            }

            timelineLayerUnitStationArea(layer_unit_node_index, process, layer_unit_station_area);
        }

        int Timeline::timelineLayerUnitArea(int html_parent_node, ProcessVisualization::ProcessAnalysis process, int unit_num)
        {
            HTMLKit::HtmlKitElement layer_unit_area("div");
            layer_unit_area.addEClass("layer_unit");
            int layer_unit_node_index = html_kit_tree.add_node(html_parent_node, layer_unit_area);

            return layer_unit_node_index;
        }

        void Timeline::timelineLayerUnitStationArea(int html_parent_node, ProcessVisualization::ProcessAnalysis process, HTMLKit::HtmlKitElement layer_unit_station_area)
        {
            layer_unit_station_area.addEClass(process.process_type);
            int layer_unit_station_node_index = html_kit_tree.add_node(html_parent_node, layer_unit_station_area);
        }

        void Timeline::meta_data()
        {
            JsonKit::JsonKitElement meta_data("dist");
            int meta_data_index = json_kit_tree_meta.add_node(0, meta_data);

            JsonKit::JsonKitElement token_length("value", "token_length", token_string_vector_p->size());
            json_kit_tree_meta.add_node(meta_data_index, token_length);

            JsonKit::JsonKitElement source_code_file_name_value("value", "source_code_file_name", source_code_file_name);
            json_kit_tree_meta.add_node(meta_data_index, source_code_file_name_value);

            JsonKit::JsonKitElement process_length("value", "process_length", process_result_p->size());
            json_kit_tree_meta.add_node(meta_data_index, process_length);

            JsonKit::JsonKitElement variable_enumeration("value", "variable_enumeration");
            int variable_enumeration_node = json_kit_tree_meta.add_node(meta_data_index, variable_enumeration);

            JsonKit::JsonKitElement variable_enumeration_dist("dist");
            int variable_enumeration_dist_node = json_kit_tree_meta.add_node(variable_enumeration_node, variable_enumeration_dist);

            vint ve_keys = getMapKeyString(variable_enumeration_map);
            for (int i = 0; i < ve_keys.size(); i++)
            {
                int layer = ve_keys[i];
                ProcessVisualization::VariableProcessEnumeration ve = variable_enumeration_map[layer];

                JsonKit::JsonKitElement variable_enumeration_value_name("value", to_string(ve.layer));
                int variable_enumeration_value_name_node = json_kit_tree_meta.add_node(variable_enumeration_dist_node, variable_enumeration_value_name);

                JsonKit::JsonKitElement variable_enumeration_value_dist("dist");
                int variable_enumeration_value_dist_node = json_kit_tree_meta.add_node(variable_enumeration_value_name_node, variable_enumeration_value_dist);

                JsonKit::JsonKitElement variable_enumeration_name("value", "name", ve.name);
                json_kit_tree_meta.add_node(variable_enumeration_value_dist_node, variable_enumeration_name);

                JsonKit::JsonKitElement variable_enumeration_type("value", "type", ve.type);
                json_kit_tree_meta.add_node(variable_enumeration_value_dist_node, variable_enumeration_type);

                JsonKit::JsonKitElement variable_enumeration_layer("value", "layer", ve.layer);
                json_kit_tree_meta.add_node(variable_enumeration_value_dist_node, variable_enumeration_layer);

                JsonKit::JsonKitElement variable_enumeration_definition("value", "definition_node", ve.definition_node);
                json_kit_tree_meta.add_node(variable_enumeration_value_dist_node, variable_enumeration_definition);
            }
        }

        void Timeline::process_group()
        {
            JsonKit::JsonKitElement process_groups("array");
            int process_groups_index = json_kit_tree_process.add_node(0, process_groups);

            for (int i = 0; i < process_result_p->size(); i++)
            {
                process(i, process_groups_index);
            }
        }

        void Timeline::process(int process_index, int kit_index)
        {
            ProcessVisualization::ProcessAnalysis process_unit = (*process_result_p)[process_index];

            JsonKit::JsonKitElement process_node("dist");
            int process_kit_index = json_kit_tree_process.add_node(kit_index, process_node);

            JsonKit::JsonKitElement depth("value", "depth", process_unit.depth);
            json_kit_tree_process.add_node(process_kit_index, depth);

            JsonKit::JsonKitElement message("value", "message", process_unit.message);
            json_kit_tree_process.add_node(process_kit_index, message);

            JsonKit::JsonKitElement node_index("value", "node_index", process_unit.node_index);
            json_kit_tree_process.add_node(process_kit_index, node_index);

            Syntactic::SyntacticTreeNode node = (*syntactic_analysis_tree_p)[process_unit.node_index];
            JsonKit::JsonKitElement token_element("value", "token", node.token);
            json_kit_tree_process.add_node(process_kit_index, token_element);

            JsonKit::JsonKitElement token_order_element("value", "token_order", node.token_order);
            json_kit_tree_process.add_node(process_kit_index, token_order_element);

            JsonKit::JsonKitElement process_type("value", "process_type", process_unit.process_type);
            json_kit_tree_process.add_node(process_kit_index, process_type);

            JsonKit::JsonKitElement variable("value", "variable");
            int variable_node_index = json_kit_tree_process.add_node(process_kit_index, variable);

            JsonKit::JsonKitElement variable_dist("dist");
            int variable_dist_index = json_kit_tree_process.add_node(variable_node_index, variable_dist);

            mp_i_s variable_type = process_unit.variable_possession->getVariableType();
            mp_i_i variable_int = process_unit.variable_possession->getVariableInt();
            mp_i_s variable_string = process_unit.variable_possession->getVariableString();

            vint int_keys = getMapKeyString(variable_int);
            vint str_keys = getMapKeyString(variable_string);
            for (int i = 0; i < int_keys.size(); i++)
            {
                int layer = int_keys[i];
                JsonKit::JsonKitElement variable_inside_int("value", to_string(layer), to_string(variable_int[layer]));
                json_kit_tree_process.add_node(variable_dist_index, variable_inside_int);
            }
            for (int i = 0; i < str_keys.size(); i++)
            {
                int layer = str_keys[i];
                JsonKit::JsonKitElement variable_inside_str("value", to_string(layer), variable_string[layer]);
                json_kit_tree_process.add_node(variable_dist_index, variable_inside_str);
            }

            JsonKit::JsonKitElement pointer("value", "pointer");
            int pinter_node_index = json_kit_tree_process.add_node(process_kit_index, pointer);

            JsonKit::JsonKitElement pointer_dist("dist");
            int pointer_dist_index = json_kit_tree_process.add_node(pinter_node_index, pointer_dist);

            vint pointer_keys = getMapKeyString(process_unit.pointer_value_table);
            for (int i = 0; i < pointer_keys.size(); i++)
            {

                JsonKit::JsonKitElement pointer_vector_value("value", to_string(pointer_keys[i]));
                int pointer_value_index = json_kit_tree_process.add_node(pointer_dist_index, pointer_vector_value);

                JsonKit::JsonKitElement pointer_vector_value_list("array");
                int pointer_value_list_index = json_kit_tree_process.add_node(pointer_value_index, pointer_vector_value_list);

                vint pointer_vector = process_unit.pointer_value_table[pointer_keys[i]];
                for (int j = 0; j < pointer_vector.size(); j++)
                {
                    int p = pointer_vector[j];
                    JsonKit::JsonKitElement pointer_data("value");
                    pointer_data.set_element(p);
                    json_kit_tree_process.add_node(pointer_value_list_index, pointer_data);
                }
            }
        }

        Timeline::Timeline(Syntactic::vSyntacticTree *syntactic_analysis_tree_p, ProcessVisualization::vProcessAnalysis *process_result_p, ProcessVisualization::VariablePossessionUnion *variable_possession_union_p, LexicalAnalysis::vLexicalToken *token_string_vector_p, string source_code_file_name)
        {
            this->syntactic_analysis_tree_p = syntactic_analysis_tree_p;
            this->process_result_p = process_result_p;
            this->variable_possession_union_p = variable_possession_union_p;
            this->json_kit_tree_process = JsonKit::JsonKitTree();
            this->html_kit_tree = HTMLKit::HtmlKitTree();
            this->token_string_vector_p = token_string_vector_p;
            this->source_code_file_name = source_code_file_name;

            this->variable_enumeration_map = variable_possession_union_p->getVariableProcessEnumeration();

            int max_depth_length = 0;

            for (int i = 0; i < process_result_p->size(); i++)
            {
                int d = (*process_result_p)[i].depth;
                if (max_depth_length < d)
                {
                    max_depth_length = d + 1;
                }
            }

            this->depth_length = max_depth_length + 1;
        }

        string Timeline::getBody()
        {
            HTMLKit::HtmlKitElement timeline_area("div");
            timeline_area.addEClass("timeline");
            int timeline_area_index = html_kit_tree.add_node(0, timeline_area);

            HTMLKit::HtmlKitElement timeline_scroll_area("div");
            timeline_scroll_area.addEClass("timeline_scroll");
            int timeline_scroll_area_index = html_kit_tree.add_node(timeline_area_index, timeline_scroll_area);

            HTMLKit::HtmlKitElement timeline_left_area("div");
            timeline_left_area.addEClass("timeline_left");
            HTMLKit::HtmlKitElement timeline_right_area("div");
            timeline_right_area.addEClass("timeline_right");

            int timeline_left_index = html_kit_tree.add_node(timeline_scroll_area_index, timeline_left_area);
            int timeline_right_index = html_kit_tree.add_node(timeline_scroll_area_index, timeline_right_area);

            HTMLKit::HtmlKitElement context_left_area("div");
            context_left_area.addEClass("context_left_area");
            int context_left_area_index = html_kit_tree.add_node(timeline_left_index, context_left_area);
            timelineMessageContextArea("進行", "行", "列", "実行", context_left_area_index);

            HTMLKit::HtmlKitElement context_right_area("div");
            context_right_area.addEClass("context_right_area");
            int context_right_area_index = html_kit_tree.add_node(timeline_right_index, context_right_area);

            HTMLKit::HtmlKitElement context_right_text_area("span");
            context_right_text_area.addEClass("context_right_text");
            context_right_text_area.setElement("スコープ状況");
            html_kit_tree.add_node(context_right_area_index, context_right_text_area);

            HTMLKit::HtmlKitElement timeline_right_scroll_area("div");
            timeline_right_scroll_area.addEClass("timeline_right_scroll");
            int timeline_right_scroll_index = html_kit_tree.add_node(timeline_right_index, timeline_right_scroll_area);

            for (int i = 0; i < process_result_p->size(); i++)
            {
                ProcessVisualization::ProcessAnalysis pr = (*process_result_p)[i];
                timelineLeftArea(i, timeline_left_index, pr);
            }

            for (int i = 0; i < process_result_p->size(); i++)
            {
                ProcessVisualization::ProcessAnalysis pr = (*process_result_p)[i];
                timelineRightArea(i, timeline_right_scroll_index, pr);
            }

            printf("タイムライン木構造変換\n");

            string html_txt = html_kit_tree.parseHtml();
            printf("timeline area %s\n", html_txt.c_str());
            return html_txt;
            // return html_txt;
        }
        string Timeline::getJson()
        {
            process_group();
            meta_data();
            string meta_data = json_kit_tree_meta.parseJson();
            string process_data = json_kit_tree_process.parseJson();
            string meta_text = "const meta_data = " + meta_data + ";";
            string process_text = "const process_data = " + process_data + ";";
            string text = meta_text + process_text;
            return text;
            // return html_txt;
        }

    }

};
