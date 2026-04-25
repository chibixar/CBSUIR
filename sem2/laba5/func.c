#include "header.h"

void push(Stack** top, char c)                                 //Дадаць новы элемент на вяршыню стэка.
{
    Stack* node = malloc(sizeof(Stack));                       //Вылучаем памяць для новага вузла.
    if (node == NULL) {                                        //Памяць не вылучана — крытычная памылка.
        fprintf(stderr, "Fatal: out of memory\n");
        exit(EXIT_FAILURE);
    }
    node->data = c;                                            //Захоўваем сімвал у новым вузле.
    node->next = *top;                                         //Новы вузел паказвае на бягучую вяршыню.
    *top = node;                                               //Абнаўляем указальнік на вяршыню стэка.
}

char pop(Stack** top)                                          //Здыць і вярнуць элемент з вяршыні стэка.
{
    if (*top == NULL) return '\0';                             //Стэк пусты — вяртаем пусты сімвал.

    Stack* tmp = *top;                                         //Захоўваем указальнік на выдаляемы вузел.
    char          val = tmp->data;                             //Запамінаем значэнне перад выдаленнем.
    *top = tmp->next;                                          //Перасоўваем вяршыню на наступны элемент.
    free(tmp);                                                 //Вызваляем памяць выдаленага вузла.
    return val;
}

void printStack(Stack* top)                                    //Вывесці змест стэка (выклікаецца калі стэк непусты).
{
    printf("  Remaining in stack: [ ");
    Stack* cur = top;                                          //Абыходзім стэк не мяняючы яго.
    while (cur != NULL) {
        printf("'%c' ", cur->data);                            //Выводзім кожны элемент ад вяршыні да дна.
        cur = cur->next;
    }
    printf("]\n");
}

void clearStack(Stack** top)                                   //Ачысціць увесь стэк і вызваліць памяць.
{
    while (*top != NULL) {                                     //Выдаляем элементы пакуль стэк не стане пустым.
        Stack* tmp = *top;
        *top = tmp->next;
        free(tmp);                                             //Вызваляем кожны вузел паасобку.
    }
}

static int isOpen(char c)                                      //Вярнуць 1 калі сімвал з'яўляецца адкрываючай дужкай.
{
    return c == '(' || c == '[' || c == '{';
}

static int isClose(char c)                                     //Вярнуць 1 калі сімвал з'яўляецца зачыняючай дужкай.
{
    return c == ')' || c == ']' || c == '}';
}

