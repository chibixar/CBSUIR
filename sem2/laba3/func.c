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
        read_line(c->first_name, MAX_ALLOWED, stdin);                                               // Счытванне імя дзіцяці.

        printf("Surname: ");
        read_line(c->surname, MAX_ALLOWED, stdin);                                                  // Счытванне прозвішча дзіцяці.

        printf("Age: ");
        GetInt(&c->age);                                                                            // Увод узросту дзіцяці.

        printf("Was hospitalized? (1=yes, 0=no): ");
        GetInt(&c->was_hospitalized);                                                               // Увод флага шпіталізацыі.

        if (c->was_hospitalized)
        {
            printf("Illness: ");
            read_line(c->health_information.hospital.illness, MAX_ALLOWED, stdin);                  // Счытванне назвы хваробы (шпіталь).

            printf("Attending doctor: ");
            read_line(c->health_information.hospital.attending_doctor, MAX_ALLOWED, stdin);         // Счытванне імя лечачага ўрача.

            printf("Hospital address: ");
            read_line(c->health_information.hospital.adress, MAX_ALLOWED, stdin);                  // Счытванне адраса бальніцы.

            printf("Hospital number: ");
            GetInt(&c->health_information.hospital.hospital_number);                               // Увод нумара бальніцы.
        }
        else
        {
            printf("Illness: ");
            read_line(c->health_information.local.illness, MAX_ALLOWED, stdin);                    // Счытванне назвы хваробы (мясцовы ўрач).

            printf("Local doctor: ");
            read_line(c->health_information.local.local_doctor, MAX_ALLOWED, stdin);               // Счытванне імя мясцовага ўрача.
        }
    }
}


void get_input_file_name(char *filename)
{
    printf("Enter file name to read:\n");
    fgets(filename,MAX_FILENAME,stdin);                                                
    filename[strcspn(filename,"\n")] = 0;
}

void get_output_file_name(char *filename)
{
    printf("Enter file name to save table:\n");
    fgets(filename,100,stdin);
    filename[strcspn(filename,"\n")] = 0;
}

void read_children_from_file(const char *filename, Child **children, int *count)                        //Злічыць структуру з файла.
{
    FILE *f = fopen(filename, "r");                                                                     //Адкрыць файл для чытання.
    if (!f)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    int capacity = 16;                                                                                   //Зменная для выдзялення памяці.
    *count = 0;
    *children = malloc(capacity * sizeof(Child));

    char line[MAX_ALLOWED];
    while (fgets(line, sizeof(line), f))                                                                 //Цыкл па радках файлу.
    {
        Child c = {0};
        char hosp[4];
        if (sscanf(line, "%19s %19s %d %3s %19s %19s %19s #%d",
                   c.first_name, c.surname, &c.age, hosp,
                   c.health_information.hospital.illness,
                   c.health_information.hospital.attending_doctor,
                   c.health_information.hospital.adress,
                   &c.health_information.hospital.hospital_number) == 8
                   && strcmp(hosp, "yes") == 0)
        {
            c.was_hospitalized = 1;
        }
        else if (sscanf(line, "%19s %19s %d %3s %19s %19s",
                        c.first_name, c.surname, &c.age, hosp,
                        c.health_information.local.illness,
                        c.health_information.local.local_doctor) == 6
                        && strcmp(hosp, "no") == 0)
        {
            c.was_hospitalized = 0;
        }
        else
        {
            continue;
        }

        if (*count >= capacity)                                                                             //Перавыдзяленне памяці.
        {
            capacity *= 2;
            *children = realloc(*children, capacity * sizeof(Child));
        }
        (*children)[(*count)++] = c;
    }

    fclose(f);
}

void choose_input(Child **children, int *number_of_children)                                        //Функцыя выюару тыпу ўводу.
{
    int choice;
    printf("Choose input method:\n");
    printf("1. Read from file\n");
    printf("2. Enter from keyboard\n");
    printf("Your choice: ");
    GetInt(&choice);

    switch (choice)
    {
        case 1:                                                                                     //Злічыць з файла.
        {
            char filename[MAX_FILENAME];
            get_input_file_name(filename);
            read_children_from_file(filename, children, number_of_children);
            break;
        }
        case 2:                                                                                     ///Злічыць з клавіятуры.
            input_Child(children, number_of_children);
            break;
        default:
            printf("Invalid choice. Defaulting to keyboard input.\n");
            input_Child(children, number_of_children);
            break;
    }
}

void read_line(char *buffer, int size, FILE *f)
{
    if (fgets(buffer, size, f) != NULL)
    {
        buffer[strcspn(buffer, "\n")] = '\0';                                                           //Замяніць \n на \0.
    }
}

void write_children_to_file(const char *filename, Child *children, int count, const char *mode)         //Функцыя запісу ў файл.
{
    FILE *f = fopen(filename, mode);
    if (!f)                                                                                                                                                                  
    {
        printf("Error opening file for writing.\n");
        return;
    }

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
    fprintf(f, "\n\n");
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

void rewind_linux(void)
{
    int c;
    while((c=getchar()) != '\n' && c != EOF); // Чытанне сімвалаў да канца радка або канца файла.
}