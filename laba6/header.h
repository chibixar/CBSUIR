#ifndef HEADER_H                                                  
#define HEADER_H                                                  

#define LOWEST_ASCII_DIGIT 48                                      //мінімальны ASCII код лічбы.
#define HIGHEST_ASCII_DIGIT 57                                     //максімальны ASCII код лічбы.
#define SPACE 32                                                   //ASCII код прабелу.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int GetInt(void);                                                  //прататып функцыі ўводу цэлага ліку.
char** text_memory_allocate(char** text, int number_of_strings, int max_string_size);
void text_free(char **text, int number_of_strings);
char** text_input(char** text, int number_of_strings, int max_string_size);
void output_text(char** text, int number_of_strings);
void swap_str(char** a, char** b);
int compare_first_letter(const char* a, const char* b);
int partition_name(char** text, int low, int high);
void Quick_Sort_Alphabetically(char** text, int low, int high);
void QuickSort_Name(char ** text, int low, int high);

int* digital_sum_memory_allocation(int *digital_sum, int number_of_strings);
void swap_num(int* a, int* b);
int char_isdigit(char** text, int i, int j);
int digital_sum_calculation(char** text, int* digital_sum, int i, int j, int len);
void salary_find(char** text, int* digital_sum, int number_of_strings, int max_string_size);
void QuickSort_Salary(char ** text, int low, int high, int* digital_sum);
#endif         