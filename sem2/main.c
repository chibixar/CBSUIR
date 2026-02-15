#include <stdio.h>
#include <stdlib.h>
#include "header.h"

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








































































