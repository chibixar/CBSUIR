#include <stdio.h>                   
#define N 10                                //заданне памеру масіву
void input(int arr[]);                      //прататып функцыі уводу
void output(int arr[]);                     //прататып функцыі вываду
void sort(int arr[]);                       //прататып функцыі сартыроўкі метадам бурбалкі



int main(void)                              
{
    int arr[N];                             //дэкларацыя масіву
    input(arr);                             //выклік функцыі ўводу
    sort(arr);                              //выклік функцыі сартыроўкі
    output(arr);                            //выклік функцыі вываду





return 0;
}

void input(int arr[])                       //вызначэнне функцыі ўводу
{
    printf("Enter an array: ");
    for(int i=0; i<N; i++)                  
    {
        
        scanf("%d", &arr[i]);
    }
}


void output(int arr[])                      //вызначэнне функцыі вываду значэння адстартаванага масіву
{
    printf("Sorted array:\n {");
    for (int i = 0; i < N; i++)
    {
        printf("%d  ",arr[i]);
    }
    printf("}");
}

void sort(int arr[])                        //вызначэнне функцыі сартыроўкі масіву
{
    int swap;                               //дэкларацыя зменнай для спынення цыклу, калі масіў ужо адсартаваны
    int temp;                               //дэкларацыя зменнай для перастаноўкі значэнняў элементаў масіву
    for (int i = 0; i < N-1; i++)           //цыкл для сартыроўкі масіву
    {
        swap=0;                             //значэнне зменнай для спынення цыклу
        for (int j = 0; j < N-i-1; j++)     //цыкл для перастаноўкі элементаў масіву
        {
            if(arr[j]>arr[j+1])             //перастаноўка элементаў масіву
            {
                temp=arr[j];                
                arr[j]=arr[j+1];            
                arr[j+1]=temp;              
                swap=1;
            }
        }
        if (swap==0)                        //спыненне сартыроўкі
        {
            break;
        }
        
        
    }
    
}



       
           