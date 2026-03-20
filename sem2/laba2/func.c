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

void input_Child(Child **children, int *number_of_children)
{
    printf("Enter number of children: ");
    GetInt(number_of_children);                                                                     // Увод колькасці дзяцей.
    memory_allocation_Child(children, *number_of_children);                                         // Выдзяленне памяці пад патрэбную колькасць дзяцей.

    for (int i = 0; i < *number_of_children; i++)
    {
        Child *c = *children + i;                                                                   // Арыфметыка паказальнікаў: пачатак масіву + зрух.
        printf("\n--- Child %d ---\n", i + 1);

        printf("First name: ");
        fgets(c->first_name, MAX_ALLOWED, stdin);                                                   // Счытванне імя дзіцяці.
        c->first_name[strcspn(c->first_name, "\n")] = '\0';                                         // Выдаленне сімвала новага радка пасля fgets.

        printf("Surname: ");
        fgets(c->surname, MAX_ALLOWED, stdin);                                                      // Счытванне прозвішча дзіцяці.
        c->surname[strcspn(c->surname, "\n")] = '\0';                                               // Выдаленне сімвала новага радка пасля fgets.

        printf("Age: ");
        GetInt(&c->age);                                                                            // Увод узросту дзіцяці.

        printf("Was hospitalized? (1=yes, 0=no): ");
        GetInt(&c->was_hospitalized);                                                               // Увод флага шпіталізацыі.

        if (c->was_hospitalized)
        {
            printf("Illness: ");
            fgets(c->health_information.hospital.illness, MAX_ALLOWED, stdin);                      // Счытванне назвы хваробы (шпіталь).
            c->health_information.hospital.illness[strcspn(c->health_information.hospital.illness, "\n")] = '\0'; // Выдаленне сімвала новага радка.

            printf("Attending doctor: ");
            fgets(c->health_information.hospital.attending_doctor, MAX_ALLOWED, stdin);             // Счытванне імя лечачага ўрача.
            c->health_information.hospital.attending_doctor[strcspn(c->health_information.hospital.attending_doctor, "\n")] = '\0'; // Выдаленне сімвала новага радка.

            printf("Hospital address: ");
            fgets(c->health_information.hospital.adress, MAX_ALLOWED, stdin);                      // Счытванне адраса бальніцы.
            c->health_information.hospital.adress[strcspn(c->health_information.hospital.adress, "\n")] = '\0'; // Выдаленне сімвала новага радка.

            printf("Hospital number: ");
            GetInt(&c->health_information.hospital.hospital_number);                               // Увод нумара бальніцы.
        }
        else
        {
            printf("Illness: ");
            fgets(c->health_information.local.illness, MAX_ALLOWED, stdin);                        // Счытванне назвы хваробы (мясцовы ўрач).
            c->health_information.local.illness[strcspn(c->health_information.local.illness, "\n")] = '\0'; // Выдаленне сімвала новага радка.

            printf("Local doctor: ");
            fgets(c->health_information.local.local_doctor, MAX_ALLOWED, stdin);                   // Счытванне імя мясцовага ўрача.
            c->health_information.local.local_doctor[strcspn(c->health_information.local.local_doctor, "\n")] = '\0'; // Выдаленне сімвала новага радка.
        }
    }
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

void get_target_illness(char *target_illness)
{
    printf("Enter the target illness:\n");
    fgets(target_illness, MAX_ALLOWED, stdin);                                                                           // Счытванне назвы мэтавай хваробы.
    target_illness[strcspn(target_illness, "\n")] = '\0';                                                                // Выдаленне сімвала новага радка пасля fgets.
}

void children_analysis(Child *children, int number_of_children, Child **result, int *result_count,  char *target_illness)
{
    puts(target_illness);
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
    // Child *tmp = realloc(*result, *result_count * sizeof(Child));                                       // Змяншэнне памяці масіву да фактычнага памеру.
    // if (!tmp) 
    // {
    //     free(*result);                                                                              // Вызваленне памяці пры памылцы realloc.
    //     exit(1);                                                                                    // Завяршэнне праграмы пры памылцы перавыдзялення памяці.
    // }
    Child *result = realloc(*result, *result_count * sizeof(Child));                                       // Змяншэнне памяці масіву да фактычнага памеру.
    
    // *result = tmp;                                                                                  // Прысваенне новага паказальніка пасля realloc.
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