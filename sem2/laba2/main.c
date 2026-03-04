
//2 arrays of structs. After the analysis realloc the 2-nd array once.
#include <stdio.h>
#include "header.h"
int main()
{
    int number_of_children;
    char target_illness[MAX_ALLOWED];
    int result_count = 0;
    Child *children;
    Child *children_with_target_illness;
    input_Child(&children, &number_of_children);
    output_Child(children, number_of_children);
    printf("Enter the target illness:\n");
    fgets(target_illness, MAX_ALLOWED, stdin);
    children_analysis(children, number_of_children, &children_with_target_illness, &result_count, target_illness);
    output_children_with_target_illness(children_with_target_illness, result_count);
    
    // free(children);
    // free(children_with_target_illness);

    
}