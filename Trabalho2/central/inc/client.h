#ifndef _CLIENT_
#define _CLIENT_


#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define servidorPorta 3001
#define IP_Servidor "192.168.0.4"

 

void createClient();

int sendMessage(char *message);

void closeClient();

#endif