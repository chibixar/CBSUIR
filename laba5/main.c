// Даны натуральное число n и символы S1,...,Sn. Строку s1,...,sn обработать
// так, чтобы все слова, состоящие только из цифр, были удалены, их сумма стояла
// последним словом в строке.

#include <stdio.h>
#include "header.h"

int main()
{   
    int string_size;
    int sum = 0, digit_count = 0;
    char* string;
    // int* digit_arr;
    char choice;
    do
    {
        printf("Enter the number of characters in your string (less than 81):\n");
        string_size = GetInt() + 1;
        // digit_arr = digit_arr_memory_allocate(digit_arr);
        string=(string_memory_allocate(string, string_size));
        printf("Enter a string:\n");
        string_input(string, string_size);
        string_digit_word(string, &sum, &digit_count);
        printf("Modified string:\n");
        puts(string);

        printf("Do you want to try again? (Y/n): ");
        choice = getchar();
        while ((choice = getchar()) == '\n');
        
    } while (choice == 'Y' || choice == 'y');
    
    
    




 printf("Program terminated.\n");
    return 0;
}
