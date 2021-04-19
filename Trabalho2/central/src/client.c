#include "../inc/client.h"

int clientSocket;

void closeClient(){
    close(clientSocket);
}

int sendMessage(char *message){
    char buffer[16];
	unsigned int tamanhoMensagem;
	int bytesRecebidos;
	int res;
    tamanhoMensagem = strlen(message);-
	if(send(clientSocket, message, tamanhoMensagem, 0) != tamanhoMensagem)
		printf("Erro no envio: numero de bytes enviados diferente do esperado\n");

    if((bytesRecebidos = recv(clientSocket, buffer, 16-1, 0)) <= 0)
		printf("Não recebeu o total de bytes enviados\n");
    
	res = buffer[0];
    return res;
}

void createClient() {

	struct sockaddr_in servidorAddr;


	// Criar Socket
	if((clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("Erro no socket()\n");

	// Construir struct sockaddr_in
	memset(&servidorAddr, 0, sizeof(servidorAddr)); // Zerando a estrutura de dados
	servidorAddr.sin_family = AF_INET;
	servidorAddr.sin_addr.s_addr = inet_addr(IP_Servidor);
	servidorAddr.sin_port = htons(servidorPorta);

	// Connect
	if(connect(clientSocket, (struct sockaddr *) &servidorAddr, sizeof(servidorAddr)) < 0)
		printf("Erro no connect()\n");

}
