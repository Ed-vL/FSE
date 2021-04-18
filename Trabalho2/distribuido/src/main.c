#include "../inc/server.h"
#include "../inc/bme280.h"
#include "../inc/Gpio.h"

int main(){
    createServer();
    while(1){
        
    }
   /* int bme = bme280Init(1, 0x76);
    if(bme < 0){
      printf("Erro ao inicializar BME280\n");
    }
    configGpio();
    */
    return 0;
}