#ifndef _ACTIONINGSCREEN_
#define _ACTIONINGSCREEN_

#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define WIDTH 40
#define HEIGHT 10 

void ActionScreen();

void print_options(WINDOW *menu_win, int highlight);

#endif