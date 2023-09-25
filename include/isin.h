#ifndef ISIN_H
#define ISIN_H

extern char* lower_case_alphabet;
extern char* upper_case_alphabet;
extern char* numbers;
extern char* operators;
extern char* parentheses;

int is_in(char character, char* list_of_characters);

#endif