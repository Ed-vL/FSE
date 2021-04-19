#include "../inc/gpio.h"

void configGpio(){
  if(wiringPiSetup() != 0){
    printf("Erro ao configurar GPIO\n");
    exit(0);
  }
  pinMode(L1_pin,OUTPUT);
  pinMode(L2_pin,OUTPUT);
  pinMode(L3_pin,OUTPUT);
  pinMode(L4_pin,OUTPUT);
  pinMode(A1_pin,OUTPUT);
  pinMode(A2_pin,OUTPUT);
  pinMode(P1_pin,INPUT);
  pinMode(P2_pin,INPUT);
  pinMode(S1_pin,INPUT);
  pinMode(S2_pin,INPUT);
  pinMode(S3_pin,INPUT);
  pinMode(S4_pin,INPUT);
  pinMode(S5_pin,INPUT);
  pinMode(S6_pin,INPUT);
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
            if(num == 1) return P1_pin;
            if(num == 2) return P2_pin;
        case 'S':
            if(num == 1) return S1_pin;
            if(num == 2) return S2_pin;
            if(num == 3) return S3_pin;
            if(num == 4) return S4_pin;
            if(num == 5) return S5_pin;
            if(num == 6) return S6_pin;
    }
}

int getState(char cod, int num){
    int pin = pinTranslator(cod,num);
    int state = digitalRead(pin);
    return state;
}