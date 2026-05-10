//В массиве структур хранится информациия о детях детского сада. Элементом структуры является объединение, в котором зранится последнее заболевание рабёнка, имя участкового врача. Если ребенок находится в больнице, то и номер больницыы, её адрес и имя лечащего врача.
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
    char filename[MAX_FILENAME];
    choose_input(&children, &number_of_children);
    output_Child(children, number_of_children);
    get_output_file_name(filename);
    write_children_to_file(filename, children, number_of_children, "w");
    printf("Enter the target illness:\n");
    read_line(target_illness, MAX_ALLOWED, stdin);                                                                // Выдаленне сімвала новага радка пасля fgets.
    children_analysis(children, number_of_children, &children_with_target_illness, &result_count, target_illness);       // Аналіз і фільтрацыя дзяцей па мэтавай хваробе.
    if(!result_count) return 1;
    output_Child(children_with_target_illness, result_count);
    write_children_to_file(filename, children_with_target_illness, result_count, "a");

    
    free(children);                                                                                                      // Вызваленне памяці першага масіву.
    free(children_with_target_illness);                                                                                  // Вызваленне памяці другога масіву.

    
}