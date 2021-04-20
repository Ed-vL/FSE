#include "../inc/server.h"

 

bool alarme;

void toggleAlarm(){
	alarme = !alarme;
}

bool getAlarm(){
	return alarme;
}

void triggerAlarm(){
	char command[1000], cwd[500];
	strcpy(command, "aplay ");
	getcwd(cwd, sizeof(cwd));
	strcat(command, cwd);
	strcat(command, "/alarm.mp3");
	system(command);
}

FILE *t;
void configCsv(){
    t = fopen("Relatorio.csv", "w+");
	fprintf(t,"Data/Hora, Evento\n");
}

void TrataClienteTCP(int socketCliente) {
	time_t rawtime;
  	struct tm * timeinfo;
	time (&rawtime);
    timeinfo = localtime (&rawtime);
	char buffer[16];
	char confirm[16];

	int tamanhoRecebido;
	int res;
	if((tamanhoRecebido = recv(socketCliente, buffer, 16, 0)) < 0){
		printf("Erro no recv()\n");
		confirm[0] = 0;
	} else {
		confirm[0] = 1;
	}
	send(socketCliente,confirm,2,0);
	res = buffer[0] - '0';
    if(res){
		if(alarme){
			triggerAlarm();
		    fprintf(t, "%d-%d-%d %d:%d:%d,Alarme disparado\n", 
    		timeinfo->tm_mday,timeinfo->tm_mon+1,timeinfo->tm_year+1900,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
		}
	}
	while (tamanhoRecebido > 0) {
		time (&rawtime);
    	timeinfo = localtime (&rawtime);
		if((tamanhoRecebido = recv(socketCliente, buffer, 16, 0)) < 0){
			printf("Erro no recv()\n");
			confirm[0] = 0;
		} else {
			confirm[0] = 1;
		}
		send(socketCliente,confirm,2,0);
		res = buffer[0] - '0';
        if(res){
			if(alarme){
				triggerAlarm();
		    	fprintf(t, "%d-%d-%d %d:%d:%d,Alarme disparado\n", 
    			timeinfo->tm_mday,timeinfo->tm_mon+1,timeinfo->tm_year+1900,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
			}
		}
	}
	fclose(t);
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
