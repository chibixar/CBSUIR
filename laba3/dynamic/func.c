#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int** MemoryAllocation(int **arr2D, int rows, int cols)
{
    arr2D = (int**)calloc(rows, sizeof(int*));
    if (arr2D == NULL)
    {
        printf("Memory allocation failed.");
        return NULL;
    }
    for (int i = 0; i < rows; i++)
    {
        *(arr2D+i) = (int*)calloc(cols, sizeof(int));
        if (*(arr2D+i)==NULL)
    {
        printf("Memory allocation failed.");
        for (int k = 0; k < i; k++) free(*(arr2D + k));
            free(arr2D);
        return NULL;
    }
    
    }
    return arr2D;
    
}

void input2D(int **arr2D, int rows, int cols)
{
    char ch;
    for (int i = 0; i < rows; i++)                                             //цыкл па слупках.
        for (int j = 0; j < cols; j++)                                         //цыкл па радках.
        *(*(arr2D+i)+j)=GetInt();                                                 //правярае увод і атрымлівае цэлае зн.
}

void output(int **arr2D, int rows, int cols)
{
    putchar('\n');
    for (int i = 0; i < rows; i++)                    //цыкл вываду слупкоў.
    {
        for(int j = 0; j < cols; j++)                 //цыкл вываду радкоў.
        printf("%7d", *(*(arr2D+i)+j));
        putchar('\n');
    }
    
}

void BubbleSort(int **arr2D, int rows, int cols)                     //функцыя сартыроўкі масіву.
{
    int temp, swap;                                 //зменная часовага ўтрымання эл-ту масіву і зменная для праверкі перастаноўкі.
    for (int m = 0; m < rows; m++)                     //цыкл па слупкам.
        for (int i = 0; i < cols-1; i++)               //цыкл сартыроўкі па радках.
        {
            swap = 0;
            for(int j = 0; j < cols-1-i; j++)          //цыкл сартыроўкі і-га радка .
            {
                if(*(*(arr2D+m)+j)<*(*(arr2D+m)+j+1))
                {
                    temp = *(*(arr2D+m)+j);
                    *(*(arr2D+m)+j) = *(*(arr2D+m)+j+1);
                    *(*(arr2D+m)+j+1) = temp;
                    swap = 1;                       //зменная для праверкі перастаноўкі.
                }
                
            }
            if(swap==0) break;                      //спыненне сартыроўкі радка, калі ён ўжо адсартаваны.
        }
}

int GetInt(void) {
    int value;
    char ch;

    while (1) {                                                     //бясконнцы цыкл.

        if (scanf("%d", &value) == 1) {                             //калі гэта цэлы лік.
            while ((ch = getchar()) != '\n' && ch != EOF);          //чысціць буфер уводу.
            return value;                                           //вяртае знач. з клавіятуры.
        } else {
            printf("Invalid input. Please enter an integer.\n");
            
            while ((ch = getchar()) != '\n' && ch != EOF);          //чысціць буфер уводу.
        }
    }
}

void MemoryFree(int **arr2D, int rows)
{
    for (int i = 0; i < rows; i++)
        free(*(arr2D+i));
    free(arr2D);
}