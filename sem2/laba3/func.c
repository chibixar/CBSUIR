#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "header.h"


void GetInt(int *value) {
    char ch;  
    while(1)
    {                                                      
        if (scanf("%d", value) == 1) {                                                              // Праверка, ці ўдалося счытаць цэлы лік.
            rewind_linux();                                                                         // Ачыстка буфера ўводу пасля паспяховага счытвання.
            return;
        } else {
            printf("Invalid input. Please enter an integer.\n");                                    // Паведамленне пра памылку ўводу.
            rewind_linux();                                                                         // Ачыстка буфера пасля некарэктнага ўводу.
        }
    }
}

void memory_allocation_Child(Child **children,int number_of_children)
{
    *children = malloc(number_of_children * (sizeof(Child)));                                       // Выдзяленне памяці пад масіў дзяцей.
    if (*children == NULL)
    {
        printf("Struct memory allocation failed.");                                                 // Паведамленне пра памылку выдзялення памяці.
        exit(1);                                                                                    // Завяршэнне праграмы пры памылцы выдзялення памяці.
    }
}

void read_children_from_file(const char *filename, Child **children, int *count)
{
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    fscanf(f,"%d\n",count);

    *children = malloc((*count) * sizeof(Child));

    for (int i = 0; i < *count; i++)
    {
        Child *c = &(*children)[i];

        fgets(c->first_name, MAX_ALLOWED, f);
        c->first_name[strcspn(c->first_name,"\n")] = 0;

        fgets(c->surname, MAX_ALLOWED, f);
        c->surname[strcspn(c->surname,"\n")] = 0;

        fscanf(f,"%d\n",&c->age);
        fscanf(f,"%d\n",&c->was_hospitalized);

        if (c->was_hospitalized)
        {
            fgets(c->health_information.hospital.illness, MAX_ALLOWED, f);
            c->health_information.hospital.illness[strcspn(c->health_information.hospital.illness,"\n")] = 0;

            fgets(c->health_information.hospital.attending_doctor, MAX_ALLOWED, f);
            c->health_information.hospital.attending_doctor[strcspn(c->health_information.hospital.attending_doctor,"\n")] = 0;

            fgets(c->health_information.hospital.adress, MAX_ALLOWED, f);
            c->health_information.hospital.adress[strcspn(c->health_information.hospital.adress,"\n")] = 0;

            fscanf(f,"%d\n",&c->health_information.hospital.hospital_number);
        }
        else
        {
            fgets(c->health_information.local.illness, MAX_ALLOWED, f);
            c->health_information.local.illness[strcspn(c->health_information.local.illness,"\n")] = 0;

            fgets(c->health_information.local.local_doctor, MAX_ALLOWED, f);
            c->health_information.local.local_doctor[strcspn(c->health_information.local.local_doctor,"\n")] = 0;
        }
    }

    fclose(f);
}

void write_children_to_file(const char *filename, Child *children, int count)
{
    FILE *f = fopen(filename, "w");
    if (!f)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(f,"%-5s %-20s %-20s %-5s %-5s %-20s %-20s %-20s\n",
           "No.", "First Name", "Surname", "Age", "Hosp", "Illness", "Doctor", "Address/Hospital#");

    for (int i = 0; i < count; i++)
    {
        Child *c = &children[i];

        if (c->was_hospitalized)
        {
            fprintf(f,"%-5d %-20s %-20s %-5d %-5s %-20s %-20s %-20s #%d\n",
                    i+1,
                    c->first_name,
                    c->surname,
                    c->age,
                    "yes",
                    c->health_information.hospital.illness,
                    c->health_information.hospital.attending_doctor,
                    c->health_information.hospital.adress,
                    c->health_information.hospital.hospital_number);
        }
        else
        {
            fprintf(f,"%-5d %-20s %-20s %-5d %-5s %-20s %-20s %-20s\n",
                    i+1,
                    c->first_name,
                    c->surname,
                    c->age,
                    "no",
                    c->health_information.local.illness,
                    c->health_information.local.local_doctor,
                    "-");
        }
    }

    fclose(f);
}

