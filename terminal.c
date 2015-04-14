#include "terminal.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>


void t_init()
{
    struct termios termios;
    if (tcgetattr(STDIN_FILENO, &termios) != 0)
        exit(1);
    termios.c_lflag &= ~(ICANON | ECHO);
    termios.c_oflag &= ~(OCRNL | ONOCR | ONLRET);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &termios) != 0)
        exit(1);
}


void t_reset()
{
    fputs("\ec", stdout);
}


void t_save()
{
    fputs("\e7", stdout);
}


void t_restore()
{
    fputs("\e8", stdout);
}


struct pos t_getpos(char* extra)
{
    enum {
        ESC,
        BRACKET,
        LINE,
        COL,
        DONE,
    } state = ESC;
    struct pos pos = {0, 0};
    char* first;

    fputs("\e[6n", stdout);
    while (state != DONE) {
        int c = getchar();
        if (c == EOF)
            exit(1);

        *(extra++) = c;

        if (c == 0x1B) {
            state = ESC + 1;
            first = extra - 1;
        } else if (state == BRACKET) {
            if (c == '[')
                state++;
            else
                state = ESC;
        } else if (state == LINE) {
            if (c >= '0' && c <= '9')
                pos.line = pos.line * 10 + c - '0';
            else if (c == ';')
                state++;
            else
                state = ESC;
        } else if (state == COL) {
            if (c >= '0' && c <= '9')
                pos.col = pos.col * 10 + c - '0';
            else if (c == 'R')
                state++;
            else
                state = ESC;
        }
    }

    *first = '\0';

    return pos;
}


void t_setpos(const struct pos* pos)
{
    printf("\e[%hu;%huH", pos->line, pos->col);
}
