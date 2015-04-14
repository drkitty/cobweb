#include "terminal_internal.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>


int main()
{
    t_init();
    /*t_reset();*/


    {
        t_save();

        struct pos bottom_right = {1024, 1024};
        t_setpos(&bottom_right);

        char extra[32];
        struct pos max = t_getpos(extra);

        t_restore();
        printf("%hu, %hu\n", max.line, max.col);
    }

    return 0;
}
