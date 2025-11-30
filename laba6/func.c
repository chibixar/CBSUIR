#include <stdio.h>                                                  
#include <stdlib.h>                                                 
#include "header.h"                                                 
#include <string.h>  

int GetInt(void) {                                                  //функцыя бяспечнага ўводу цэлага ліку.
    int value;                                                      
    char ch;                                                        

        if (scanf("%d", &value) == 1) {                             //калі ўведзены карэктны лік.
            rewind(stdin);                                          //ачышчаем буфер уводу.
            return value;                                           //вяртаем лік.
        } else {                                                    //калі ўведзена не лікавое значэнне.
            printf("Invalid input. Please enter an integer.\n");    
            rewind(stdin);                                          //ачышчаем буфер уводу.
            return GetInt();
        }
     
}



char** text_memory_allocate(char** text, int number_of_strings, int max_string_size)         
{                                                                   
    text = (char**)malloc(number_of_strings*sizeof(char*));               //выдзяляем памяць пад радок.
    if (text == NULL)                                             //праверка паспяховасці выдзялення.
    {
        printf("Memory allocation failed");                         
        exit(1);                                                    //завяршэнне пры памылцы.
    }  
    for (int i = 0; i < number_of_strings; i++)
    {
         *(text + i) = (int*)malloc(max_string_size * sizeof(char));            // выдзяляем памяць пад элементы кожнага радка.
        if (*(text + i) == NULL)                                  // правяраем, ці атрымалася выдзеліць памяць для радка.
        {
            printf("Memory allocation failed.");                   
            for (int k = 0; k < i; k++)                            
                free(*(text + k));                                // вызваляем кожны папярэдні радок.
            free(text);                                           // вызваляем масіў указальнікаў.
            return NULL;                                           // вяртаем NULL, калі ўзнікла памылка.
        }
    }
    return text;
                    
}

int* digital_sum_memory_allocation(int *digital_sum, int number_of_strings)
{
    digital_sum = (int*)calloc(number_of_strings, sizeof(int));
    if (digital_sum == NULL) 
    {
        printf("Memory allocation failed");                         
        exit(1);                                                    //завяршэнне пры памылцы.
    }  
}


char** text_input(char** text, int number_of_strings, int max_string_size)                   
{
    for (int i = 0; i < number_of_strings; i++)
    {
       fgets(*(text+i), max_string_size, stdin);                //чытанне радка з клавіятуры.
        
    // size_t len = strlen(text[i]);                                    //выдаляем \n з канца каб не ламаць логіку калі апошняе слова з лічбаў.                      //!IDK
    // if (len > 0 && text[i][len-1]=='\n')
    //     text[i][len-1]='\0';
    
    
}
return text;                                             //вяртаем уведзены радок. 

    
}

void output_text(char** text, int number_of_strings)
{
    for (int i = 0; i < number_of_strings; i++)
        puts(*(text+i));
}

text_sort_by_name(char** text, int number_of_strings, int max_string_size)
{

}

int compare_first_letter(const char* a, const char* b)
{
    while (*a == ' ') a++;
    while (*b == ' ') b++;
    return (unsigned char)*a - (unsigned char)*b;
}

void swap_str(char** a, char** b) {
    char* temp = *a;
    *a = *b;
    *b = temp;
}

int partition_name(char** text, int low, int high) {
    char *p = *(text+low);  
    int i = low;
    int j = high;

    while (i < j) {

        while (compare_first_letter(*(text+i), p) <= 0 && i <= high - 1) {
            i++;
        }

        while (compare_first_letter(*(text+j), p) > 0 && j >= low + 1) {
            j--;
        }

        if (i < j) {
            swap_str(*(text+i), *(text+j));
        }
    }

    swap_str(*(text+low), *(text+j));
    return j;
}

void Quick_Sort_Alphabetically(char** text, int low, int high) {
    if (low < high) {
        int pi = partition_name(text, low, high);
        Quick_Sort_Alphabetically(text, low, pi - 1);
        Quick_Sort_Alphabetically(text, pi + 1, high);
    }
}







