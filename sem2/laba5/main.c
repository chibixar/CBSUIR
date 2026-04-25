#include "header.h"

int main(void)                    //Кропка ўваходу — запускае цыкл галоўнага меню.
{
    int choice;

    do {
        showMenu();               //Паказваем меню карыстальніку.
        choice = getMenuChoice(); //Чытаем яго выбар.

        switch (choice) {
            case 1:
                handleCheck();    //Запускаем праверку выразу.
                break;
            case 2:
                printf("Goodbye!\n");
                break;
            default:
                printf("Unknown option, try again.\n");
                break;
        }

    } while (choice != 2);        //Цыкл пакуль карыстальнік не абярэ выхад.

    return EXIT_SUCCESS;
}
