#ifndef _SERVERD_
#define _SERVERD_

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define servidorPorta 3001

void TrataClienteTCP();

void createServer();

void *initServer();

#endif