static int isMatchingPair(char open, char close)               //Вярнуць 1 калі зачыняючая адпавядае адкрываючай.
{
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

static char* appendChar(char* buf, int* len, int* cap, char c) //Дадаць сімвал у дынамічны буфер з пашырэннем.
{
    if (*len + 1 >= *cap) {                                    //Буфер поўны — патрэбна пашырэнне памяці.
        *cap *= 2;
        char* tmp = realloc(buf, *cap);
        if (tmp == NULL) {                                     //Не ўдалося пашырыць — вяртаем NULL.
            free(buf);
            return NULL;
        }
        buf = tmp;
    }
    buf[(*len)++] = c;                                         //Дадаём сімвал і павялічваем даўжыню.
    return buf;
}

char* inputFromKeyboard(void)                                  //Прачытаць выраз з клавіятуры ў дынамічны радок.
{
    printf("Enter expression: ");

    int   cap = 64;                                            //Пачатковы памер буфера ў байтах.
    int   len = 0;
    char* buf = malloc(cap);                                   //Вылучаем памяць для захавання радка.
    if (buf == NULL) return NULL;

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {              //Чытаем пасімвальна да канца радка.
        buf = appendChar(buf, &len, &cap, (char)c);
        if (buf == NULL) return NULL;                          //Памылка пашырэння буфера.
    }
    buf[len] = '\0';                                           //Завяршаем радок нуль-сімвалам.
    return buf;
}

char* inputFromFile(void)                                      //Прачытаць першы радок з файла ў дынамічны радок.
{
    char path[256];
    printf("Enter file path: ");
    if (scanf("%255s", path) != 1) {                           //Счытваем шлях да файла.
        while (getchar() != '\n');
        return NULL;
    }
    while (getchar() != '\n');                                 //Ачышчаем буфер пасля scanf.

    FILE* f = fopen(path, "r");
    if (f == NULL) {                                           //Файл не знойдзены або няма доступу.
        printf("Error: cannot open file '%s'\n", path);
        return NULL;
    }

    int   cap = 64;
    int   len = 0;
    char* buf = malloc(cap);
    if (buf == NULL) { fclose(f); return NULL; }

    int c;
    while ((c = fgetc(f)) != EOF && c != '\n') {               //Чытаем першы радок файла.
        buf = appendChar(buf, &len, &cap, (char)c);
        if (buf == NULL) { fclose(f); return NULL; }
    }
    fclose(f);

    buf[len] = '\0';
    if (len == 0) {                                            //Файл пусты або першы радок пусты.
        printf("Error: file is empty or first line is blank\n");
        free(buf);
        return NULL;
    }
    printf("Read from file: %s\n", buf);                       //Пацвярджаем паспяховае чытанне з файла.
    return buf;
}

int chooseInputMethod(void)                                    //Паказаць падменю і вярнуць абраны метад уводу.
{
    printf("\nInput method:\n");
    printf("  1. Keyboard\n");
    printf("  2. File\n");
    printf("Choice: ");

    int choice = 0;
    if (scanf("%d", &choice) != 1) choice = 0;                 //Абаронімся ад нелічбавага ўводу.
    while (getchar() != '\n');

    if (choice != 1 && choice != 2) {
        printf("Invalid choice, defaulting to keyboard.\n");
        return 1;                                              //Па змоўчанні выкарыстоўваем клавіятуру.
    }
    return choice;
}

int checkBrackets(const char* expr)                            //Праверыць правільнасць дужак праз стэк, вярнуць 1 або 0.
{
    Stack* top    = NULL;                                      //Стэк для захавання адкрываючых дужак.
    int           result = 1;                                  //Вынік праверкі: 1 — правільна, 0 — памылка.
    int           len    = (int)strlen(expr);

    printf("\nAnalysing: %s\n", expr);

    for (int i = 0; i < len; i++) {
        char c = expr[i];

        if (isOpen(c)) {
            push(&top, c);                                     //Адкрываючая дужка — кладзём у стэк.
            printf("  [%2d] '%c' -> pushed\n", i + 1, c);

        } else if (isClose(c)) {

            if (top == NULL) {                                 //Стэк пусты — няма пары для зачыняючай дужкі.
                printf("  [%2d] '%c' -> ERROR: no matching opening bracket\n", i + 1, c);
                result = 0;
                break;
            }

            char got = pop(&top);

            if (!isMatchingPair(got, c)) {                     //Тыпы дужак не супадаюць.
                printf("  [%2d] '%c' -> ERROR: expected closing for '%c', got '%c'\n",
                       i + 1, c, got, c);
                result = 0;
                break;
            }

            printf("  [%2d] '%c' -> matches '%c', popped\n", i + 1, c, got);
        }                                                      //Усе іншыя сімвалы (літары, лічбы, аперацыі) прапускаем.
    }

    if (result == 1 && top != NULL) {                          //Дайшлі да канца, але ёсць незачыненыя дужкі.
        printf("\nERROR: unclosed brackets left in stack:\n");
        printStack(top);                                       //Паказваем якія дужкі засталіся адкрытымі.
        result = 0;
    }

    clearStack(&top);                                          //Заўсёды ачышчаем стэк перад выхадам з функцыі.
    return result;
}

void showMenu(void)                                            //Вывесці пункты галоўнага меню на экран.
{
    printf("\n--- Bracket Checker ---\n");
    printf("  1. Check an expression\n");
    printf("  2. Exit\n");
    printf("Choice: ");
}

int getMenuChoice(void)                                        //Счытаць і вярнуць выбар карыстальніка з меню.
{
    int choice = 0;
    if (scanf("%d", &choice) != 1) {                           //Абаронімся ад нелічбавага ўводу.
        while (getchar() != '\n');
        return -1;                                             //Вяртаем -1 як прыкмету няверных дадзеных.
    }
    while (getchar() != '\n');                                 //Ачышчаем рэшту радка ўводу.
    return choice;
}

void handleCheck(void)                                         //Апрацаваць увод і запусціць праверку выразу.
{
    int method = chooseInputMethod();                          //Карыстальнік выбірае адкуль браць выраз.

    char* expr = NULL;
    if (method == 1)
        expr = inputFromKeyboard();                            //Увод з клавіятуры.
    else
        expr = inputFromFile();                                //Увод з файла.

    if (expr == NULL || expr[0] == '\0') {                     //Выраз не атрыманы — выходзім.
        printf("No expression to check.\n");
        free(expr);
        return;
    }

    int ok = checkBrackets(expr);                              //Запускаем праверку дужак.

    printf("\nResult: ");
    if (ok)
        printf("brackets are CORRECT\n");
    else
        printf("brackets are INCORRECT\n");

    free(expr);                                                //Вызваляем дынамічны радок пасля выкарыстання.
}
