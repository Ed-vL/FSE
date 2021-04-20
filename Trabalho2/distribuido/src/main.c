#include "../inc/server.h"
#include "../inc/bme280.h"
#include "../inc/gpio.h"
#include "../inc/client.h"
#include "../inc/pinWatcher.h"
#include <signal.h>

int main(){
    signal(SIGPIPE, SIG_IGN);
    createServer();
    int bme = bme280Init(1, 0x76);
    if(bme < 0){
      printf("Erro ao inicializar BME280\n");
    }
    configGpio();
    createClient();
    watcher();
    pause();
    closeClient();
    return 0;
}