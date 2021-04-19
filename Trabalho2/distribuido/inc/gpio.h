#ifndef _GPIO_
#define _GPIO_

#include <unistd.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#define L1_pin 0
#define L2_pin 1
#define L3_pin 2
#define L4_pin 3
#define A1_pin 23
#define A2_pin 24
#define P1_pin 6
#define P2_pin 25
#define S1_pin 21
#define S2_pin 22
#define S3_pin 26
#define S4_pin 27
#define S5_pin 28
#define S6_pin 29

void configGpio();

int toggleLight(int l);

int toggleAC(int a);

int getState(char code, int pin);

#endif