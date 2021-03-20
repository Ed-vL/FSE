#include <unistd.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>

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

void setFan(int pid){
  if(pid > -40)
    return;
  softPwmWrite(5,pid * -1);
  usleep(100000);
}


void setResistor(int pid){
  softPwmWrite(5,pid);
  usleep(100000);
}

void turnOff(){
  softPwmWrite(4,0);
  softPwmWrite(5,0);
}