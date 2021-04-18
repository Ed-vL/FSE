#include "../inc/Gpio.h"

/*void configGpio(){
  if(wiringPiSetup() != 0){
    printf("Erro ao configurar GPIO\n");
    exit(0);
  }
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(23,OUTPUT);
  pinMode(24,OUTPUT);
  pinMode(6,INPUT);
  pinMode(25,INPUT);
  pinMode(21,INPUT);
  pinMode(22,INPUT);
  pinMode(26,INPUT);
  pinMode(27,INPUT);
  pinMode(28,INPUT);
  pinMode(29,INPUT);
}


int toggleLight(int l){
    int state;
    int pin = l - 1;
    state = digitalRead(pin);
    if(state){
        digitalWrite(pin,0);
        return 1;
    } else {
        digitalWrite(pin,1);
        return 1;
    }
    return 0;
}

int toggleAC(int a)
{
    int state;
    int pin = a + 22;
    state = digitalRead(pin);
    if(state){
        digitalWrite(pin,0);
        return 1;
    } else {
        digitalWrite(pin,1);
        return 1;
    }
    return 0;
}*/
