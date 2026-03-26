#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void rewind_linux(void)
{
    int c;
    while((c=getchar()) != '\n' && c != EOF); // Чытанне сімвалаў да канца радка або канца файла.
}