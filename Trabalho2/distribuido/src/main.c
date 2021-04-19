#include "../inc/server.h"
#include "../inc/bme280.h"
#include "../inc/gpio.h"
#include "../inc/client.h"
#include "../inc/pinWatcher.h"

int main(){
    createServer();
    createClient();
    int bme = bme280Init(1, 0x76);
    if(bme < 0){
      printf("Erro ao inicializar BME280\n");
    }
    configGpio();
    watcher();
    pause();
    closeClient();
    return 0;
}