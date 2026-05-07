#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

int main()
{
    int number_of_children = 0;
    char target_illness[MAX_ALLOWED];
    int result_count = 0;
    Child *children = NULL;
    Child *children_with_target_illness = NULL;
    choose_input(&children, &number_of_children);
    output_Child(children, number_of_children);
    choose_output(children, number_of_children);
    printf("Enter the target illness: ");
    read_line(target_illness, MAX_ALLOWED, stdin);
    children_analysis(children, number_of_children,
                      &children_with_target_illness, &result_count,
                      target_illness);
    if (!result_count)
    {
        printf("No children found with illness '%s'.\n", target_illness);
        free(children);
        return 0;
    }
    output_Child(children_with_target_illness, result_count);
    choose_output(children_with_target_illness, result_count);
    free(children);
    free(children_with_target_illness);
    return 0;
}