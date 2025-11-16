#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include <string.h>

int GetInt(void) {
    int value;
    char ch;

    while (1) {                                                     //бясконнцы цыкл.

        if (scanf("%d", &value) == 1) {                             //калі гэта цэлы лік.
            rewind(stdin);                                          //чысціць буфер уводу.
            return value;                                           //вяртае знач. з клавіятуры.
        } else {
            printf("Invalid input. Please enter an integer.\n");
            rewind(stdin);                                          //чысціць буфер уводу.
        }
    }
}


char* string_memory_allocate(char* string, int string_size)
{
    string = (char*)malloc(string_size*sizeof(char));
    if (string == NULL)
    {
        printf("Memory allocation failed");
        exit(1);
    }
    return string;
}


char* string_input(char* string, int string_size)
{
    if (fgets(string, string_size, stdin) == NULL) 
    {
        printf("Input erorr");
        exit(1);
    }
    else return string;
}


void string_digit_word(char* string, int* sum, int* digit_count)
{
    int i = 0, j = 0;       
    while(string[i] == ' ') {i++; j++;};                                                                                                   //Для масіву сум лічбаў
    while (string[i] != '\0')
    {
        *digit_count = 0;
        if(word_isdigit(string, sum, digit_count, i))
            i += *digit_count;
            else string[j++]=string[i++];   
    }
    string[j]='\0';
    if (j>0) strcat(string, " ");
    char buf[32];
    sprintf(buf, "%d", *sum);
    strcat(string, buf);
}

int word_isdigit(char* string, int* sum, int* digit_count, int i)
{
    int k = i;
    int temp_sum = 0;
    *digit_count = 0;
    if (string[i] == ' ' || string[i] == '\0')
        return 0;
    
    for (; string[k] != '\0' && string[k] != ' '; k++)
    {
        if (!char_isdigit(string, k))
            return 0;
        temp_sum += (string[k] - '0');                              //сумаваць значэнні, а не ASCII.
        (*digit_count)++;
    }
    
    if (*digit_count == 0)
        return 0;
    

    *sum += temp_sum;
    return 1; 
}

int char_isdigit(char* string, int i)
{
    if (string[i] >= LOWEST_ASCII_DIGIT && string[i] <= HIGHEST_ASCII_DIGIT)
    return 1; else return 0;
}

//c >= 48 && c <= 57

