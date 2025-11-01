#ifndef HEADER_H
#define HEADER_H

int** MemoryAllocation(int **arr2D, int rows, int cols);        //прататып функцыі выдзялення памяці пад двухмерны масіў.
void input2D(int **arr2D, int rows, int cols);                  //прататып функцыі ўводу масіву.
int GetInt(void);                                               //прататып функцыі ўводу цэлага ліку.
void BubbleSort(int **arr2D, int rows, int cols);               //прататып функцыі сартыроўкі метадам бурбалкі.
void output(int **arr2D, int rows, int cols);                   //прататып функцыі вываду.
void MemoryFree(int **arr2D, int rows);
    

#endif