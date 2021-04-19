#include "../inc/server.h"

 

bool alarme;

void toggleAlarm(){
	alarme = !alarme;
}

bool getAlarm(){
	return alarme;
}

void triggerAlarm(){
	printf("WOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n");
	system("omxplayer ../media/alarm.mp3");
}

void TrataClienteTCP(int socketCliente) {
	
	char buffer[16];
	int tamanhoRecebido;
	int res;
	if((tamanhoRecebido = recv(socketCliente, buffer, 16, 0)) < 0)
		printf("Erro no recv()\n");
	res = buffer[0] - '0';
	printf("Recebido: %d\n",res);
    if(res){
		if(alarme){
			triggerAlarm();
		}
	}
	while (tamanhoRecebido > 0) {
		if((tamanhoRecebido = recv(socketCliente, buffer, 16, 0)) < 0){
			printf("Erro no recv()");
			}
		res = buffer[0] - '0';
		printf("Recebido: %d\n",res);
        if(res){
			if(alarme){
				triggerAlarm();
			}
		}
	}
}

void *initServer(void * arg) {
	alarme = false;
	int servidorSocket;
	int socketCliente;
	struct sockaddr_in servidorAddr;
	struct sockaddr_in clienteAddr;

	unsigned int clienteLength;

	// Abrir Socket
	if((servidorSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("falha no socker do Servidor\n");

	// Montar a estrutura sockaddr_in
	memset(&servidorAddr, 0, sizeof(servidorAddr)); // Zerando a estrutura de dados
	servidorAddr.sin_family = AF_INET;
	servidorAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servidorAddr.sin_port = htons(servidorPorta);

	// Bind
	if(bind(servidorSocket, (struct sockaddr *) &servidorAddr, sizeof(servidorAddr)) < 0)
		printf("Falha no Bind\n");

	// Listen
	if(listen(servidorSocket, 10) < 0)
		printf("Falha no Listen\n");		

	while(1) {
		clienteLength = sizeof(clienteAddr);
		if((socketCliente = accept(servidorSocket, 
			                      (struct sockaddr *) &clienteAddr, 
			                      &clienteLength)) < 0)
			printf("Falha no Accept\n");
				
		TrataClienteTCP(socketCliente);
		close(socketCliente);

	}
	close(servidorSocket);

}

void createServer(){
    pthread_t thread;
    pthread_create(&thread,NULL,&initServer,NULL);
}
