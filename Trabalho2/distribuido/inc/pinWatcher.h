#ifndef _PINWATCHER_
#define _PINWATCHER_

#include <unistd.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#define P1_pin 6
#define P2_pin 25
#define S1_pin 21
#define S2_pin 22
#define S3_pin 26
#define S4_pin 27
#define S5_pin 28
#define S6_pin 29

int watcher();

#endif