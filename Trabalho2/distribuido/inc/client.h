#ifndef _CLIENTD_
#define _CLIENTD_


#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define servidorPorta 10027
#define IP_Servidor "192.168.0.53"

 

void createClient();

int sendMessage(char *message);

void closeClient();

#endif