#include <ncurses.h>
#include <unistd.h>
#include "uart.h"
#include "pid.h"
#include "Gpio.h"

#define WIDTH 40
#define HEIGHT 10 

int startx = 0;
int starty = 0;

void PScreen(){
  WINDOW *P;
  initscr();
	clear();
	noecho();
  int entry;
  int pid = 0;
  startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;
  P = newwin(HEIGHT, WIDTH, starty, startx);
  float Internaltemp;
  float PotentiometerTemp;
  char codeI, codeP;
  codeI = 0xC1;
  codeP = 0xC2;
  openUart();
  halfdelay(10);
  do{
    entry = wgetch(P);
    mvprintw(0,0,"Pressione ESC para retornar ao menu");
    Internaltemp = getTempUart(codeI,7);
    PotentiometerTemp = getTempUart(codeP, 7);
    setReference(PotentiometerTemp);
    pid = pidControl(Internaltemp);
    mvprintw(2,2,"TI: %2.f Celsius\n",Internaltemp);
    mvprintw(3,2,"TR: %2.f Celsius\n",PotentiometerTemp);
    mvprintw(4,2,"PID: %d\n",pid);
    if(pid < 0){
      activateFan(pid);
    } else if(pid > 0) {
      activateResistor(pid);
    }
    refresh();
    sleep(1);    
  } while(entry != 27);
  closeUart();
  turnOffResistor();
  turnOffFan();
}

void TScreen(){
  WINDOW *T;
  float UserTemp;
  int pid = 0;
  initscr();
	clear();
  echo();
  mvprintw(0,0,"Informe a temperatura desejada em graus celsius: \n");
	scanw("%f",&UserTemp);
  clear();
  int entry;
  startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;
  T = newwin(HEIGHT, WIDTH, starty, startx);
  float Internaltemp;
  char codeI;
  codeI = 0xC1;
  openUart();
  noecho();
  halfdelay(10);
  do{
    entry = wgetch(T);
    mvprintw(0,0,"Pressione ESC para retornar ao menu");
    Internaltemp = getTempUart(codeI,7);
    setReference(UserTemp);
    pid = pidControl(Internaltemp);
    mvprintw(2,2,"TI: %.2f Celsius\n",Internaltemp);
    mvprintw(3,2,"TR: %.2f Celsius\n",UserTemp);
    mvprintw(4,2,"PID: %d\n",pid);
    if(pid < 0){
      activateFan(pid);
    } else if(pid > 0) {
      activateResistor(pid);
    }
    refresh();
    sleep(1);
  } while(entry != 27);
  closeUart();
  turnOffResistor();
  turnOffFan();
}