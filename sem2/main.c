#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

struct Cube
{
    int size;
    char color[MAX_COLOR_LENGTH];
    char material[MAX_MATERIAL_LENGTH];
};

struct ColorAnalysis
{
    int count;
    int total_volume;
};
struct MaterialSizeAnalysis
{
    int wooden_count;
    int metal_count;
    int n;
    int m;
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

void color_input(char *color, char allowed_colors[][MAX_COLOR_LENGTH])
{
    while (1)
    {
        scanf("%9s", color);
        rewind_linux();
        for (int i = 0; i < NUMBER_OF_ALLOWED_COLORS; i++)
        {
            if (strcmp(color, allowed_colors[i]) == 0)
                return;
        }

        printf("\nInvalid color. Try again: (Red Yellow Green Blue)\n");
    }
}

void material_input(char *material, char allowed_materials[][MAX_MATERIAL_LENGTH])
{
    while (1)
    {
        scanf("%9s", material);
        rewind_linux();
        for (int i = 0; i < NUMBER_OF_ALLOWED_MATERIALS; i++)
        {
            if (strcmp(material, allowed_materials[i]) == 0)
                return;
        }

        printf("\nInvalid material. Try again: (Wood Metal Cardboard)\n");
    }
}

void input_Cubes (struct Cube **cubes, int *number_of_cubes, char allowed_colors[][MAX_COLOR_LENGTH], char allowed_materials[][MAX_MATERIAL_LENGTH])
{
    printf("Enter number of cubes: ");
    GetInt(number_of_cubes);
    memory_allocation_Cubes(cubes, *number_of_cubes);
    for (int i = 0; i < *number_of_cubes; i++)
    {
    printf("\nCube %d\n",i+1);
    
    printf("Size: (in cm) ");
    GetInt((&(*cubes)[i].size));

    printf("Color: ");
    color_input((*cubes)[i].color, allowed_colors);
    printf("Material: ");
    material_input((*cubes)[i].material, allowed_materials);
    }
}

void analyze_by_color(struct Cube *cubes, int number_of_cubes, char allowed_colors[][MAX_COLOR_LENGTH], struct ColorAnalysis *results)
{
    for (int i = 0; i < NUMBER_OF_ALLOWED_COLORS; i++)
    {
        results[i].count = 0;
        results[i].total_volume = 0;
        
        for (int j = 0; j < number_of_cubes; j++)
        {
            if (strcmp(cubes[j].color, allowed_colors[i]) == 0)
            {
                results[i].count++;
                results[i].total_volume += cubes[j].size * cubes[j].size * cubes[j].size;
            }
        }
    }
}

void output_color_analysis(char allowed_colors[][MAX_COLOR_LENGTH], struct ColorAnalysis *results)
{
    printf("\n=== Task a) Color Analysis ===\n");
    
    for (int i = 0; i < NUMBER_OF_ALLOWED_COLORS; i++)
    {
        if (results[i].count > 0)
        {
            printf("%s cubes: Count = %d, Total Volume = %d cm³\n", 
                   allowed_colors[i], results[i].count, results[i].total_volume);
        }
    }
}

void analyze_by_material_and_size(struct Cube *cubes, int number_of_cubes, 
                                  int n, int m,
                                  struct MaterialSizeAnalysis *result)
{
    result->wooden_count = 0;
    result->metal_count = 0;
    result->n = n;
    result->m = m;
    
    for (int i = 0; i < number_of_cubes; i++)
    {
        if (strcmp(cubes[i].material, "Wood") == 0 && cubes[i].size == n)
        {
            result->wooden_count++;
        }
        
        if (strcmp(cubes[i].material, "Metal") == 0 && cubes[i].size > m)
        {
            result->metal_count++;
        }
    }
}

void output_material_size_analysis(struct MaterialSizeAnalysis *result)
{
    printf("\n=== Task b) Material and Size Analysis ===\n");
    printf("Wooden cubes with edge = %d cm: %d\n", result->n, result->wooden_count);
    printf("Metal cubes with edge > %d cm: %d\n", result->m, result->metal_count);
}

int main(void)
{
    int number_of_cubes;
    int n, m;
    char allowed_colors[NUMBER_OF_ALLOWED_COLORS][MAX_COLOR_LENGTH] = {"Red", "Yellow", "Green", "Blue"};
    char allowed_materials[NUMBER_OF_ALLOWED_MATERIALS][MAX_MATERIAL_LENGTH] = {"Wood", "Metal", "Cardboard"};
    struct Cube *cubes;
    input_Cubes(&cubes, &number_of_cubes, allowed_colors, allowed_materials);
    struct ColorAnalysis color_results[NUMBER_OF_ALLOWED_COLORS];
    analyze_by_color(cubes, number_of_cubes, allowed_colors, color_results);
    output_color_analysis(allowed_colors, color_results);
    printf("\nEnter edge length n (for wooden cubes): ");
    GetInt(&n);
    printf("Enter edge length m (for metal cubes > m): ");
    GetInt(&m);
    struct MaterialSizeAnalysis material_result;
    analyze_by_material_and_size(cubes, number_of_cubes, n, m, &material_result);
    output_material_size_analysis(&material_result);

    free(cubes);
    return 0;
}








































































