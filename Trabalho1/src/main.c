#include <stdio.h>
#include "../inc/menu.h"
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void trataSinal(int sig){
  switch(sig){
    case SIGINT:
      closeUart();
      turnOff();
  }
}

int main(int argc, const char * argv[]) {
    signal(SIGINT,trataSinal);
    configGpio();
    menu();
   return 0;
}