int char_isdigit(char** text, int i, int j)                               
{
    if (*(*(text+i)+j) >= LOWEST_ASCII_DIGIT && text[i] <= HIGHEST_ASCII_DIGIT)
    return 1; else return 0;                                        //праверка, ці з'яўляецца сімвал лічбай.
}

digital_sum_calculation(int* digital_sum, int i, int j, int len)
{
    
}

void salary_find(char** text, int* digital_sum, int number_of_strings, int max_string_size)
{
    for (int i = 0; i < number_of_strings; i++)
    {
        int j = 0, len = 0;
        while(*(*(text+i)+j) != ' ' || !char_isdigit(text, i, j+1)) j++;
        j++; len++;
        while(*(*(text+i)+j+1) != ' ' && *(*(text+i)+j+1) != '\n' && *(*(text+i)+j+1) != '\0') 
        {
            len++;
            j++;
        }

    }
    
}

int compare_salary(const int* a, const int* b)
{
    while (*a == ' ') a++;
    while (*b == ' ') b++;
    return (int)*a - (int)*b;
}

int partition_salary(char** text, int* digital_sum, int low, int high) {
    char *p = *(digital_sum+low);  
    int i = low;
    int j = high;

    while (i < j) {

        while (compare_salary(*(digital_sum+i), p) <= 0 && i <= high - 1) {
            i++;
        }

        while (compare_salary(*(digital_sum+j), p) > 0 && j >= low + 1) {
            j--;
        }

        if (i < j) {
            swap_str(*(text+i), *(text+j));
        }
    }

    swap_str(*(text+low), *(text+j));
    return j;
}

void Quick_Sort_Alphabetically(char** text, int* digital_sum, int low, int high) {
    if (low < high) {
        int pi = partition_salary(text, digital_sum, low, high);
        Quick_Sort_Alphabetically(text, low, pi - 1);
        Quick_Sort_Alphabetically(text, pi + 1, high);
    }
}


















// text_sort_by_salary(char** text, int number_of_strings, int max_string_size, int digital_sum)
// {

// }

// void text_digit_word(char** text, int* sum)    
// {
//     int i = 0, j = 0;                                               
//     while(text[i] == ' ') i++;                                    //прапускаем пачатковыя прабелы.

//     while (text[i] != '\0')                                       //пакуль не канец радка.
//     {
//         int k = i;
//         while(text[k] != '\0' && text[k] != ' ') k++;
//         int len = k-i;
//         if(word_isdigit(text, sum, i))                            //калі слова складаецца з лічбаў.
//             i = k;                                                  //пераскокваем гэта слова.
//         else 
//         {
//             for (int t = 0; t< len; ++t)
//                 text[j++]=text[i+t];
//             i=k;
//             while (text[i]==' ') i++;                             //пропуск прабелаў паміж словамі.
//             if (text[i]!='\0')
//                 text[j++] = ' ';
            
            
//         }
                                    
//     }
//     text[j]='\0';                                                 //ставім канец радка.

//     if (j>0) strcat(text, " ");                                   //дадаем прабел перад сумай.

//     char buf[32];                                                   
//     sprintf(buf, "%d", *sum);                                       //пераўтвараем суму ў радок.
//     strcat(text, buf);                                            //дапаўняем радок сумай.
// }

// int word_isdigit(char** text, int* sum, int i)   
// {
//     int k = i;                                                      
//     int temp_sum = 0;                                                                                             

//     if (text[i] == ' ' || text[i] == '\0')                      //калі пустоца або канец радка.
//         return 0;                                                   

//     for (; text[k] != '\0' && text[k] != ' '; k++)              //пакуль не канец слова.
//     {
//         if (!char_isdigit(text, k))                               //калі хоць адзін сімвал не лічба.
//             return 0;                                               
//         temp_sum += (text[k] - '0');                              //дадаём лічбу да сумы. НЕ АСКІ
                
//     }
                                                   

//     *sum += temp_sum;                                               //дадаём у агульную суму.
//     return 1;                                                       //слова складаецца з лічбаў.
// }

