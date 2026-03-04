#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "header.h"


void GetInt(int *value) {
    char ch;  
    while(1)
    {                                                      
        if (scanf("%d", value) == 1) {                             // Праверка, ці ўдалося счытаць цэлы лік.
            rewind_linux();                                         // Ачыстка буфера ўводу пасля паспяховага счытвання.
            return;
        } else {
            printf("Invalid input. Please enter an integer.\n");   // Паведамленне пра памылку ўводу.
            rewind_linux();                                         // Ачыстка буфера пасля некарэктнага ўводу.
        }
    }
}

void memory_allocation_Child(Child **children,int number_of_children)
{
    *children = malloc(number_of_children * (sizeof(Child)));      // Выдзяленне памяці пад масіў дзяцей.
    if (*children == NULL)
    {
        printf("Struct memory allocation failed.");                 // Паведамленне пра памылку выдзялення памяці.
        exit(1);                                                   // Завяршэнне праграмы пры памылцы выдзялення памяці.
    }
}

void input_Child(Child **children, int *number_of_children)
{
    printf("Enter number of children: ");
    GetInt(number_of_children);
    memory_allocation_Child(children, *number_of_children);

    for (int i = 0; i < *number_of_children; i++)
    {
        Child *c = *children + i;             // pointer arithmetic: start of array + offset
        printf("\n--- Child %d ---\n", i + 1);

        printf("First name: ");
        fgets(c->first_name, MAX_ALLOWED, stdin);
        c->first_name[strcspn(c->first_name, "\n")] = '\0';   // strip trailing newline left by fgets

        printf("Surname: ");
        fgets(c->surname, MAX_ALLOWED, stdin);
        c->surname[strcspn(c->surname, "\n")] = '\0';

        printf("Age: ");
        GetInt(&c->age);

        printf("Was hospitalized? (1=yes, 0=no): ");
        GetInt(&c->was_hospitalized);

        if (c->was_hospitalized)
        {
            printf("Illness: ");
            fgets(c->health_information.hospital.illness, MAX_ALLOWED, stdin);
            c->health_information.hospital.illness[strcspn(c->health_information.hospital.illness, "\n")] = '\0';

            printf("Attending doctor: ");
            fgets(c->health_information.hospital.attending_doctor, MAX_ALLOWED, stdin);
            c->health_information.hospital.attending_doctor[strcspn(c->health_information.hospital.attending_doctor, "\n")] = '\0';

            printf("Hospital address: ");
            fgets(c->health_information.hospital.adress, MAX_ALLOWED, stdin);
            c->health_information.hospital.adress[strcspn(c->health_information.hospital.adress, "\n")] = '\0';

            printf("Hospital number: ");
            GetInt(&c->health_information.hospital.hospital_number);
        }
        else
        {
            printf("Illness: ");
            fgets(c->health_information.local.illness, MAX_ALLOWED, stdin);
            c->health_information.local.illness[strcspn(c->health_information.local.illness, "\n")] = '\0';

            printf("Local doctor: ");
            fgets(c->health_information.local.local_doctor, MAX_ALLOWED, stdin);
            c->health_information.local.local_doctor[strcspn(c->health_information.local.local_doctor, "\n")] = '\0';
        }
    }
}

void output_Child(Child *children, int number_of_children)
{
    // Table header
    printf("\n%-5s %-20s %-20s %-5s %-5s %-20s %-20s %-20s\n",
           "No.", "First Name", "Surname", "Age", "Hosp", "Illness", "Doctor", "Address/Hospital#");
    printf("%-5s %-20s %-20s %-5s %-5s %-20s %-20s %-20s\n",
           "---", "----------", "-------", "---", "----", "-------", "------", "-----------------");

    for (int i = 0; i < number_of_children; i++)
    {
        Child *c = &children[i];
        const char *illness, *doctor, *extra;
        char extra_buf[MAX_ALLOWED];

        if (c->was_hospitalized)
        {
            illness = c->health_information.hospital.illness;
            doctor  = c->health_information.hospital.attending_doctor;
            // combine address and hospital number into one column
            snprintf(extra_buf, sizeof(extra_buf), "%s #%d",
                     c->health_information.hospital.adress,
                     c->health_information.hospital.hospital_number);
            extra = extra_buf;
        }
        else
        {
            illness = c->health_information.local.illness;
            doctor  = c->health_information.local.local_doctor;
            extra   = "-";
        }

        printf("%-5d %-20s %-20s %-5d %-5s %-20s %-20s %-20s\n",
               i + 1,
               c->first_name,
               c->surname,
               c->age,
               c->was_hospitalized ? "yes" : "no",
               illness,
               doctor,
               extra);
    }
    printf("\n");
}

int compare_by_surname(const void *a, const void *b) {
    return strcmp(((const Child *)a)->surname, ((const Child *)b)->surname);
}

void children_analysis(Child *children, int number_of_children, Child **result, int *result_count, const char *target_illness)
{
    *result_count = 0;
    *result = malloc(number_of_children * sizeof(Child));
    for (int i = 0; i < number_of_children; i++)
    {
        char *ill = children[i].was_hospitalized
        ? children[i].health_information.hospital.illness
        : children[i].health_information.local.illness;
        if (strcmp(ill, target_illness) == 0) 
        (*result)[(*result_count)++] = children[i];
    }
    if (*result_count == 0)
{
    free(*result);
    *result = NULL;
    return;
}
Child *tmp = realloc(*result, *result_count * sizeof(Child));
    if (!tmp) 
    {
        free(*result);
        exit(1);
    }
    *result = tmp;
    qsort(*result, *result_count, sizeof(Child), compare_by_surname);
}

void output_children_with_target_illness(Child *children_with_target_illness, int result_count)
{
    if (!children_with_target_illness || result_count == 0) { printf("\nNo children found with that illness.\n"); return; }
    printf("\n===== Children with target illness (alphabetical by surname) =====\n");
    for (int i = 0; i < result_count; i++)
        printf("%d. %s %s\n", i+1, children_with_target_illness[i].surname, children_with_target_illness[i].first_name);
}

void rewind_linux(void)
{
    int c;
    while((c=getchar()) != '\n' && c != EOF); // Чытанне сімвалаў да канца радка або канца файла.
}








