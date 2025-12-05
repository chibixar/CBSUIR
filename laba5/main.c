// Даны натуральное число n и символы S1,...,Sn. Строку s1,...,sn обработать
// так, чтобы все слова, состоящие только из цифр, были удалены, их сумма стояла
// последним словом в строке.
#include "header.h"

int main()                                                         //пачатак асноўнай праграмы.
{   
    int string_size;                                               //памер радка.
    int sum = 0;                                                   //сума лічбаў.
    char* string;                                                  //указальнік на радок.
    char choice;                                                   //пераменная для паўтору праграмы.

    do {                                                           //цыкл паўтору праграмы.
        printf("Enter the number of characters in your string (less than 81):\n");
        string_size = GetInt() + 1;                                //атрымаць памер радка (+1 для '\0').

        string_memory_allocate(&string, string_size);              //выдзяленне памяці пад радок.

        printf("Enter a string:\n");                               
        string_input(string, string_size);                         //увод радка.

        string_digit_word(string, &sum);                           //апрацоўка радка.

        printf("Modified string:\n");                              
        puts(string);                                              //вывад мадыфікаванага радка.
        free(string);
        printf("Do you want to try again? (Y/n): ");               
                                               
        while ((choice = getchar()) == '\n');                      //прапускаем '\n'.

    } while (choice == 'Y' || choice == 'y');                      //ўмова паўтору.
    
    
    printf("Program terminated.\n");                               //канчатковае паведамленне.
    return 0;                                                      //выхад з праграмы.
}
