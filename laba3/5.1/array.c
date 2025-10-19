#include <stdio.h>
#include "header.h"


int main ()
{   
    int arr[N];
    int arr2D[N][N];
    printf("Enter an array of %d numbers:\n", N);
    input(arr);
    putchar('\n');
    change(arr, arr2D);
    output(arr2D);
    return 0;
    

}