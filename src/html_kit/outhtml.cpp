
#include "./html_kit.hpp"

namespace HTMLParse
{

    void outputHtml(Syntactic::vSyntacticTree syntactic_analysis_tree, ProcessVisualization::ProcessAnalysisTimeline process_timeline, ProcessVisualization::VariablePossessionUnion variable_possession_union, LexicalAnalysis::vLexicalToken token_string_vector, string source_code_file_name)
    {
        ProcessVisualization::vProcessAnalysis process_result = process_timeline.getProcessResult();
        std::ofstream writing_file;
        std::string filename = "test.html";

        writing_file.open(filename, std::ios::out);

        std::ifstream html_header_stream("./src/html_kit/include/header.html");
        std::string html_header_stream_string((std::istreambuf_iterator<char>(html_header_stream)), std::istreambuf_iterator<char>());
        html_header_stream.close();

        std::ifstream html_header_meta_stream("./src/html_kit/include/header_meta.html");
        std::string html_header_meta_stream_string((std::istreambuf_iterator<char>(html_header_meta_stream)), std::istreambuf_iterator<char>());
        html_header_meta_stream.close();

        std::ifstream css_header_stream("./src/html_kit/include/header.css");
        std::string css_header_stream_string((std::istreambuf_iterator<char>(css_header_stream)), std::istreambuf_iterator<char>());
        css_header_stream.close();

        std::ifstream html_controller_stream("./src/html_kit/include/controller.html");
        std::string html_controller_stream_string((std::istreambuf_iterator<char>(html_controller_stream)), std::istreambuf_iterator<char>());
        html_controller_stream.close();

        std::ifstream css_main_stream("./src/html_kit/include/main.css");
        std::string css_main_stream_string((std::istreambuf_iterator<char>(css_main_stream)), std::istreambuf_iterator<char>());
        css_main_stream.close();

        std::ifstream css_timeline_stream("./src/html_kit/include/timeline.css");
        std::string css_timeline_stream_string((std::istreambuf_iterator<char>(css_timeline_stream)), std::istreambuf_iterator<char>());
        css_timeline_stream.close();

        std::ifstream css_code_view_stream("./src/html_kit/include/codeview.css");
        std::string css_code_view_stream_string((std::istreambuf_iterator<char>(css_code_view_stream)), std::istreambuf_iterator<char>());
        css_code_view_stream.close();

        std::ifstream css_controller_stream("./src/html_kit/include/controller.css");
        std::string css_controller_stream_string((std::istreambuf_iterator<char>(css_controller_stream)), std::istreambuf_iterator<char>());
        css_controller_stream.close();

        std::ifstream js_timeline_stream("./src/html_kit/include/codeview.js");
        std::string js_timeline_stream_string((std::istreambuf_iterator<char>(js_timeline_stream)), std::istreambuf_iterator<char>());
        js_timeline_stream.close();

        std::ifstream css_insideview_stream("./src/html_kit/include/insideview.css");
        std::string css_insideview_stream_string((std::istreambuf_iterator<char>(css_insideview_stream)), std::istreambuf_iterator<char>());
        css_insideview_stream.close();

        std::ifstream js_insideview_stream("./src/html_kit/include/insideview.js");
        std::string js_insideview_stream_string((std::istreambuf_iterator<char>(js_insideview_stream)), std::istreambuf_iterator<char>());
        js_insideview_stream.close();

        std::ifstream html_insideview_stream("./src/html_kit/include/insideview.html");
        std::string html_insideview_stream_string((std::istreambuf_iterator<char>(html_insideview_stream)), std::istreambuf_iterator<char>());
        html_insideview_stream.close();

        std::ifstream js_setup_stream("./src/html_kit/include/setup.js");
        std::string js_setup_stream_string((std::istreambuf_iterator<char>(js_setup_stream)), std::istreambuf_iterator<char>());
        js_setup_stream.close();

        Conversion::Timeline html_timeline(&syntactic_analysis_tree, &process_result, &variable_possession_union, &token_string_vector, source_code_file_name);
        Conversion::SourceCodeView html_source_code_view(&syntactic_analysis_tree, &process_result, &variable_possession_union, &token_string_vector);

        string css_style = "<style>" + css_header_stream_string + css_main_stream_string + css_controller_stream_string + css_code_view_stream_string + css_timeline_stream_string + css_insideview_stream_string + "</style>";

        string javascript_element = "<script type=\"text/javascript\"> ";
        javascript_element += html_timeline.getJson();
        javascript_element += js_timeline_stream_string;
        javascript_element += js_insideview_stream_string;
        javascript_element += js_setup_stream_string;
        javascript_element += " </script>";

        string html_meta = "<!DOCTYPE html><html lang=\"ja\">";

        writing_file << html_meta << endl;
        writing_file << css_style << endl;
        writing_file << javascript_element << endl;

        string html_source_code_view_body = html_source_code_view.getBody();
        string html_timeline_body = html_timeline.getBody();

        string body_str_sta = "<body onload=\"firstScript()\">";
        string body_str_end = "</body>";

        string codeview_upper_str_sta = "<div class=\"codeview_upper_side\">";
        string codeview_upper_str_end = "</div>";
        string codeview_bottom_str_sta = "<div class=\"codeview_bottom_side\">";
        string codeview_bottom_str_end = "</div>";

        string left_str_sta = "<div class=\"left_side\">";
        string left_str_end = "</div>";
        string right_str_sta = "<div class=\"right_side\">";
        string right_str_end = "</div>";

        string sys_str_sta = "<div class=\"system\">";
        string sys_str_end = "</div>";
        string html_meta_end = "</html>";

        string dividing_border = "<div class=\"dividing_border\"></div>";
        writing_file << html_header_meta_stream_string << endl;
        writing_file << html_header_stream_string << endl;
        writing_file << body_str_sta << endl;

        writing_file << sys_str_sta << endl;

        writing_file << left_str_sta << endl;
        writing_file << codeview_upper_str_sta << endl;
        writing_file << html_source_code_view_body << endl;
        writing_file << codeview_upper_str_end << endl;

        writing_file << codeview_bottom_str_sta << endl;
        writing_file << html_insideview_stream_string << endl;
        writing_file << codeview_bottom_str_end << endl;

        writing_file << left_str_end << endl;

        writing_file << dividing_border << endl;
        writing_file << right_str_sta << endl;
        writing_file << html_controller_stream_string << endl;
        writing_file << html_timeline_body << endl;

        writing_file << right_str_end << endl;

        writing_file << sys_str_end << endl;
        writing_file << body_str_end << endl;
        writing_file << html_meta_end << endl;

        writing_file.close();

        printf("%s\n", css_style.c_str());
    }
}
