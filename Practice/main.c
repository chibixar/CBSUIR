// Праграма "Аэрапорт": сістэма кіравання рэйсамі.
// Структуры дадзеных: стэк (гісторыя змяненняў/undo),
//                     чарга (рэйсы на пацвярджэнне),
//                     бінарнае дрэва пошуку (хуткі пошук па нумары).
// Увод: клавіятура / txt-файл / бінарны файл.
// Вывад: экран + txt-файл або бінарны файл.

#include "header.h"

int main(void)
{
    AirportSystem sys;
    sys_init(&sys);                                                       // Ініцыялізацыя пустой сістэмы.

    printf("==========================================\n");
    printf("      AIRPORT INFORMATION SYSTEM v1.0    \n");
    printf("==========================================\n\n");

    User currentUser;                                                     // Аўтэнтыфікацыя карыстальніка.
    int  attempts = 0;
    printf("=== Login ===\n");
    printf("  (admin/admin123  or  passenger/pass)\n\n");
    while (!auth_login(&currentUser))
    {
        attempts++;
        if (attempts >= 3)
        {
            printf("  Too many failed attempts. Exiting.\n");
            sys_free(&sys);
            return 1;
        }
        printf("  Invalid credentials. Try again (%d/3).\n", attempts);
    }
    printf("\n  Welcome, %s!\n", currentUser.username);

    printf("\n=== Initial Data Load ===\n");                             // Першапачатковая загрузка дадзеных.
    input_choose(&sys);

    menu_main(&sys, &currentUser);                                        // Галоўнае меню праграмы.

    if (sys.count > 0)                                                    // Прапанова захаваць перад выхадам.
    {
        printf("\nSave data before exit? (1=yes, 0=no): ");
        int save; GetInt(&save);
        if (save) output_choose(&sys);
    }

    sys_free(&sys);                                                       // Вызваляем усю памяць перад выхадам.
    return 0;
}
