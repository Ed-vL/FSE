#ifndef _ACTIONINGSCREEN_
#define _ACTIONINGSCREEN_

#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

void ActionScreen();

void print_options(WINDOW *menu_win, int highlight);

#endif