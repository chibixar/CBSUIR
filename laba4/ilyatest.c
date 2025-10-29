#include <stdio.h>
int main()
{
    int arows = 3;
    int acols = 3;
    int matr[3][3] = {
    {3, 7, 3},
    {1, 2, 1},
    {1, 5, 0}
};

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