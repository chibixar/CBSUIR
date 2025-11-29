//
#include <stdio.h>
#include "header.h"

int main(void)
{
    char ch_to_loop, ch_to_sort;
    char** text;
    int number_of_strings, max_string_size;
    int low, high;
    int digital_sum;
    do
    {
        digital_sum = 0;
        printf("Enter the number of strings you would enter:\n");
        number_of_strings = GetInt();
        low = 0;
        high = number_of_strings - 1;
        printf("Enter the number of characters in the longest string (less than 81):\n");
        max_string_size = GetInt() + 1;
        text = text_memory_allocate(text, number_of_strings, max_string_size);
        text = text_input(text, number_of_strings, max_string_size);
        printf("Sort by name: 'a'      Sort by salary: 'b'\n");
        while((ch_to_sort = getchar()) =='\n');
        while (ch_to_sort != 'a' && ch_to_sort != 'b') printf("Invalid input. Enter an 'a' or 'b'\n");
        printf("Sorted text:\n");
        if(ch_to_sort == 'a') Quick_Sort_Alphabetically(text, low, high);                                                   //parametr
        // else text = text_sort_by_salary();                                                                  //parametr
        output_text(text, number_of_strings);                                                                                           //

        printf("Do you want to try again? (Y/n): ");
        while((ch_to_loop = getchar()) =='\n');
    } while (ch_to_loop == 'y' || ch_to_loop == 'Y');
    printf("Programm terminated.");
    return 0;
    
}