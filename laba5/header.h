#ifndef HEADER_H
#define HEADER_H

#define LOWEST_ASCII_DIGIT 48
#define HIGHEST_ASCII_DIGIT 57
#define SPACE 32

int GetInt(void);                                               //прататып функцыі ўводу цэлага ліку.
int* digit_arr_memory_allocate(int* digit_arr);
char* string_memory_allocate(char* string, int string_size);
char* string_input(char* string);
void string_digit_word(char* string, int* digit_arr)

#endif