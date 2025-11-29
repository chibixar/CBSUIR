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
            GetInt();
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
                    
}


char** text_input(char** text, int number_of_strings, int max_string_size)                   
{
    for (int i = 0; i < number_of_strings; i++)
    {
       if (fgets(*(text+i), max_string_size, stdin) == NULL)                  //чытанне радка з клавіятуры.
        {
        printf("Input erorr");                                      
        exit(1);                                                    //завяршэнне пры памылцы.
        }
    size_t len = strlen(text);                                    //выдаляем \n з канца каб не ламаць логіку калі апошняе слова з лічбаў.                      //!IDK
    if (len > 0 && text[len-1]=='\n')
        text[len-1]='\0';
    
    
    return text;                                             //вяртаем уведзены радок. 
    }
    
    
}

text_sort_by_name(char** text, int number_of_strings, int max_string_size)
{

}

int compare_first_letter(char** a, char** b)     
{
    int i = 0, j = 0;
    while (a[i] == ' ') i++;
    while (b[j] == ' ') j++;
    char first_a = a[i];
    char first_b = b[j];
    if (b<a) return 1;
    else return 0;
}

void swap_str(char** a, char** b) {
    char* temp = *a;
    *a = *b;
    *b = temp;
}

int partition(char** text, int low, int high) {
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

    swap_str(*(text+i), *(text+j));
    return j;
}

void Quick_Sort_Alphabetically(char** text, int low, int high) {
    if (low < high) {
        int pi = partition(text, low, high);
        Quick_Sort_Alphabetically(text, low, pi - 1);
        Quick_Sort_Alphabeticallyt(text, pi + 1, high);
    }
}













text_sort_by_salary(char** text, int number_of_strings, int max_string_size, int digital_sum)
{

}

void text_digit_word(char* text, int* sum)    
{
    int i = 0, j = 0;                                               
    while(text[i] == ' ') i++;                                    //прапускаем пачатковыя прабелы.

    while (text[i] != '\0')                                       //пакуль не канец радка.
    {
        int k = i;
        while(text[k] != '\0' && text[k] != ' ') k++;
        int len = k-i;
        if(word_isdigit(text, sum, i))                            //калі слова складаецца з лічбаў.
            i = k;                                                  //пераскокваем гэта слова.
        else 
        {
            for (int t = 0; t< len; ++t)
                text[j++]=text[i+t];
            i=k;
            while (text[i]==' ') i++;                             //пропуск прабелаў паміж словамі.
            if (text[i]!='\0')
                text[j++] = ' ';
            
            
        }
                                    
    }
    text[j]='\0';                                                 //ставім канец радка.

    if (j>0) strcat(text, " ");                                   //дадаем прабел перад сумай.

    char buf[32];                                                   
    sprintf(buf, "%d", *sum);                                       //пераўтвараем суму ў радок.
    strcat(text, buf);                                            //дапаўняем радок сумай.
}

int word_isdigit(char* text, int* sum, int i)   
{
    int k = i;                                                      
    int temp_sum = 0;                                                                                             

    if (text[i] == ' ' || text[i] == '\0')                      //калі пустоца або канец радка.
        return 0;                                                   

    for (; text[k] != '\0' && text[k] != ' '; k++)              //пакуль не канец слова.
    {
        if (!char_isdigit(text, k))                               //калі хоць адзін сімвал не лічба.
            return 0;                                               
        temp_sum += (text[k] - '0');                              //дадаём лічбу да сумы. НЕ АСКІ
                
    }
                                                   

    *sum += temp_sum;                                               //дадаём у агульную суму.
    return 1;                                                       //слова складаецца з лічбаў.
}

int char_isdigit(char* text, int i)                               
{
    if (text[i] >= LOWEST_ASCII_DIGIT && text[i] <= HIGHEST_ASCII_DIGIT)
    return 1; else return 0;                                        //праверка, ці з'яўляецца сімвал лічбай.
}

void QuickSort(int l, int r, char** text)
{
    int w, x, i, j;
    i=l;
    j=r;
    x=text[(l+r)/2];
    while (i<=j)
    {
        while (text[i]<x) i++;
        while(x<text[j]) j--;
        if (i<=j)
        {
            w=text[i]; text[i]=text[j]; text[j]=w;
            i++; j--;
        }
        if(l<j) QuickSort(l,j,a);
        if(i<r) QuickSort(i,r,a);
        
    }
    
}