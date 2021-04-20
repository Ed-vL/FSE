#ifndef _SERVERD_
#define _SERVERD_

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define servidorPorta 10127

void TrataClienteTCP();

void createServer();

void *initServer();

#endif