void output_Child(Child *children, int number_of_children)
{
    printf("\n%-5s %-20s %-20s %-5s %-5s %-20s %-20s %-20s\n",
           "No.", "First Name", "Surname", "Age", "Hosp", "Illness", "Doctor", "Address/Hospital#"); // Вывад загалоўка табліцы.
    printf("%-5s %-20s %-20s %-5s %-5s %-20s %-20s %-20s\n",
           "---", "----------", "-------", "---", "----", "-------", "------", "-----------------"); // Вывад падзяляльніка табліцы.

    for (int i = 0; i < number_of_children; i++)
    {
        Child *c = &children[i];                                                                    // Указальнік на бягучае дзіця.
        const char *illness, *doctor, *extra;
        char extra_buf[MAX_ALLOWED];                                                                // Буфер для фарматавання адраса і нумара бальніцы.

        if (c->was_hospitalized)
        {
            illness = c->health_information.hospital.illness;                                      // Атрыманне назвы хваробы (шпіталь).
            doctor  = c->health_information.hospital.attending_doctor;                             // Атрыманне імя лечачага ўрача.
            snprintf(extra_buf, sizeof(extra_buf), "%s #%d",
                     c->health_information.hospital.adress,
                     c->health_information.hospital.hospital_number);                              // Фарматаванне адраса і нумара бальніцы ў адзін радок.
            extra = extra_buf;                                                                      // Прысваенне адфарматаванага радка.
        }
        else
        {
            illness = c->health_information.local.illness;                                         // Атрыманне назвы хваробы (мясцовы ўрач).
            doctor  = c->health_information.local.local_doctor;                                    // Атрыманне імя мясцовага ўрача.
            extra   = "-";                                                                          // Дадатковае поле не выкарыстоўваецца.
        }

        printf("%-5d %-20s %-20s %-5d %-5s %-20s %-20s %-20s\n",
               i + 1,
               c->first_name,
               c->surname,
               c->age,
               c->was_hospitalized ? "yes" : "no",
               illness,
               doctor,
               extra);                                                                             // Вывад радка табліцы для бягучага дзіцяці.
    }
    printf("\n");
}

int compare_by_surname(const void *a, const void *b) {
    return strcmp(((const Child *)a)->surname, ((const Child *)b)->surname); // Параўнанне двух дзяцей па прозвішчы для сартавання.
}

void children_analysis(Child *children, int number_of_children, Child **result, int *result_count, const char *target_illness)
{
    *result_count = 0;                                                                              // Скід лічыльніка вынікаў.
    *result = malloc(number_of_children * sizeof(Child));                                           // Выдзяленне максімальна магчымай памяці пад вынік.
    for (int i = 0; i < number_of_children; i++)
    {
        char *ill = children[i].was_hospitalized
        ? children[i].health_information.hospital.illness
        : children[i].health_information.local.illness;                                            // Выбар назвы хваробы ў залежнасці ад флага шпіталізацыі.
        if (strcmp(ill, target_illness) == 0) 
        (*result)[(*result_count)++] = children[i];                                                // Дадаванне дзіцяці ў масіў вынікаў і павелічэнне лічыльніка.
    }
    if (*result_count == 0)
    {
    free(*result);                                                                                  // Вызваленне памяці пры адсутнасці вынікаў.
    *result = NULL;                                                                                 // Абнуленне паказальніка пры пустым выніку.
    return;
    }
    Child *tmp = realloc(*result, *result_count * sizeof(Child));                                       // Змяншэнне памяці масіву да фактычнага памеру.
    if (!tmp) 
    {
        free(*result);                                                                              // Вызваленне памяці пры памылцы realloc.
        exit(1);                                                                                    // Завяршэнне праграмы пры памылцы перавыдзялення памяці.
    }
    *result = tmp;                                                                                  // Прысваенне новага паказальніка пасля realloc.
    qsort(*result, *result_count, sizeof(Child), compare_by_surname);                              // Сартаванне вынікаў па прозвішчы.
}

void output_children_with_target_illness(Child *children_with_target_illness, int result_count)
{
    if (!children_with_target_illness || result_count == 0) { printf("\nNo children found with that illness.\n"); return; } // Выхад з функцыі пры адсутнасці вынікаў.
    printf("\n===== Children with target illness (alphabetical by surname) =====\n");
    for (int i = 0; i < result_count; i++)
        printf("%d. %s %s\n", i+1, children_with_target_illness[i].surname, children_with_target_illness[i].first_name); // Вывад прозвішча і імя дзіцяці.
}

void rewind_linux(void)
{
    int c;
    while((c=getchar()) != '\n' && c != EOF); // Чытанне сімвалаў да канца радка або канца файла.
}