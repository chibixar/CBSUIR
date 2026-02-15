#include <stdio.h>
#include "header.h"
void GetInt(int *value) {                                                  //функцыя бяспечнага ўводу цэлага ліку.                                                      
    char ch;  
    while(1)
    {                                                      
        if (scanf("%d", value) == 1) {                             //калі ўведзены карэктны лік.
            fflush(stdin);
            return;
        } else {                                                    //калі ўведзена не лікавое значэнне.
            printf("Invalid input. Please enter an integer.\n");
            fflush(stdin);
        }
    }
}

void rewind_linux(void)
{
    int c;
    while((c=getchar()) != '\n' && c != EOF);
}