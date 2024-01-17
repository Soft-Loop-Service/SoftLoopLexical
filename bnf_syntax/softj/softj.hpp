
#ifndef __SOFTJ
#define __SOFTJ

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

#include "./calc.hpp"
#include "./expr.hpp"
#include "./extract.hpp"
#include "./function.hpp"
#include "./logic.hpp"
#include "./preparation.hpp"
#include "./recursion.hpp"
#include "./resolution.hpp"
#include "./array.hpp"
#include "./softj_tree.hpp"

// このファイルはinclude用なので、消さないように

namespace LanguageSpecifications
{
    namespace SoftjLanguage
    {

        class Softj;
    }
};
#endif