#pragma once


struct pos {
    short unsigned int line;
    short unsigned int col;
};


void t_init();
void t_reset();
void t_save();
void t_restore();
struct pos t_getpos(char* extra);
void t_setpos(const struct pos* pos);
