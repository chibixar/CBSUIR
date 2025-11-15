#include <stdio.h>
#include "header.h"

void input2D(int arr2D[][N])
{
    char ch;
    for (int i = 0; i < M; i++)                                             //цыкл па слупках.
        for (int j = 0; j < N; j++)                                         //цыкл па радках.
        arr2D[i][j]=GetInt();                                               //выклік функцыя якая атрымлівае цэлае значэнне з клавіятуры з праверкай.
}                

void output(int arr2D[][N])
{
    putchar('\n');
    for (int i = 0; i < M; i++)                    //цыкл вываду слупкоў.
    {
        for(int j = 0; j < N; j++)                 //цыкл вываду радкоў.
        printf("%7d", arr2D[i][j]);
        putchar('\n');
    }
    
}

void BubbleSort(int arr2D[][N])                     //функцыя сартыроўкі масіву.
{
    int temp, swap;                                 //зменная часовага ўтрымання эл-ту масіву і зменная для праверкі перастаноўкі.
    for (int m = 0; m < M; m++)                     //цыкл па слупкам.
        for (int i = 0; i < N-1; i++)               //цыкл сартыроўкі па радках.
        {
            swap = 0;
            for(int j = 0; j < N-1-i; j++)          //цыкл сартыроўкі і-га радка .
            {
                if(arr2D[m][j]<arr2D[m][j+1])
                {
                    temp = arr2D[m][j];
                    arr2D[m][j] = arr2D[m][j+1];
                    arr2D[m][j+1] = temp;
                    swap = 1;                       //зменная для праверкі перастаноўкі.
                }
                
            }
            if(swap==0) break;                      //спыненне сартыроўкі радка, калі ён ўжо адсартаваны.
        }
}

int GetInt(void) {                                                  //функцыя уводу цэлага значэння з праверкай.
    int value;                                                      //зменная для вяртання.
    while (1) {                                                     //бясконцы цыкл.

        if (scanf("%d", &value) == 1) {                             //калі гэта цэлы лік.
            rewind(stdin);                                          //чысціць буфер уводу.
            return value;                                           //вяртае знач. з клавіятуры.
        } else {
            printf("Invalid input. Please enter an integer.\n");
            rewind(stdin);                                          //чысціць буфер уводу.
        }
    }
}