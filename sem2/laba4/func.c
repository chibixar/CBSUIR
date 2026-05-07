#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void read_line(char *buffer, int size, FILE *f)
{
    fgets(buffer, size, f);
    buffer[strcspn(buffer, "\n")] = 0;
}

void rewind_linux(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void GetInt(int *value)
{
    while (1)
    {
        if (scanf("%d", value) == 1)
        {
            rewind_linux();
            return;
        }
        else
        {
            printf("Invalid input. Please enter an integer.\n");
            rewind_linux();
        }
    }
}

void memory_allocation_Child(Child **children, int number_of_children)
{
    *children = malloc(number_of_children * sizeof(Child));
    if (*children == NULL)
    {
        printf("Struct memory allocation failed.\n");
        exit(1);
    }
}

void get_input_file_name(char *filename)
{
    printf("Enter file name to read:\n");
    fgets(filename, MAX_FILENAME, stdin);
    filename[strcspn(filename, "\n")] = 0;
}

void get_output_file_name(char *filename)
{
    printf("Enter file name to save:\n");
    fgets(filename, MAX_FILENAME, stdin);
    filename[strcspn(filename, "\n")] = 0;
}


void read_children_from_file(const char *filename, Child **children, int *count)
{
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    int capacity = 16;
    *count = 0;
    *children = malloc(capacity * sizeof(Child));

    char line[256];
    while (fgets(line, sizeof(line), f))
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

        if (*count >= capacity)
        {
            capacity *= 2;
            *children = realloc(*children, capacity * sizeof(Child));
        }
        (*children)[(*count)++] = c;
    }

    fclose(f);
}

void read_children_from_binary_file(const char *filename, Child **children, int *count)
{
    FILE *f = fopen(filename, "rb");
    if (!f)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    fread(count, sizeof(int), 1, f);

    *children = malloc((*count) * sizeof(Child));
    if (!*children)
    {
        printf("Memory allocation failed.\n");
        fclose(f);
        return;
    }

    fread(*children, sizeof(Child), *count, f);
    fclose(f);
}

void input_Child(Child **children, int *number_of_children)
{
    printf("Enter number of children: ");
    GetInt(number_of_children);
    memory_allocation_Child(children, *number_of_children);

    for (int i = 0; i < *number_of_children; i++)
    {
        Child *c = *children + i;
        printf("\n--- Child %d ---\n", i + 1);

        printf("First name: ");
        read_line(c->first_name, MAX_ALLOWED, stdin);

        printf("Surname: ");
        read_line(c->surname, MAX_ALLOWED, stdin);

        printf("Age: ");
        GetInt(&c->age);

        printf("Was hospitalized? (1=yes, 0=no): ");
        GetInt(&c->was_hospitalized);

        if (c->was_hospitalized)
        {
            printf("Illness: ");
            read_line(c->health_information.hospital.illness, MAX_ALLOWED, stdin);

            printf("Attending doctor: ");
            read_line(c->health_information.hospital.attending_doctor, MAX_ALLOWED, stdin);

            printf("Hospital address: ");
            read_line(c->health_information.hospital.adress, MAX_ALLOWED, stdin);

            printf("Hospital number: ");
            GetInt(&c->health_information.hospital.hospital_number);
        }
        else
        {
            printf("Illness: ");
            read_line(c->health_information.local.illness, MAX_ALLOWED, stdin);

            printf("Local doctor: ");
            read_line(c->health_information.local.local_doctor, MAX_ALLOWED, stdin);
        }
    }
}

void choose_input(Child **children, int *number_of_children)
{
    int choice;
    printf("Choose input method:\n");
    printf("1. Read from text file\n");
    printf("2. Enter from keyboard\n");
    printf("3. Read from binary file\n");
    printf("Your choice: ");
    GetInt(&choice);

    switch (choice)
    {
        case 1:
        {
            char filename[MAX_FILENAME];
            get_input_file_name(filename);
            read_children_from_file(filename, children, number_of_children);
            break;
        }
        case 2:
            input_Child(children, number_of_children);
            break;
        case 3:
        {
            char filename[MAX_FILENAME];
            get_input_file_name(filename);
            read_children_from_binary_file(filename, children, number_of_children);
            break;
        }
        default:
            printf("Invalid choice. Defaulting to keyboard input.\n");
            input_Child(children, number_of_children);
            break;
    }
}

void write_children_to_txt_file(const char *filename, Child *children, int count)
{
    FILE *f = fopen(filename, "wa");
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
            fprintf(f, "%-20s %-20s %-5d yes   %-20s %-20s %-20s #%d\n",
                    c->first_name,
                    c->surname,
                    c->age,
                    c->health_information.hospital.illness,
                    c->health_information.hospital.attending_doctor,
                    c->health_information.hospital.adress,
                    c->health_information.hospital.hospital_number);
        }
        else
        {
            fprintf(f, "%-20s %-20s %-5d no    %-20s %-20s\n",
                    c->first_name,
                    c->surname,
                    c->age,
                    c->health_information.local.illness,
                    c->health_information.local.local_doctor);
        }
    }

    fclose(f);
    printf("Data written to text file '%s'.\n", filename);
}

void write_children_to_binary_file(const char *filename, Child *children, int count, const char *mode)
{
    FILE *f = fopen(filename, mode);
    if (!f)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, f);
    fwrite(children, sizeof(Child), count, f);
    fclose(f);
    printf("Data written to binary file '%s'.\n", filename);
}

void choose_output(Child *children, int number_of_children)
{
    char filename[MAX_FILENAME];
    get_output_file_name(filename);

    int choice;
    printf("Choose output format:\n");
    printf("1. Write to text (.txt) file\n");
    printf("2. Write to binary file\n");
    printf("Your choice: ");
    GetInt(&choice);

    switch (choice)
    {
        case 1:
            write_children_to_txt_file(filename, children, number_of_children);
            break;
        case 2:
            write_children_to_binary_file(filename, children, number_of_children, "wb");
            break;
        default:
            printf("Invalid choice. Defaulting to text file.\n");
            write_children_to_txt_file(filename, children, number_of_children);
            break;
    }
}


void output_Child(Child *children, int number_of_children)
{
    printf("\n%-5s %-20s %-20s %-5s %-5s %-20s %-20s %-20s\n",
           "No.", "First Name", "Surname", "Age", "Hosp", "Illness", "Doctor", "Address/Hospital#");
    printf("%-5s %-20s %-20s %-5s %-5s %-20s %-20s %-20s\n",
           "---", "----------", "-------", "---", "----", "-------", "------", "-----------------");

    for (int i = 0; i < number_of_children; i++)
    {
        Child *c = &children[i];
        const char *illness, *doctor, *extra;
        char extra_buf[MAX_ALLOWED * 2];

        if (c->was_hospitalized)
        {
            illness = c->health_information.hospital.illness;
            doctor  = c->health_information.hospital.attending_doctor;
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

int compare_by_surname(const void *a, const void *b)
{
    return strcmp(((const Child *)a)->surname, ((const Child *)b)->surname);
}

void children_analysis(Child *children, int number_of_children,
                        Child **result, int *result_count,
                        const char *target_illness)
{
    *result_count = 0;
    *result = malloc(number_of_children * sizeof(Child));

    for (int i = 0; i < number_of_children; i++)
    {
        const char *ill = children[i].was_hospitalized
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