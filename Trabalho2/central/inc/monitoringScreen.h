#ifndef _MONITORINGSCREEN_
#define _MONITORINGSCREEN_

#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define WIDTH 40
#define HEIGHT 10 

void MonitoringScreen();

void getState();
#endif