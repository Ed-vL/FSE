#include "../inc/menu.h"
#include "../inc/server.h"
#include <signal.h>
 

int main(void){
    signal(SIGPIPE, SIG_IGN);
    createServer();
    menu();
    return 0;
}