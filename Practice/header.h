#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// раблю свой уласны bool, бо ў стандартным С яго няма
typedef enum {
    FALSE = 0,                      // хлусня
    TRUE = 1                        // праўда
} Boolean;

// напрамак
typedef enum {
    ARRIVAL = 0,                    // прылёт
    DEPARTURE = 1                   // вылет
} FlightType;

// магчымыя станы рэйса на табло
typedef enum {
    ON_TIME = 0,                    // па раскладзе
    DELAYED = 1,                    // спазняецца
    BOARDING = 2,                   // пасадка (калі гэта вылет)
    DEPARTED = 3,                   // ужо вылецеў
    LANDED = 4,                     // ужо прызямліўся
    CANCELED = 5                    // адменены
} FlightStatus;

// для падзелу правоў у праграме
typedef enum {
    ROLE_PASSENGER = 0,             // можа толькі глядзець табло і шукаць
    ROLE_ADMIN = 1                  // можа дадаваць, рэдагаваць і выдаляць
} UserRole;

typedef struct {
    char username[30];              // логін карыстальніка
    char password[30];              // пароль (для курсавой хопіць радка)
    UserRole role;                  // узровень доступу
} User;

// захоўваю час асобнымі лічбамі для зручнага сартавання
typedef struct {
    int day;                        // дзень
    int month;                      // месяц
    int year;                       // год
    int hour;                       // гадзіны
    int minute;                     // хвіліны
} DateTime;

// асноўная структура аднаго рэйса
typedef struct {
    char flightNumber[10];          // нумар, напрыклад "B2-737"
    char airline[50];               // авіякампанія
    char city[50];                  // куды ляціць або адкуль прылятае
    char airplaneModel[30];         // мадэль самалёта
    
    FlightType type;                // прылёт або вылет
    DateTime scheduleTime;          // час па плане
    DateTime actualTime;            // рэальны час (важна пры затрымцы)
    FlightStatus status;            // бягучы стан рэйса
    
    char terminal;                  // літара тэрмінала (A, B, C...)
    int gate;                       // нумар гейта для пасадкі
} Flight;

// база дадзеных майго аэрапорта (дынамічны масіў)
typedef struct {
    Flight *flights;                // указальнік на масіў у памяці
    int count;                      // колькі рэйсаў рэальна запісана зараз
    int capacity;                   // на колькі месцаў выдзелена памяць
} AirportSystem;

// структура-фільтр для разумнага пошуку
// калі сцяг (use...) у TRUE, значыць улічваю гэты параметр пры адборы
typedef struct {
    Boolean useTypeFilter;          // ці шукаю па канкрэтным напрамку
    FlightType targetType;          // сам напрамак (прылёт/вылет)

    Boolean useCityFilter;          // ці шукаю па горадзе
    char targetCity[50];            // назва горада для пошуку

    Boolean useStatusFilter;        // ці шукаю па статусе
    FlightStatus targetStatus;      // сам статус (напрыклад, затрымліваюцца)
    
    Boolean useTimeFilter;          // ці шукаю па часе
    DateTime startTime;             // шукаю рэйсы толькі пасля гэтага часу
} SearchFilter;
