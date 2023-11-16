
#ifndef __PRAD
#define __PRAD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "./../definition.hpp"

class ProcessAnalysis;
typedef std::vector<ProcessAnalysis> vProcessAnalysis;

class ProcessAnalysis
{
    string operation;
    string value;
};

#endif