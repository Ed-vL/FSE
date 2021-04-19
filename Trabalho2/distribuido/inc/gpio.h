#ifndef _GPIO_
#define _GPIO_

#include <unistd.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

void configGpio();

int toggleLight(int l);

int toggleAC(int a);

int getState(char code, int pin);

#endif