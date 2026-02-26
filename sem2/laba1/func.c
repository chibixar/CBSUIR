#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void GetInt(int *value) {
    char ch;  
    while(1)
    {                                                      
        if (scanf("%d", value) == 1) {                             // Праверка, ці ўдалося счытаць цэлы лік.
            fflush(stdin);                                         // Ачыстка буфера ўводу пасля паспяховага счытвання.
            return;
        } else {
            printf("Invalid input. Please enter an integer.\n");   // Паведамленне пра памылку ўводу.
            fflush(stdin);                                         // Ачыстка буфера пасля некарэктнага ўводу.
        }
    }
}

void memory_allocation_Cubes(struct Cube **cubes,int number_of_cubes)
{
    *cubes = malloc(number_of_cubes * (sizeof(struct Cube)));      // Выдзяленне памяці пад масіў кубікаў.
    if (*cubes == NULL)
    {
        printf("Cubes memory allocation failed.");                 // Паведамленне пра памылку выдзялення памяці.
        exit(1);                                                   // Завяршэнне праграмы пры памылцы выдзялення памяці.
    }
}

void color_input(char *color, char allowed_colors[][MAX_COLOR_LENGTH])
{
    while (1)
    {
        scanf("%9s", color);                                       // Счытванне радка колеру, не больш за 9 сімвалаў.
        rewind_linux();                                            // Ачыстка буфера ўводу пасля счытвання.
        for (int i = 0; i < NUMBER_OF_ALLOWED_COLORS; i++)
        {
            if (strcmp(color, allowed_colors[i]) == 0)             // Параўнанне ўведзенага колеру з дазволенымі.
                return;
        }
        printf("Invalid color. Try again: (Red Yellow Green Blue)\n"); // Паведамленне пра недапушчальны колер.
    }
}

void material_input(char *material, char allowed_materials[][MAX_MATERIAL_LENGTH])
{
    while (1)
    {
        scanf("%9s", material);                                    // Счытванне радка матэрыялу, не больш за 9 сімвалаў.
        rewind_linux();                                            // Ачыстка буфера ўводу пасля счытвання.
        for (int i = 0; i < NUMBER_OF_ALLOWED_MATERIALS; i++)
        {
            if (strcmp(material, allowed_materials[i]) == 0)       // Параўнанне ўведзенага матэрыялу з дазволенымі.
                return;
        }
        printf("Invalid material. Try again: (Wood Metal Cardboard)\n"); // Паведамленне пра недапушчальны матэрыял.
    }
}

void input_Cubes (struct Cube **cubes, int *number_of_cubes, char allowed_colors[][MAX_COLOR_LENGTH], char allowed_materials[][MAX_MATERIAL_LENGTH])
{
    printf("Enter number of cubes: ");
    GetInt(number_of_cubes);                                       // Увод колькасці кубікаў.
    memory_allocation_Cubes(cubes, *number_of_cubes);              // Выдзяленне памяці пад патрэбную колькасць кубікаў.
    for (int i = 0; i < *number_of_cubes; i++)
    {
    printf("\nCube %d\n",i+1);
    printf("Size: (in cm) ");
    GetInt((&(*cubes)[i].size));                                   // Увод памеру рабра i-га кубіка.
    printf("Color: ");
    color_input((*cubes)[i].color, allowed_colors);                // Увод і праверка колеру i-га кубіка.
    printf("Material: ");
    material_input((*cubes)[i].material, allowed_materials);       // Увод і праверка матэрыялу i-га кубіка.
    }
}

void analyze_by_color(struct Cube *cubes, int number_of_cubes, char allowed_colors[][MAX_COLOR_LENGTH], struct ColorAnalysis *results)
{
    for (int i = 0; i < NUMBER_OF_ALLOWED_COLORS; i++)
    {
        results[i].count = 0;                                      // Скід лічыльніка кубікаў дадзенага колеру.
        results[i].total_volume = 0;                               // Скід сумарнага аб'ёму кубікаў дадзенага колеру.
        for (int j = 0; j < number_of_cubes; j++)
        {
            if (strcmp(cubes[j].color, allowed_colors[i]) == 0)    // Кубік адпавядае бягучаму колеру.
            {
                results[i].count++;                                                                // Павелічэнне лічыльніка кубікаў дадзенага колеру.
                results[i].total_volume += cubes[j].size * cubes[j].size * cubes[j].size;         // Дадаванне аб'ёму кубіка (a³).
            }
        }
    }
}

void output_color_analysis(char allowed_colors[][MAX_COLOR_LENGTH], struct ColorAnalysis *results)
{
    printf("\n=== Task a) Color Analysis ===\n");
    for (int i = 0; i < NUMBER_OF_ALLOWED_COLORS; i++)
    {
        if (results[i].count > 0)                                  // Вывад толькі для колераў, якія прысутнічаюць.
        {
            printf("%s cubes: Count = %d, Total Volume = %d cm³\n", 
                   allowed_colors[i], results[i].count, results[i].total_volume); // Вывад статыстыкі для бягучага колеру.
        }
    }
}

void analyze_by_material_and_size(struct Cube *cubes, int number_of_cubes, int n, int m, struct MaterialSizeAnalysis *result)
{
    result->wooden_count = 0;                                      // Скід лічыльніка драўляных кубікаў.
    result->metal_count = 0;                                       // Скід лічыльніка металічных кубікаў.
    result->n = n;                                                 // Захаванне зададзенага памеру n.
    result->m = m;                                                 // Захаванне парогавага памеру m.
    for (int i = 0; i < number_of_cubes; i++)
    {
        if (strcmp(cubes[i].material, "Wood") == 0 && cubes[i].size == n) // Драўляны кубік з рабром роўным n.
        {
            result->wooden_count++;                                // Павелічэнне лічыльніка драўляных кубікаў.
        }
        if (strcmp(cubes[i].material, "Metal") == 0 && cubes[i].size > m) // Металічны кубік з рабром больш за m.
        {
            result->metal_count++;                                 // Павелічэнне лічыльніка металічных кубікаў.
        }
    }
}

void output_material_size_analysis(struct MaterialSizeAnalysis *result)
{
    printf("\n=== Task b) Material and Size Analysis ===\n");
    if(result->wooden_count) printf("Wooden cubes with edge = %d cm: %d\n", result->n, result->wooden_count); // Вывад колькасці драўляных кубікаў.
    else printf("No wooden cubes with edge = %d cm\n", result->n);                                                                          // Вывад паведамлення пра адсутнасць драўляных кубікаў.
    if(result->metal_count) printf("Metal cubes with edge > %d cm: %d\n", result->m, result->metal_count);    // Вывад колькасці металічных кубікаў.
    else printf("No metal cubes with edge > %d cm\n", result->m);                                                                           // Вывад паведамлення пра адсутнасць металічных кубікаў.
}

void rewind_linux(void)
{
    int c;
    while((c=getchar()) != '\n' && c != EOF); // Чытанне сімвалаў да канца радка або канца файла.
}