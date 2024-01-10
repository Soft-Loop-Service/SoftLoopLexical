// 字句解析定義ファイル

#ifndef __LexicalAnalysisDefinition
#define __LexicalAnalysisDefinition

#include "./../definition.hpp"
#include "./../debug.hpp"
#include "./../symbol.hpp"

struct lexicalToken
{
    string token;
    string token_type;

    int source_code_line;
    int source_code_column;
};

typedef vector<lexicalToken> vLexicalToken;

#endif