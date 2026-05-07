#include <stdio.h>

#ifndef HEADER_H
#define HEADER_H
#define MAX_ALLOWED 20
#define MAX_FILENAME 100

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

void read_line(char *buffer, int size, FILE *f);
void GetInt(int *value);
void rewind_linux(void);
void get_input_file_name(char *filename);
void get_output_file_name(char *filename);
void choose_input(Child **children, int *number_of_children);
void choose_output(Child *children, int number_of_children);
void memory_allocation_Child(Child **children, int number_of_children);
void read_children_from_file(const char *filename, Child **children, int *count);
void read_children_from_binary_file(const char *filename, Child **children, int *count);
void input_Child(Child **children, int *number_of_children);
void write_children_to_txt_file(const char *filename, Child *children, int count);
void write_children_to_binary_file(const char *filename, Child *children, int count, const char *mode);
void output_Child(Child *children, int number_of_children);
int compare_by_surname(const void *a, const void *b);
void children_analysis(Child *children, int number_of_children, Child **result, int *result_count, const char *target_illness);

#endif