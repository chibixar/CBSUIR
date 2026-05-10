#include "header.h"

int main() {
    HospitalQueue queue = {NULL, NULL, 0};                                  // Стварэнне і ініцыялізацыя пустой чаргі.

    initialize_system(&queue);                                              // Першапачатковая загрузка бальніц і пацыентаў.

    int running = 1;
    while (running) {                                                       // Галоўны інтэрактыўны цыкл праграмы.
        running = process_user_command(&queue);
    }

    free_queue(&queue);                                                     // Ачыстка памяці перад завяршэннем працы.
    printf("System memory cleared. Goodbye!\n");
    
    return 0;
}