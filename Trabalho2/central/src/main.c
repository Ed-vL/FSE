#include "../inc/menu.h"
#include "../inc/server.h"

 

int main(void){
    signal(SIGPIPE, SIG_IGN);
    createServer();
    menu();
    return 0;
}