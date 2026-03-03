#ifndef HEADER_H                                                                                                                                     // Абарона ад паўторнага ўключэння загалоўачнага файла.
#define HEADER_H    
#define MAX_ALLOWED 20

typedef struct 
{
    char illness[MAX_ALLOWED];
    char local_doctor[MAX_ALLOWED];
} LocalRecord;

typedef struct 
{
    char illness[MAX_ALLOWED];
    char attending_doctor[MAX_ALLOWED];
    char adress[MAX_ALLOWED];
    int hospital_number;
} HospitalRecord;

typedef union 
{
    LocalRecord local;
    HospitalRecord hospital; 
} MedicalInfo;

typedef struct  
{
    char first_name[MAX_ALLOWED];
    char surname[MAX_ALLOWED];
    int age;
    int was_hospitalized;
    MedicalInfo health_information;
    
} Child;

void rewind_linux(void);
void GetInt(int *value);
void memory_allocation_Child(Child **children, int number_of_children);
void input_Child(Child **children, int *number_of_children);
void output_Child(Child *children, int number_of_children);
void children_analysis(Child *children, int number_of_children,
                       Child **result, int *result_count, const char *target_illness);
void output_children_with_target_illness(Child *children, int count);
void children_free(Child **children);                                                                                                                           // Аб'ява функцыі бяспечнага ўводу цэлага ліку.


#endif