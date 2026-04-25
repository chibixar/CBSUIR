#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Stack {                         //Вузел стэка — сімвал і ўказальнік на наступны.
    char   data;
    struct Stack* next;
}Stack;

void  push(Stack** top, char c);       //Дадаць элемент на вяршыню.
char  pop(Stack** top);                //Здыць элемент з вяршыні.
void  printStack(Stack* top);          //Вывесці змест стэка.
void  clearStack(Stack** top);         //Ачысціць увесь стэк.

char* inputFromKeyboard(void);         //Увод выразу з клавіятуры.
char* inputFromFile(void);             //Увод выразу з файла.
int   chooseInputMethod(void);         //Выбар метаду ўводу.

int   checkBrackets(const char* expr); //Праверка правільнасці дужак.

void  showMenu(void);                  //Вывад галоўнага меню.
int   getMenuChoice(void);             //Счытванне выбару карыстальніка.
void  handleCheck(void);               //Апрацоўка пункту праверкі выразу.

#endif
