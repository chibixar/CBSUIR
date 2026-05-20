#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef HEADER_H
#define HEADER_H

// ===================== КАНСТАНТЫ =====================
#define MAX_FILENAME   100
#define MAX_FLIGHTS    1024                                  // Максімальная колькасць рэйсаў у сістэме.

// ===================== ПЕРАЛІЧЭННІ =====================

typedef enum { FALSE = 0, TRUE = 1 } Boolean;               // Уласны булеан, бо ў C89/C90 яго няма.

typedef enum {
    ARRIVAL   = 0,                                          // Прылёт.
    DEPARTURE = 1                                           // Вылет.
} FlightType;

typedef enum {
    ON_TIME  = 0,                                           // Па раскладзе.
    DELAYED  = 1,                                           // Спазняецца.
    BOARDING = 2,                                           // Пасадка (вылет).
    DEPARTED = 3,                                           // Ужо вылецеў.
    LANDED   = 4,                                           // Ужо прызямліўся.
    CANCELED = 5                                            // Адменены.
} FlightStatus;

typedef enum {
    ROLE_PASSENGER = 0,                                     // Толькі прагляд.
    ROLE_ADMIN     = 1                                      // Поўны доступ.
} UserRole;

// ===================== СТРУКТУРЫ =====================

typedef struct {
    char     username[30];                                  // Лагін.
    char     password[30];                                  // Пароль.
    UserRole role;                                          // Узровень доступу.
} User;

typedef struct {                                            // Час захоўваецца асобнымі палямі — зручна для сартавання.
    int day;
    int month;
    int year;
    int hour;
    int minute;
} DateTime;

typedef struct {
    char         flightNumber[10];                          // Нумар рэйса, напрыклад "B2-737".
    char         airline[50];                               // Авіякампанія.
    char         city[50];                                  // Горад прылёту або вылету.
    char         airplaneModel[30];                         // Мадэль самалёта.

    FlightType   type;                                      // Прылёт або вылет.
    DateTime     scheduleTime;                              // Час па плане.
    DateTime     actualTime;                                // Рэальны час з улікам затрымкі.
    FlightStatus status;                                    // Бягучы стан.

    char         terminal;                                  // Літара тэрмінала (A, B, C...).
    int          gate;                                      // Нумар гейта.
} Flight;

typedef struct {                                            // Фільтр для разумнага пошуку.
    Boolean    useTypeFilter;
    FlightType targetType;

    Boolean      useCityFilter;
    char         targetCity[50];

    Boolean      useStatusFilter;
    FlightStatus targetStatus;

    Boolean  useTimeFilter;
    DateTime startTime;
} SearchFilter;

// ==================== СТЭК ====================

typedef struct StackNode {
    Flight          data;
    struct StackNode *next;
} StackNode;

typedef struct {
    StackNode *top;
    int        size;
} Stack;

// ==================== ЧАРГА ====================

typedef struct QueueNode {
    Flight           data;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *head;
    QueueNode *tail;
    int        size;
} Queue;

// ==================== БІНАРНАЕ ДРЭВА ====================

typedef struct TreeNode {
    Flight           data;
    struct TreeNode  *left;
    struct TreeNode  *right;
} TreeNode;

// ==================== АСНОЎНАЯ СІСТЭМА ====================

typedef struct {
    Flight flights[MAX_FLIGHTS];                            // Асноўны масіў усіх рэйсаў.
    int    count;                                           // Колькасць рэйсаў зараз.
    Stack  history;                                         // Стэк для адмены дзеянняў.
    Queue  pendingQueue;                                    // Чарга рэйсаў на пацвярджэнне.
    TreeNode *searchTree;                                   // BST для хуткага пошуку.
} AirportSystem;

// ==================== ПРАТАТЫПЫ ФУНКЦЫЙ ====================

void         read_line(char *buf, int size, FILE *f);
void         rewind_stdin(void);
void         GetInt(int *value);
void         GetChar(char *value);
void         clear_screen(void);
void         press_enter(void);

void         datetime_print(DateTime dt);
int          datetime_compare(DateTime a, DateTime b);
void         datetime_input(DateTime *dt);

const char  *flight_type_str(FlightType t);
const char  *flight_status_str(FlightStatus s);
FlightType   parse_flight_type(const char *s);
FlightStatus parse_flight_status(const char *s);

void         flight_print_header(void);
void         flight_print_row(int idx, const Flight *f);
void         flight_input_keyboard(Flight *f);
int          flight_parse_line(const char *line, Flight *f);
Boolean      flight_matches_filter(const Flight *f, const SearchFilter *filter);

void         stack_init(Stack *s);
void         stack_push(Stack *s, Flight f);
Boolean      stack_pop(Stack *s, Flight *out);
Boolean      stack_peek(const Stack *s, Flight *out);
void         stack_free(Stack *s);

void         queue_init(Queue *q);
void         queue_enqueue(Queue *q, Flight f);
Boolean      queue_dequeue(Queue *q, Flight *out);
void         queue_free(Queue *q);
void         queue_print(const Queue *q);

TreeNode    *bst_insert(TreeNode *root, Flight f);
TreeNode    *bst_search(TreeNode *root, const char *flightNumber);
TreeNode    *bst_delete(TreeNode *root, const char *flightNumber);
void         bst_inorder_print(TreeNode *root);
void         bst_free(TreeNode *root);

void         sys_init(AirportSystem *sys);
void         sys_free(AirportSystem *sys);
void         sys_add_flight(AirportSystem *sys, Flight f);
Boolean      sys_find_by_number(AirportSystem *sys, const char *num, int *outIdx);
void         sys_delete_flight(AirportSystem *sys, int idx);
void         sys_update_status(AirportSystem *sys, int idx, FlightStatus newStatus);
void         sys_sort_by_schedule(AirportSystem *sys);
void         sys_print_all(AirportSystem *sys);
void         sys_search(AirportSystem *sys, const SearchFilter *filter);
void         sys_undo(AirportSystem *sys);

void         input_choose(AirportSystem *sys);
void         input_keyboard(AirportSystem *sys);
void         input_txt_file(AirportSystem *sys);
void         input_binary_file(AirportSystem *sys);

void         output_choose(AirportSystem *sys);
void         output_txt_file(AirportSystem *sys, const char *filename);
void         output_binary_file(AirportSystem *sys, const char *filename);

void         menu_main(AirportSystem *sys, User *currentUser);
void         menu_search(AirportSystem *sys);
void         menu_add(AirportSystem *sys);
void         menu_edit(AirportSystem *sys);
void         menu_delete(AirportSystem *sys);
void         menu_pending_queue(AirportSystem *sys);
void         menu_bst(AirportSystem *sys);

Boolean      auth_login(User *out);

#endif
