#include <stdio.h>
#include "header.h"

void input2D(int arr2D[][N])
{
    char ch;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        while(scanf_s("%d", &arr2D[i][j]) != 1)
        {
            printf("Invalid input. Please enter an integer: ");
            while ((ch = getchar()) != '\n' && ch != EOF && ch != ' ');     //prvents infinite loop ak clearls Input Buffer 
        }
}

void output(int arr2D[][N])
{
    for (int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        printf("%d ", arr2D[i][j]);
        putchar('\n');
    }
    
}

void input(int arr[])
{
    for (int i = 0; i < N; i++)
    {
        scanf("%d",&arr[i]);
    }
    
}

void change(int arr[], int arr2D[][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int a = (i + j)%N;          //паніжае а калі яно больш за N
            // if(a > N-1) do
            // a = a - N;
            // while (a > N);
            arr2D[i][j]=arr[a];
        }
    }   
    
}