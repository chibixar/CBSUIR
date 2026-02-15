#include <stdio.h>
#include <stdlib.h>
#include "header.h"

struct Cube
{
    int size;
    char color[10];
    char material[20];
};

void memory_allocation_Cubes(struct Cube **cubes,int number_of_cubes)
{
    *cubes = malloc(number_of_cubes * (sizeof(struct Cube)));
    if (*cubes == NULL) 
    {
        printf("Cubes memory allocation failed.");
        exit(1);
    }
}

color_input(char *color, int number_of_cubes, char allowed_colors[][MAX_COLOR_LENGTH])
{
    while (1)
    {
        scanf("%9s", color);
        fflush(stdin);
        for (int i = 0; i < number_of_cubes; i++)
        {
            if (strcmp(color, allowed_colors[i]) == 0)
                return;
        }

        printf("Invalid color. Try again: (Red Yellow Green Blue)");
    }
}

void input_Cubes (struct Cube *cubes, int *number_of_cubes, char allowed_colors[])
{
    printf("Enter number of cubes: ");
    GetInt(number_of_cubes);
    memory_allocation_Cubes(&cubes, *number_of_cubes);
    for (int i = 0; i < *number_of_cubes; i++)
    {
    char tempColor[15];
    printf("\nCube %d\n",i+1);
    
    printf("Size: (in cm) ");
    GetInt((&cubes[i].size));

    printf("Color: ");
    color_input(&cubes[i].color, *number_of_cubes, allowed_colors[][MAX_COLOR_LENGTH]);
    }
}


int main(void)
{
    int number_of_cubes;
    char allowed_colors[NUMBER_OF_ALLOWED_COLORS][MAX_COLOR_LENGTH] = {"Red", "Yellow", "Green", "Blue"};
    char allowed_materials[NUMBER_OF_ALLOWED_MATERIALS][MAX_MATERIAL_LENGTH] = {"Wood", "Metal", "Cardboard"};
    struct Cube *cubes;
    input_Cubes(cubes, &number_of_cubes);


    free(cubes);
    return 0;
}