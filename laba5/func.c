#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int* digit_arr_memory_allocate(int* digit_arr)
{
    if ((digit_arr = malloc(sizeof(int))) == NULL) 
    {
        printf("Memory allocation failed");
        return NULL;
    }
    else 
    {
        digit_arr = 0;      //!!!
        return digit_arr;
    }
}

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
    string = (int*)malloc(string_size*sizeof(char));
    if (string == NULL)
    {
        printf("Memory allocation failed");
        return NULL;
    }
    else return string;
}


char* string_input(char* string)
{
    if (gets_s(string, sizeof(string)) == NULL) printf("Input erorr");
}


void string_digit_word(char* string, int* digit_arr)
{
    int n = 0;                                                                                                              //Для масіву сум лічбаў
    for (int i = 0; string[i] != '\0'; i++)
    {
        if ((string[i] >= LOWEST_ASCII_DIGIT && string[i] <= HIGHEST_ASCII_DIGIT) && (string[i-1] == SPACE || i == 0))
        {
            do
            {
                //check lectos
                
                digit_arr[n] += string[i];
                
            } while (string[i] >= LOWEST_ASCII_DIGIT && string[i] <= HIGHEST_ASCII_DIGIT);
            
            
        }
        
    }
    
}

//c >= 48 && c <= 57

