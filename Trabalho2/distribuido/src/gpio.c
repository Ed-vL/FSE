#include "../inc/gpio.h"

void configGpio(){
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
}

int pinTranslator(char cod, int num){
    switch(cod){
        case 'L':
            return num - 1;
        case 'A':
            return num + 22;
        case 'P':
            if(num == 1) return 6;
            if(num == 2) return 25;
        case 'S':
            if(num == 1) return 29;
            if(num == 2) return 31;
            if(num == 3) return 26;
            if(num == 4) return 27;
            if(num == 5) return 28;
            if(num == 6) return 29;
    }
}

int getState(char cod, int num){
    int pin = pinTranslator(cod,num);
    int state = digitalRead(pin);
    return state;
}