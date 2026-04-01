#ifndef HEADER_H                                                                                                                                     // Абарона ад паўторнага ўключэння загалоўачнага файла.
#define HEADER_H    
#define MAX_ALLOWED 20                                                                                                                               // Максімальная даўжыня радкоў у структурах.
#define MAX_FILENAME 100
typedef struct 
{
    char illness[MAX_ALLOWED];                                                                                                                       // Назва хваробы пры лячэнні ў мясцовага ўрача.
    char local_doctor[MAX_ALLOWED];                                                                                                                  // Імя мясцовага ўрача.
} LocalRecord;

typedef struct 
{
    char illness[MAX_ALLOWED];                                                                                                                       // Назва хваробы пры шпіталізацыі.
    char attending_doctor[MAX_ALLOWED];                                                                                                              // Імя лечачага ўрача ў бальніцы.
    char adress[MAX_ALLOWED];                                                                                                                        // Адрас бальніцы.
    int hospital_number;                                                                                                                             // Нумар бальніцы.
} HospitalRecord;

typedef union 
{
    LocalRecord local;                                                                                                                               // Дадзеныя пры мясцовым лячэнні.
    HospitalRecord hospital;                                                                                                                         // Дадзеныя пры шпіталізацыі.
} MedicalInfo;

typedef struct  
{
    char first_name[MAX_ALLOWED];                                                                                                                    // Імя дзіцяці.
    char surname[MAX_ALLOWED];                                                                                                                       // Прозвішча дзіцяці.
    int age;                                                                                                                                         // Узрост дзіцяці.
    int was_hospitalized;                                                                                                                            // Флаг: 1 — быў шпіталізаваны, 0 — не.
    MedicalInfo health_information;                                                                                                                  // Медыцынская інфармацыя (аб'яднанне).
    
} Child;

void read_line(char *buffer, int size, FILE *f);
void GetInt(int *value);                                                                                                                             // Аб'ява функцыі бяспечнага ўводу цэлага ліку.
void rewind_linux(void);                                                                                                                             // Аб'ява функцыі ачысткі буфера ўводу.
void get_input_file_name(char *filename);
void get_output_file_name(char *filename);
void memory_allocation_Child(Child **children, int number_of_children);                                                                              // Аб'ява функцыі выдзялення памяці пад масіў дзяцей.
void write_children_to_file(const char *filename, Child *children, int count, const char *mode);
void read_children_from_file(const char *filename, Child **children, int *count);
void output_Child(Child *children, int number_of_children);                                                                                          // Аб'ява функцыі вываду ўсіх дзяцей.
int compare_by_surname(const void *a, const void *b);                                                                                               // Аб'ява функцыі параўнання па прозвішчы для qsort.
void children_analysis(Child *children, int number_of_children, Child **result, int *result_count, const char *target_illness);                      // Аб'ява функцыі аналізу і фільтрацыі дзяцей.
void output_children_with_target_illness(Child *children, int count);                                                                               // Аб'ява функцыі вываду адфільтраваных дзяцей.
void children_free(Child **children);                                                                                                                // Аб'ява функцыі вызвалення памяці масіву дзяцей.


#endif