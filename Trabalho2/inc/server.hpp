#ifndef _SERVER_
#define _SERVER_

#include <cstdio>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define servidorPorta 3000

void TrataClienteTCP();

void createServer();

void *initServer();
#endif