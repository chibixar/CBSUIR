#include <stdio.h> 
#include <stdlib.h>                  
int GetInt(void);
int* MemoryAllocation(int *arr, int elements);
void input(int *arr, int elements);                      //прататып функцыі уводу
void output(int *arr, int elements);                     //прататып функцыі вываду
void sort(int *arr, int elements);                       //прататып функцыі сартыроўкі метадам бурбалкі



int main(void)                              
{
    int elements;
    char choice;
    int *arr;                                         //дэкларацыя указальніка.
    do
    {
    arr = NULL;
    printf("Enter the number of elements:\n");
    elements = GetInt();;                             //дэкларацыя зменнай для колькасці элементаў масіву і атрыманне значэння з клавіятуры.
    arr = MemoryAllocation(arr, elements);
    if (arr == NULL)
        return 1;
    input(arr, elements);                             //выклік функцыі ўводу
    sort(arr, elements);                              //выклік функцыі сартыроўкі
    output(arr, elements);                            //выклік функцыі вываду
    free(arr);
    printf("\nDo you want to run again? (y/n): ");
        while((choice = getchar()) == '\n');
    } while (choice == 'y' || choice == 'Y');
printf("Programm terminated.");
return 0;
}

int* MemoryAllocation(int *arr, int elements)
{
    arr = (int*)calloc(elements, sizeof(int));
    if (arr == NULL)
    {
        printf("Memory allocation failed.");
        return NULL;
    }
    
}

void input(int *arr, int elements)                       //вызначэнне функцыі ўводу
{
    printf("Enter an array:\n");
    for(int i=0; i<elements; i++)                  
    {
        
        *(arr + i) = GetInt();
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

void output(int *arr, int elements)                      //вызначэнне функцыі вываду значэння адстартаванага масіву
{
    printf("Sorted array:\n {");
    for (int i = 0; i < elements; i++)
    {
        printf("%7d", *(arr+i));
    }
    printf("}");
}

void sort(int *arr, int elements)                        //вызначэнне функцыі сартыроўкі масіву
{
    int swap;                               //дэкларацыя зменнай для спынення цыклу, калі масіў ужо адсартаваны
    int temp;                               //дэкларацыя зменнай для перастаноўкі значэнняў элементаў масіву
    for (int i = 0; i < elements-1; i++)           //цыкл для сартыроўкі масіву
    {
        swap=0;                             //значэнне зменнай для спынення цыклу
        for (int j = 0; j < elements-i-1; j++)     //цыкл для перастаноўкі элементаў масіву
        {
            if(*(arr+j)>*(arr+j+1))             //перастаноўка элементаў масіву
            {
                temp=*(arr+j);                
                *(arr+j)=*(arr+j+1);            
                *(arr+j+1)=temp;              
                swap=1;
            }
        }
        if (swap==0)                        //спыненне сартыроўкі
        {
            break;
        }
        
        
    }
    
}



       
           