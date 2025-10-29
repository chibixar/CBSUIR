#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#define ROWS 100
#define COLS 100
#define ASCII 49
#define TEN 10
#define TWELVE 12

// int algorithm(int matr[ROWS][COLS], int i, int j, int arows, int acols);
int alg(int matr[ROWS][COLS], int arows, int acols);


int main()
{
    srand(time(NULL));
    
    int rn; // random number
    int matr[ROWS][COLS];
    int i; // "i" is for rows
    int j; // "j" is for columns
    int arows = TEN; //actual rows 
    int acols = TWELVE; //actual columns 
    int v;

    printf("matrix was automatically set to 10x12 size\n");

    printf("Fill the matrix with random elements?\n");
    printf("enter 1 for YES\n");

    while(1)
    {
        v = getch();

    if(v == ASCII)
    {
        for(i = 0; i < arows; i++)
    {
    for(j = 0; j < acols; j++)
    {
    printf("element %d %d\n", i, j);
    rn = -TEN + rand() % TWELVE; // rn from -10 to 12
    matr[i][j] = rn;
    printf("%d\n", rn);
    }
    }
    break;
    }
    else
    {
        printf("you actually have no choice\n");
    }
    }

    // int algorithm(int matr[ROWS][COLS], int i, int j, int arows, int acols);
    // {
    //   int mxrow = matr[i][0]; 
    //   int mxcol = 1; // max in col
    //   int mnrow = matr[i][0];
    //   int mncol = 1; // min in col
      
    //   for (int i = 0; i < arows; i++)
    //   {
    //     // Находим минимальный и максимальный элементы в строке i
        
    //     for (int j = 1; j < acols; j++)
    //     {
    //         if (matr[i][j] < mnrow)
    //         {
    //             mnrow = matr[i][j];
    //         }
    //         if (matr[i][j] > mxrow)
    //         {
    //             mxrow = matr[i][j];
    //         }
    //     }
        
    //     for (int j = 0; j < acols; j++)
    //     {
    //         // Проверяем, является ли элемент минимальным в строке
    //         if (matr[i][j] == mnrow)
    //         {
    //             // Проверяем, является ли он максимальным в столбце
    //             for (int k = 0; k < arows; k++)
    //             {
    //                 if (matr[k][j] > matr[i][j])
    //                 {
    //                     mxcol = 0;
    //                     break;
    //                 }
    //             }
    //             if (mxcol)
    //             {
    //                 printf("element %d is min in row %d, max in column %d\n",matr[i][j], i, j);
    //             }
    //         }
            
    //         // Проверяем, является ли элемент максимальным в строке
    //         if (matr[i][j] == mxrow)
    //         {
    //             // Проверяем, является ли он минимальным в столбце
    //             for (int k = 0; k < arows; k++)
    //             {
    //                 if (matr[k][j] < matr[i][j])
    //                 {
    //                     mncol = 0;
    //                     break;
    //                 }
    //             }
    //             if (mncol)
    //             {
    //                 printf("element %d is min in row %d, max in column %d\n",matr[i][j], i, j);
    //             }
    //         }
    //     }
    // }
    // }



    //vivod
    printf("\nyour matrix\n");

        for (i = 0; i < arows; i++)
        {
            for (j = 0; j < acols; j++)
            {
                printf("%d\t", matr[i][j]); // "\t" is for horizontal tab
            }                              // used instead of spacebar
            printf("\n");
        }
   
        alg (matr, arows, acols);


    






    


return 0;
}
int alg (int matr[ROWS][COLS], int arows, int acols)
    {
        int SaddleCount = 0;
        int rowMin[arows];
        int rowMax[arows];
        int colMin[acols];
        int colMax[acols];
        for (int i = 0; i < arows; i++)
        {
        rowMin[i] = matr[i][0];
        rowMax[i] = matr[i][0];
            for (int j = 1; j < acols; j++)
            {
                if (matr[i][j] < rowMin[i])
                    rowMin[i] = matr[i][j];
                if (matr[i][j] > rowMax[i])
                    rowMax[i] = matr[i][j];
            }
        }
        for (int j = 0; j < acols; j++)
        {
        colMin[j] = matr[0][j];
        colMax[j] = matr[0][j];
            for (int i = 1; i < arows; i++)
            {
                if (matr[i][j] < colMin[j])
                    colMin[j] = matr[i][j];
                if (matr[i][j] > colMax[j])
                    colMax[j] = matr[i][j];
            }
    }
        
        for (int i = 0; i < arows; i++)
            for (int j = 0; j < acols; j++)
            {
                if ((matr[i][j] == colMax[j] && matr[i][j] == rowMin[i]) || (matr[i][j] == colMin[j] && matr[i][j] == rowMax[i]))
                {
                    SaddleCount++;
                    printf("%2d Saddle point is on the %d row and %d column. It's value is %d\n",SaddleCount, i+1, j+1, matr[i][j]);
                }
                
            }
         if (SaddleCount == 0)
        printf("No saddle points found in this matrix.\n");   
        
        
                
            
            
        
        
    }
