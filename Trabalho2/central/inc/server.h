#ifndef _SERVER_
#define _SERVER_

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

#define servidorPorta 10027

void TrataClienteTCP();

void createServer();

void *initServer();

void toggleAlarm();

bool getAlarm();

#endif