#include "../inc/server.h"
#include "../inc/bme280.h"
#include "../inc/gpio.h"

void TrataClienteTCP(int socketCliente) {
	
	char buffer[16];
    char res[16];
	int tamanhoRecebido;
    int T,H,P;
	int l,a, toggle, num;
	char cod;

	tamanhoRecebido = recv(socketCliente, buffer, 16, 0);
		
	printf("Recebido: %c %c\n",buffer[0],buffer[1]);

    switch(buffer[0]){
        case 'T':
            bme280ReadValues(&T, &P, &H);
            res[0] = T;
            send(socketCliente,res,2,0);
            break;
        case 'H':
            bme280ReadValues(&T, &P, &H);
            res[0] = H;
            send(socketCliente,res,2,0);
            break;
		case 'L':
			l = buffer[1] - '0';
			res[0] = toggleLight(l);
			send(socketCliente,res,2,0);
			break;
		case 'A':
			a = buffer[1] - '0';
			res[0] = toggleAC(a);
			send(socketCliente,res,2,0);
			break;
		case 'M'
			cod = buffer[1];
			num = buffer[2] - '0';
			res[0] = getState(cod,num);
			send(socketCliente,res,2,0);
    }
	while (tamanhoRecebido > 0) {
		if((tamanhoRecebido = recv(socketCliente, buffer, 16, 0)) < 0)
			printf("Erro no recv()\n");
        printf("Recebido: %c %c\n",buffer[0],buffer[1]);
        switch(buffer[0]){
            case 'T':
                bme280ReadValues(&T, &P, &H);
                res[0] = T;
                send(socketCliente,res,2,0);
                break;
            case 'H':
                bme280ReadValues(&T, &P, &H);
                res[0] = H;
                send(socketCliente,res,2,0);
                break;
			case 'L':
				l = buffer[1] - '0';
				res[0] = toggleLight(l);
				send(socketCliente,res,2,0);
				break;
			case 'A':
				a = buffer[1] - '0';
				res[0] = toggleAC(a);
				send(socketCliente,res,2,0);
				break;
        }
	}
}

void *initServer() {
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
		if((socketCliente = accept(servidorSocket, (struct sockaddr*) &clienteAddr, &clienteLength)) < 0)
			printf("Falha no Accept\n");

		printf("Conexão do Cliente %s\n", inet_ntoa(clienteAddr.sin_addr));
		
		TrataClienteTCP(socketCliente);
		close(socketCliente);

	}
	close(servidorSocket);

}

void createServer(){
    pthread_t thread;
    pthread_create(&thread,NULL,&initServer,NULL);
}
