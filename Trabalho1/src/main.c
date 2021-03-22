#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include "../inc/menu.h"
#include "../inc/Gpio.h"
#include "../inc/uart.h"
#include "../inc/bme280.h"
#include "../inc/pid.h"
#include "../inc/lcd.h"
#include "../inc/screens.h"

void trataSinal(int sig){
  switch(sig){
    case SIGINT:
      closeUart();
      turnOffResistor();
      turnOffFan();
  }
}

int main(int argc, const char * argv[]) {
    signal(SIGINT,trataSinal);
    configGpio();
    openUart();
    configCsv();
    int bme = bme280Init(1, 0x76);
    if(bme < 0){
      printf("Erro ao inicializar BME280\n");
      exit(0);
    }
    setupI2C();
    menu();
   return 0;
}