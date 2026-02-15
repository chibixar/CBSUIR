//У двумерным масіве сярод лікаў, якія стаяць на цотных месцах, вызначыць мінімальны дадатны эл-т мас. і яго індэксы.
//

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main()
{
    int rows, cols, result;
    int **arr;
    printf("Enter a number of rows:\n");
    result = scanf("%d", &rows);   
    if (result != 1)
    {
        printf("\nWrong input type. Programm terminated.");
    }
    printf("Enter a number of columns:\n");
    result = scanf("%d", &cols);                
    if (result != 1)
    {
        printf("\nWrong input type. Programm terminated.");
    }         
    arr = (int **)malloc(rows * sizeof(int *));           //
    if (arr == NULL){                                        //
        printf("\nMemory allocation Failed");
        return 1;
    }
    for (int i = 0; i < rows; i++)
    {
        arr[i] = (int *)malloc(cols * sizeof(int));
        if (arr[i] == NULL){                                    //
        printf("\nMemory allocation Failed");
        return 1;
        }        
    }
    
    printf("Input your array (fill in column by column):\n");
    input(rows, cols, arr);
    alg(rows, cols, arr);
    output(rows, cols, arr);




    for (int i = 0; i < rows; i++)
        free(arr[i]);
    free(arr);
    return 0;
}

void input(int rows, int cols, int **arr)
{
    for(int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            scanf("%7d", &arr[i][j]);
        }
        
}

void output(int rows, int cols, int **arr)
{
    putchar('\n');
    for (int i = 0; i < rows; i++)                    //цыкл вываду слупкоў
    {
        for(int j = 0; j < cols; j++)                 //цыкл вываду радкоў
        printf("%7d", arr[i][j]);
        putchar('\n');
    }
}

int alg (int rows, int cols, int **arr)
    {
        int SaddleCount = 0;
        int rowMin[rows];
        int rowMax[rows];
        int colMin[cols];
        int colMax[cols];
        for (int i = 0; i < rows; i++)
        {
        rowMin[i] = arr[i][0];
        rowMax[i] = arr[i][0];
            for (int j = 1; j < cols; j++)
            {
                if  (arr[i][j] < rowMin[i])
                    rowMin[i] = arr[i][j];
                if  (arr[i][j] > rowMax[i])
                    rowMax[i] = arr[i][j];
            }
        }
        for (int j = 0; j < cols; j++)
        {
        colMin[j] = arr[0][j];
        colMax[j] = arr[0][j];
            for (int i = 1; i < rows; i++)
            {
                if  (arr[i][j] < colMin[j])
                    colMin[j] = arr[i][j];
                if  (arr[i][j] > colMax[j])
                    colMax[j] = arr[i][j];
            }
    }
        
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
            {
                if (( arr[i][j] == colMax[j] && arr[i][j] == rowMin[i]) || (arr[i][j] == colMin[j] && arr[i][j] == rowMax[i]))
                {
                    SaddleCount++;
                    printf("%2d Saddle point is on the %d row and %d column. It's value is %d\n",SaddleCount, i+1, j+1, arr[i][j]);
                }
                
            }
         if (SaddleCount == 0)
        printf("No saddle points found in this matrix.\n");   
        
        
                
            
            
        
        
    }
