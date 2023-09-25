#include "../include/constants.h"

#include <stdio.h>
#include <string.h>

const double PI = 3.141592653589793;
const double E = 2.718281828459045;
const double FI = 1.618033988749894;

double get_constant_value(char* input_string)
{
    if(!strcmp(input_string, "PI")) { return PI; }
    if(!strcmp(input_string, "E")) { return E; }
    if(!strcmp(input_string, "FI")) { return FI; }
}