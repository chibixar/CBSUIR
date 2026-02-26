#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main(void)
{
    int number_of_cubes;                                                                                        // Колькасць кубікаў.
    int n, m;                                                                                                   // Памеры рабёр для аналізу.
    char allowed_colors[NUMBER_OF_ALLOWED_COLORS][MAX_COLOR_LENGTH] = {"Red", "Yellow", "Green", "Blue"};      // Масіў дазволеных колераў.
    char allowed_materials[NUMBER_OF_ALLOWED_MATERIALS][MAX_MATERIAL_LENGTH] = {"Wood", "Metal", "Cardboard"}; // Масіў дазволеных матэрыялаў.
    struct Cube *cubes;                                                                                         // Указальнік на дынамічны масіў кубікаў.
    input_Cubes(&cubes, &number_of_cubes, allowed_colors, allowed_materials);                                   // Увод дадзеных пра кубікі ад карыстальніка.
    struct ColorAnalysis color_results[NUMBER_OF_ALLOWED_COLORS];                                               // Масіў вынікаў аналізу па колеры.
    analyze_by_color(cubes, number_of_cubes, allowed_colors, color_results);                                    // Аналіз кубікаў па колеры.
    output_color_analysis(allowed_colors, color_results);                                                       // Вывад выніку аналізу па колеры.
    printf("\nEnter edge length n (for wooden cubes): ");                                                       // Запыт даўжыні рабра n.
    GetInt(&n);                                                                                                 // Увод даўжыні рабра n для драўляных кубікаў.
    printf("Enter edge length m (for metal cubes > m): ");                                                      // Запыт парогавага значэння m.
    GetInt(&m);                                                                                                 // Увод парогавага значэння m для металічных кубікаў.
    struct MaterialSizeAnalysis material_result;                                                                 // Структура для захавання выніку аналізу па матэрыяле.
    analyze_by_material_and_size(cubes, number_of_cubes, n, m, &material_result);                               // Аналіз кубікаў па матэрыяле і памеры.
    output_material_size_analysis(&material_result);                                                            // Вывад выніку аналізу па матэрыяле.
    free(cubes);                                                                                                // Вызваленне памяці, выдзеленай пад масіў кубікаў.
    return 0;
}