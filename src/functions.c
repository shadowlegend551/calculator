#include <math.h>
#include <stdio.h> 

#include "../include/constants.h"
#include "../include/functions.h"

double absolute_value(double* number_array)
{
    double number = number_array[1];
    double result = number < 0 ? number * -1 : number;

    return result;
}


double average(double* number_array)
{
    double result = sum(number_array);

    return result / number_array[0];
}


double deg_to_rad(double* number_array)
{
    double degrees = number_array[1];

    return degrees * (PI / 180);
}


double factorial(double* number_array)
{
    double result = 1;

    for(double number = number_array[1]; number > 1; number--)
        result *= number;

    return result;
}


double modulo(double* number_array)
{
    double result = number_array[1];
    double subtractable = number_array[2];

    while(result - subtractable >= 0) { result -= subtractable; }

    return result;
}


double rad_to_deg(double* number_array)
{
    double radians = number_array[1];

    return radians * (180 / PI);
}



double square_root(double* number_array)
{
    int RESOLUTION = 20; 
    double original_number = number_array[1];

    // Often used roots.
    if(original_number == 0.5) 
        return 0.707106781186547;

    if(original_number == 2.0)
        return 1.414213562373095;

    if(original_number == 3.0)
        return 1.732050807568877;

    if(original_number == 4.0)
        return 2.0;

    if(original_number == 5.0)
        return 2.236067977499789;

    double iterable = original_number;

    for(int i = 0; i < RESOLUTION; i++)
    {
        iterable = (iterable + original_number/iterable) / 2;
    }

    return iterable;
}


double sum(double* number_array)
{
    double argument_amount = number_array[0];
    double result = 0;

    for(int i = 1; i <= argument_amount; i++)
    {
        result += number_array[i];
    }

    return result;
}
