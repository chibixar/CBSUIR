//2 arrays of structs. After the analysis realloc the 2-nd array once.
#include <stdio.h>
#include <string.h>
#include "header.h"
#include <stdlib.h>
int main()
{
    int number_of_children;
    char target_illness[MAX_ALLOWED];                                                                                    // Радок для захавання назвы мэтавай хваробы.
    int result_count = 0;                                                                                                // Лічыльнік дзяцей з мэтавай хваробай.
    Child *children = NULL;                                                                                              // Указальнік на масіў усіх дзяцей.
    Child *children_with_target_illness = NULL;                                                                          // Указальнік на масіў адфільтраваных дзяцей.
   char filename[100];
    printf("Enter file name to read:\n");
    fgets(filename,100,stdin);
    filename[strcspn(filename,"\n")] = 0;
    read_children_from_file(filename, &children, &number_of_children);
    output_Child(children, number_of_children);
    printf("Enter file name to save table:\n");
    fgets(filename,100,stdin);
    filename[strcspn(filename,"\n")] = 0;
    write_children_to_file(filename, children, number_of_children);
    printf("Enter the target illness:\n");
    fgets(target_illness, MAX_ALLOWED, stdin);                                                                           // Счытванне назвы мэтавай хваробы.
    target_illness[strcspn(target_illness, "\n")] = '\0';                                                                // Выдаленне сімвала новага радка пасля fgets.
    children_analysis(children, number_of_children, &children_with_target_illness, &result_count, target_illness);       // Аналіз і фільтрацыя дзяцей па мэтавай хваробе.
    output_children_with_target_illness(children_with_target_illness, result_count);                                     // Вывад дзяцей з мэтавай хваробай.
    
    free(children);                                                                                                      // Вызваленне памяці першага масіву.
    free(children_with_target_illness);                                                                                  // Вызваленне памяці другога масіву.

    
}