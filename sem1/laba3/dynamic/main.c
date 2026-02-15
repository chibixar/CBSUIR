#include <stdio.h>
#include "header.h"

int main(void)
{
    char choice;                                                         // каб захоўваць y/n адказ.
    int rows, cols;
    int **arr2D;
    do {
        arr2D = NULL;
        printf("Enter the number of rows: ");
        rows = GetInt();
        printf("Enter the number of columns: ");
        cols = GetInt();
        arr2D = MemoryAllocation(arr2D, rows, cols); 
        if (arr2D == NULL)
            return 1;
        printf("Enter a 2D array of %d numbers:\n", rows*cols);
        input2D(arr2D, rows, cols);                                     //выклік функцыі ўводу.
        BubbleSort(arr2D, rows, cols);                                  //выклік функцыі сартавання.
        printf("Sorted array:");
        output(arr2D, rows, cols);                                      //выклік функцыі ўводу.
        MemoryFree(arr2D, rows);
        printf("\nDo you want to run again? (y/n): ");                  // спытаць карыстальніка ці трэба працягнуць.
        while ((choice = getchar()) == '\n');                           // прапускаць сімвалы новай стракі.

    } while (choice == 'y' || choice == 'Y');
 
    printf("Program terminated.\n");
    return 0;
}
