#include <stdio.h>
#include "header.h"

int main(void)
{
    char choice;                                            // каб захоўваць y/n адказ
    int arr2D[M][N];
    do {
        printf("Enter a 2D array of %d numbers:\n", M * N);
        input2D(arr2D);                                     //выклік функцыі ўводу
        BubbleSort(arr2D);                                  //выклік функцыі сартавання
        output(arr2D);                                      //выклік функцыі ўводу

        printf("\nDo you want to run again? (y/n): ");      // спытаць карыстальніка ці трэба працягнуць   
        while ((choice = getchar()) == '\n');               // прапускаць сімвалы новай стракі

    } while (choice == 'y' || choice == 'Y');

    printf("Program terminated.\n");
    return 0;
}
