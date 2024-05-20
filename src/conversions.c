#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/conversions.h"

// Returns base*10^power
int ten_pow(int base, int power)
{
    for(int i = 1; i < power; i++)
        base *= 10;

    return base;
}


// Converts a character to a digit.
int ctoi(char character)
{
    // A number in ASCII is 48 bigger than its numerical value.
    // 0's ASCII value is 48.
    return (int)character - '0';
}


int stoi(char* string)
{
    char is_negative = 0;
    int power_of_ten = 0;
    int return_value = 0;

    // If integer is negative, set is_negative flag and skip "-".
    if(*string == '-')
    {
        is_negative = 1;
        string++;
    }

    char* string_ptr = string;
    
    while(*string_ptr != '\0')
    {
        power_of_ten++;
        string_ptr++;
    }
    
    for(; power_of_ten > 0; power_of_ten--)
    {
        return_value += ten_pow(ctoi(*string), power_of_ten);
        string++;
    }

    return is_negative ? return_value * -1 : return_value;    
}


char* dtos(double number)
{
    char* string = malloc(26);
    sprintf(string, "%f", number);
    return string;    
}


double stod(char* string)
{
    char* whole_part_ptr = string;
    char* whole_part_end = string;
    int whole_length = 0;

    // Convert the whole part to double.
    while(*whole_part_end && *whole_part_end != '.')
    {
        whole_part_end++;
        whole_length++;
    }

    whole_part_ptr = malloc(whole_length+1);
    strncpy(whole_part_ptr, string, whole_length);
    whole_part_ptr[whole_length] = '\0';

    double whole_part = stoi(whole_part_ptr);
    free(whole_part_ptr);

    // Convert the fraction part, if it exists.
    if(*whole_part_end)
    {
        char* fraction_part_begin = whole_part_end+1;
        char* fraction_part_end = fraction_part_begin;
        int fraction_length = 0;

        while(*fraction_part_end)
        {
            fraction_length++;
            fraction_part_end++;
        }

        char* fraction_part_ptr = malloc(fraction_length+1);
        strncpy(fraction_part_ptr, fraction_part_begin, fraction_length);
        fraction_part_ptr[fraction_length] = '\0';
        
        double fraction_part = stoi(fraction_part_ptr);
        free(fraction_part_ptr);

        // Same as fraction_part * 10^-fraction_length.
        for(int i = 0; i < fraction_length; i++)
            fraction_part /= 10;

        return whole_part + fraction_part;
    }
    
    return whole_part;
}

