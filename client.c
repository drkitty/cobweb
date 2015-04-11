#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>


int main()
{
    {
        struct termios termios;
        if (tcgetattr(STDIN_FILENO, &termios) != 0)
            return 1;
        termios.c_iflag &= ~(INLCR | IGNCR | ICRNL);
        termios.c_lflag &= ~(ICANON | ECHO);
        termios.c_oflag &= ~(OCRNL | ONOCR | ONLRET);
        if (tcsetattr(STDIN_FILENO, TCSANOW, &termios) != 0)
            return 1;
    }

    {
        short unsigned int line;
        short unsigned int col;
        fputs("\e[6n", stdout); // DSR
        if (scanf("\e[%hu;%huR", &line, &col) < 2)
            return 1;
        printf("line = %hu, col = %hu\n", line, col);
    }

    return 0;
}
