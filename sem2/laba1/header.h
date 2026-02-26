#ifndef HEADER_H                                                                                                                                     // Абарона ад паўторнага ўключэння загалоўачнага файла.
#define HEADER_H    
#define NUMBER_OF_ALLOWED_COLORS 4                                                                                                                   // Колькасць дапушчальных колераў.
#define MAX_COLOR_LENGTH 10                                                                                                                          // Максімальная даўжыня радка колеру.
#define NUMBER_OF_ALLOWED_MATERIALS 3                                                                                                                // Колькасць дапушчальных матэрыялаў.
#define MAX_MATERIAL_LENGTH 10                                                                                                                       // Максімальная даўжыня радка матэрыялу.

struct Cube
{
    int size;                                                                                                                                        // Даўжыня рабра ў сантыметрах.
    char color[MAX_COLOR_LENGTH];                                                                                                                    // Колер кубіка.
    char material[MAX_MATERIAL_LENGTH];                                                                                                              // Матэрыял кубіка.
};

struct ColorAnalysis
{
    int count;                                                                                                                                       // Колькасць кубікаў дадзенага колеру.
    int total_volume;                                                                                                                                // Сумарны аб'ём кубікаў дадзенага колеру.
};

struct MaterialSizeAnalysis
{
    int wooden_count;                                                                                                                                // Колькасць драўляных кубікаў з памерам n.
    int metal_count;                                                                                                                                 // Колькасць металічных кубікаў з памерам большым за m.
    int n;                                                                                                                                           // Зададзены памер для драўляных кубікаў.
    int m;                                                                                                                                           // Парогавы памер для металічных кубікаў.
};

void rewind_linux(void);                                                                                                                             // Аб'ява функцыі ачысткі буфера ўводу.
void memory_allocation_Cubes(struct Cube **cubes, int number_of_cubes);                                                                              // Аб'ява функцыі выдзялення памяці пад масіў кубікаў.
void color_input(char *color, char allowed_colors[][MAX_COLOR_LENGTH]);                                                                              // Аб'ява функцыі ўводу колеру.
void material_input(char *material, char allowed_materials[][MAX_MATERIAL_LENGTH]);                                                                  // Аб'ява функцыі ўводу матэрыялу.
void input_Cubes(struct Cube **cubes, int *number_of_cubes, char allowed_colors[][MAX_COLOR_LENGTH], char allowed_materials[][MAX_MATERIAL_LENGTH]); // Аб'ява функцыі ўводу ўсіх кубікаў.
void analyze_by_color(struct Cube *cubes, int number_of_cubes, char allowed_colors[][MAX_COLOR_LENGTH], struct ColorAnalysis *results);              // Аб'ява функцыі аналізу па колеры.
void analyze_by_material_and_size(struct Cube *cubes, int number_of_cubes, int n, int m, struct MaterialSizeAnalysis *result);                       // Аб'ява функцыі аналізу па матэрыяле і памеры.
void output_color_analysis(char allowed_colors[][MAX_COLOR_LENGTH], struct ColorAnalysis *results);                                                  // Аб'ява функцыі вываду аналізу па колеры.
void output_material_size_analysis(struct MaterialSizeAnalysis *result);                                                                             // Аб'ява функцыі вываду аналізу па матэрыяле.
void GetInt(int *value);                                                                                                                             // Аб'ява функцыі бяспечнага ўводу цэлага ліку.
#endif