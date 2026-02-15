#include <stdio.h>                                                  
#include <stdlib.h>                                                 
#include "header.h"                                                 
#include <string.h>                                                 

int GetInt(void) {                                                  //функцыя бяспечнага ўводу цэлага ліку.
    int value;                                                      
    char ch;                                                        

    while (1) {                                                     //бясконцы цыкл.
        if (scanf("%d", &value) == 1) {                             //калі ўведзены карэктны лік.
            linux_rewind();                                          //ачышчаем буфер уводу.
            return value;                                           //вяртаем лік.
        } else {                                                    //калі ўведзена не лікавое значэнне.
            printf("Invalid input. Please enter an integer.\n");    
            linux_rewind();                                          //ачышчаем буфер уводу.
        }
    }
}


char* string_memory_allocate(char* string, int string_size)         
{                                                                   
    string = (char*)malloc(string_size*sizeof(char));               //выдзяляем памяць пад радок.
    if (string == NULL)                                             //праверка паспяховасці выдзялення.
    {
        printf("Memory allocation failed");                         
        exit(1);                                                    //завяршэнне пры памылцы.
    }
    return string;                                                  //вяртаем адрас радка.
}


char* string_input(char* string, int string_size)                   
{
    if (fgets(string, string_size, stdin) == NULL)                  //чытанне радка з клавіятуры.
    {
        printf("Input erorr");                                      
        exit(1);                                                    //завяршэнне пры памылцы.
    }
    size_t len = strlen(string);                                    //выдаляем \n з канца каб не ламаць логіку калі апошняе слова з лічбаў.
    if (len > 0 && string[len-1]=='\n')
        string[len-1]='\0';
    
    
    return string;                                                  //вяртаем уведзены радок.
}


void string_digit_word(char* string, int* sum)    
{
    int i = 0, j = 0;                                               
    while(string[i] == ' ') i++;                                    //прапускаем пачатковыя прабелы.

    while (string[i] != '\0')                                       //пакуль не канец радка.
    {
        int k = i;
        while(string[k] != '\0' && string[k] != ' ') k++;
        int len = k-i;
        if(word_isdigit(string, sum, i))                            //калі слова складаецца з лічбаў.
            i = k;                                                  //пераскокваем гэта слова.
        else 
        {
            for (int t = 0; t< len; ++t)
                string[j++]=string[i+t];
            i=k;
            while (string[i]==' ') i++;                             //пропуск прабелаў паміж словамі.
            if (string[i]!='\0')
                string[j++] = ' ';
            
            
        }

    }
    string[j]='\0';                                                 //ставім канец радка.

    if (j>0) strcat(string, " ");                                   //дадаем прабел перад сумай.

    char buf[32];                                                   
    sprintf(buf, "%d", *sum);                                       //пераўтвараем суму ў радок.
    strcat(string, buf);                                            //дапаўняем радок сумай.
}

int word_isdigit(char* string, int* sum, int i)   
{
    int k = i;                                                      
    int temp_sum = 0;                                                                                             

    if (string[i] == ' ' || string[i] == '\0')                      //калі пустоца або канец радка.
        return 0;                                                   

    for (; string[k] != '\0' && string[k] != ' '; k++)              //пакуль не канец слова.
    {
        if (!char_isdigit(string, k))                               //калі хоць адзін сімвал не лічба.
            return 0;                                               
        temp_sum += (string[k] - '0');                              //дадаём лічбу да сумы.
                
    }
                                                   

    *sum += temp_sum;                                               //дадаём у агульную суму.
    return 1;                                                       //слова складаецца з лічбаў.
}

int char_isdigit(char* string, int i)                               
{
    if (string[i] >= LOWEST_ASCII_DIGIT && string[i] <= HIGHEST_ASCII_DIGIT)
    return 1; else return 0;                                        //праверка, ці з'яўляецца сімвал лічбай.
}

//c >= 48 && c <= 57                                                //ASCII дыяпазон лічбаў.




















void linux_rewind()
{
    int c;
    while (c=(getchar())!= '\n' && c != EOF);
}