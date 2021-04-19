#include "../inc/server.h"
#include "../inc/bme280.h"
#include "../inc/gpio.h"

int main(){
    createServer();
    int bme = bme280Init(1, 0x76);
    if(bme < 0){
      printf("Erro ao inicializar BME280\n");
    }
    configGpio();
    
    return 0;
}