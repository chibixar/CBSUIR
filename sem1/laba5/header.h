#ifndef HEADER_H                                                  
#define HEADER_H                                                  

#define LOWEST_ASCII_DIGIT 48                                      //мінімальны ASCII код лічбы.
#define HIGHEST_ASCII_DIGIT 57                                     //максімальны ASCII код лічбы.
#define SPACE 32                                                   //ASCII код прабелу.

int GetInt(void);                                                  //прататып функцыі ўводу цэлага ліку.
char* string_memory_allocate(char* string, int string_size);       //прататып функцыі выдзяленне памяці пад радок.
char* string_input(char* string, int string_size);                 //прататып функцыі увод радка.
void string_digit_word(char* string, int* sum);                    //прататып функцыі апрацоўка радка.

int word_isdigit(char* string, int* sum, int i);                   //прататып функцыі праверка слова на лічбавы фармат.
int char_isdigit(char* string, int i);                             //прататып функцыі праверка аднаго сімвала.
void linux_rewind();

#endif                                                             
