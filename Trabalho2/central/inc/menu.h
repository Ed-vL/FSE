#ifndef _MENU_
#define _MENU_

#include <ncurses.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define WIDTH 45
#define HEIGHT 10 

extern int startx;
extern int starty;

void print_menu(WINDOW *menu_win, int highlight);

void menu();

#endif