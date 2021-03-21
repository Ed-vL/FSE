#include <unistd.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>

void turnOffFan();
void turnOffResistor();

void configGpio(){
  if(wiringPiSetup() != 0){
    printf("Erro ao configurar GPIO\n");
    exit(0);
  }

  pinMode(5,OUTPUT);
  digitalWrite(5,LOW);
  softPwmCreate(5,0,100);
  pinMode(4,OUTPUT);
  digitalWrite(4,LOW);
  softPwmCreate(4,0,100);
}

void activateFan(int pid){
  turnOffResistor();
  if(pid > -40){
    turnOffFan();
    return;
  }
  softPwmWrite(5,pid * -1);
  usleep(10000);
}


void activateResistor(int pid){
  turnOffFan();
  softPwmWrite(5,pid);
  usleep(10000);
}

void turnOffResistor(){
  softPwmWrite(4,1);
}

void turnOffFan(){
  softPwmWrite(5,1);
}