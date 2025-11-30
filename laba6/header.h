#ifndef HEADER_H                                                  
#define HEADER_H                                                  

#define LOWEST_ASCII_DIGIT 48                                      //мінімальны ASCII код лічбы.
#define HIGHEST_ASCII_DIGIT 57                                     //максімальны ASCII код лічбы.
#define SPACE 32                                                   //ASCII код прабелу.

int GetInt(void);                                                  //прататып функцыі ўводу цэлага ліку.
char** text_memory_allocate(char** text, int number_of_strings, int max_string_size);
char** text_input(char** text, int number_of_strings, int max_string_size);
void swap_str(char** a, char** b);
int compare_first_letter(const char* a, const char* b);
int partition_name(char** text, int low, int high);
void Quick_Sort_Alphabetically(char** text, int low, int high);
void output_text(char** text, int number_of_strings);

// int word_isdigit(char* string, int* sum, int i);                   //прататып функцыі праверка слова на лічбавы фармат.
// int char_isdigit(char* string, int i);                             //прататып функцыі праверка аднаго сімвала.

#endif         