#include <string.h>

#include "../include/isin.h"

char* lower_case_alphabet = "abcdefghijklmnopqrstuvwxyz";
char* upper_case_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char* numbers = "0123456789.";
char* operators = "+-*/^";
char* parentheses = "()";

// Checks if a character is a part of a character array. Can be used as e.g. isdigit or isalpha.
int is_in(char character, char* list_of_characters)
{   
    for(int i = 0; i < strlen(list_of_characters); i++)
    {
        if(list_of_characters[i] == character) { return 1; }
    }

    return 0;
}

