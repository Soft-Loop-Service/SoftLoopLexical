
#ifndef __LRTABLE
#define __LRTABLE

#define LR_table_operation_none 'n'
#define LR_table_operation_shift 's'
#define LR_table_operation_reduce 'r'
#define LR_table_operation_accept 'a'
#define LR_table_operation_goto 'g'
#include "./../DFA/dfa.hpp"

namespace LRTable
{

    int generateLRtable(DFAParse::vDFANode dfa_node_graph, BNFParse::BNFToken &bnf_token_p, BNFParse::RetrieveSymbol terminal_symbol, BNFParse::RetrieveSymbol nonterminal_symbol,
                        LRTableMultilayer &LR_table_multilayer);

    template <typename T>
    class LRTable
    {
    protected:
        DFAParse::vDFANode dfa_node_graph;
        int column_length;

    public:
        map<string, vector<T>> LR_table_column_map;

        
        string outputTable();
        void inputTabke();
        void makeTable();
        void debug();
        void addSymbol(string cstr);
        LRTable();
        LRTable(string table_string);
        LRTable( DFAParse::vDFANode dfa_node_graph, BNFParse::BNFToken &bnf_token_p, BNFParse::RetrieveSymbol symbol);
    };

    template <typename U>
    class LRTableMakeGoto : public LRTable<U>
    {

    public:
        using LRTable<U>::LRTable;
        // LRTableMakeGoto() {}
    };

    template <typename U>
    class LRTableMakeShift : public LRTable<U>
    {

    public:
        using LRTable<U>::LRTable;
        // LRTableMakeShift(){};

        void makeTable();
    };

    template <typename U>
    class LRTableMakeReduce : public LRTable<U>
    {

    public:
        using LRTable<U>::LRTable;
        void makeTable();

        // LRTableMakeReduce(){};
    };

    template <typename U>
    class LRTableMakeAccept : public LRTable<U>
    {

    public:
        using LRTable<U>::LRTable;
        // LRTableMakeAccept();

        void makeTable();
    };

    struct ReduceFormula // 構文解析用
    {
        string token_left;                             // 左辺
        BNFParse::vDeploymentTokenStruct token_vector; // 展開したBNFの右辺
    };
    typedef vector<ReduceFormula> vReduceFormula;

    class LRTableLoad
    {
    private:
        vector<string> result;
        int point = 0;

    public:
        LRTableLoad(string table_string);
        string road_token();
    };

    class LRTableCell
    {
    protected:
        char operation = LR_table_operation_none;

    public:
        // virtual void setCell(int next_state);
        // virtual void debugCell();
    };

    class LRTableGotoCell : public LRTableCell
    {
    private:
        char operation = LR_table_operation_goto;
        bool is_valid = false;
        int next_state = -1;

    public:
        void setCell(int next_state);
        string getCellString();
        void parseStringCell(LRTableLoad *loader);
        int getCell();
        int getValid();
        void debugCell();
    };

    class LRTableShiftCell : public LRTableCell
    {
    private:
        char operation = LR_table_operation_shift;
        bool is_valid = false;

    public:
        int next_state = -1;
        void setCell(int next_state);
        string getCellString();
        void parseStringCell(LRTableLoad *loader);
        bool getValid();
        int getCell();
        void debugCell();
    };

    class LRTableReduceCell : public LRTableCell
    {
    private:
        char operation = LR_table_operation_reduce;

        struct ReduceFormula reduce_formula;
        bool is_valid = false;

    public:
        void setCell(string token_left, BNFParse::vDeploymentTokenStruct token_vector);
        void parseStringCell(LRTableLoad *loader);
        string getCellString();
        ReduceFormula getCell();
        bool getValid();
        void debugCell();
    };

    class LRTableAcceptCell : public LRTableCell
    {
    private:
        char operation = LR_table_operation_accept;
        bool is_valid = false;

    public:
        string getCellString();
        void parseStringCell(LRTableLoad *loader);
        void setCell(bool is_valid);
        bool getValid();
        void debugCell();
    };
    struct LRTableMultilayer
    {
        LRTableMakeGoto<LRTableGotoCell> LR_table_goto;
        LRTableMakeShift<LRTableShiftCell> LR_table_shift;
        LRTableMakeReduce<LRTableReduceCell> LR_table_reduce;
        LRTableMakeAccept<LRTableAcceptCell> LR_table_accept;
    };

};

#endif