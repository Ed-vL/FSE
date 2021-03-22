#ifndef _MENU_
#define _MENU_

#include <ncurses.h>

#define WIDTH 40
#define HEIGHT 10 

extern int startx;
extern int starty;

void print_menu(WINDOW *menu_win, int highlight);

void menu();

#endif