#ifndef HEADER_H                                                  
#define HEADER_H    
#define NUMBER_OF_ALLOWED_COLORS 4
#define MAX_COLOR_LENGTH 10
#define NUMBER_OF_ALLOWED_MATERIALS 3
#define MAX_MATERIAL_LENGTH 10

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


void rewind_linux(void);
void memory_allocation_Cubes(struct Cube **cubes, int number_of_cubes);
void color_input(char *color, char allowed_colors[][MAX_COLOR_LENGTH]);
void material_input(char *material, char allowed_materials[][MAX_MATERIAL_LENGTH]);
void input_Cubes(struct Cube **cubes, int *number_of_cubes, char allowed_colors[][MAX_COLOR_LENGTH], char allowed_materials[][MAX_MATERIAL_LENGTH]);
void analyze_by_color(struct Cube *cubes, int number_of_cubes, char allowed_colors[][MAX_COLOR_LENGTH], struct ColorAnalysis *results);
void analyze_by_material_and_size(struct Cube *cubes, int number_of_cubes, int n, int m, struct MaterialSizeAnalysis *result);
void output_color_analysis(char allowed_colors[][MAX_COLOR_LENGTH], struct ColorAnalysis *results);
void output_material_size_analysis(struct MaterialSizeAnalysis *result);
void GetInt(int *value);
#endif