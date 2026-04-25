#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stack {                          //Вузел стэка — сімвал і ўказальнік на наступны.
    char          data;
    struct Stack* next;
};

void  push(struct Stack** top, char c); //Дадаць элемент на вяршыню.
char  pop(struct Stack** top);          //Здыць элемент з вяршыні.
void  printStack(struct Stack* top);    //Вывесці змест стэка.
void  clearStack(struct Stack** top);   //Ачысціць увесь стэк.

char* inputFromKeyboard(void);          //Увод выразу з клавіятуры.
char* inputFromFile(void);              //Увод выразу з файла.
int   chooseInputMethod(void);          //Выбар метаду ўводу.

int   checkBrackets(const char* expr);  //Праверка правільнасці дужак.

void  showMenu(void);                   //Вывад галоўнага меню.
int   getMenuChoice(void);              //Счытванне выбару карыстальніка.
void  handleCheck(void);                //Апрацоўка пункту праверкі выразу.

#endif
