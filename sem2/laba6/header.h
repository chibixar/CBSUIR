#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NAME_LEN 50

typedef double (*DistanceFunc)(double hx, double hy, double px, double py);

typedef struct {
    int id;
    double x;
    double y;
    int total_beds;
    int free_beds;
    char **patients_names;     
    DistanceFunc get_distance; 
} Hospital;

typedef struct Node {
    Hospital data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    int size;
} HospitalQueue;

// Памяць і чарга
void enqueue(HospitalQueue *q, Hospital h);
Hospital dequeue(HospitalQueue *q);
Hospital create_hospital(int id, double x, double y, int beds, DistanceFunc func);
void free_hospital(Hospital *h);
void free_queue(HospitalQueue *q);

// Матэматыка
double dist_euclidean(double hx, double hy, double px, double py);
double dist_manhattan(double hx, double hy, double px, double py);
DistanceFunc get_func_by_type(int type);

// Аналіз
void admit_patient(HospitalQueue *q, const char *name, double px, double py);
void discharge_patient(HospitalQueue *q, const char *name);
void print_queue_status(HospitalQueue *q);

// Уваходныя дадзеныя
void load_hospitals_file(const char *filename, HospitalQueue *q);
void load_patients_file(const char *filename, HospitalQueue *q);
void load_hospitals_manual(HospitalQueue *q);
void load_patients_manual(HospitalQueue *q);

// Запуск
void initialize_system(HospitalQueue *q);
int process_user_command(HospitalQueue *q);

#endif