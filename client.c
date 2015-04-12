#include "terminal.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>


int main()
{
    t_init();
    t_reset();


    {
        struct pos pos = {1024, 1024};
        t_setpos(&pos);

        char extra[32];
        struct pos max = t_getpos(extra);

        pos.line = 0;
        pos.col = 0;
        t_setpos(&pos);
        printf("%hu, %hu\n", max.line, max.col);
    }

    return 0;
}
