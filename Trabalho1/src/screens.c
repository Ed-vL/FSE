#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include "../inc/uart.h"
#include "../inc/pid.h"
#include "../inc/Gpio.h"
#include "../inc/bme280.h"
#include "../inc/screens.h"
#include "../inc/lcd.h"
#include <time.h>

#define WIDTH 40
#define HEIGHT 10 

int startx = 0;
int starty = 0;
FILE *f;
void configCsv(){
  f = fopen("Relatorio.csv", "w+");
  fprintf(f,"Data/Hora, TR, TI, TE, PID\n");
}

void PScreen(){
  time_t rawtime;
  struct tm * timeinfo;
  WINDOW *P;
  initscr();
	clear();
	noecho();
  int entry, TE,PA,HA;
  int pid = 0;
  startx = (80 - WIDTH) / 2;
  starty = (24 - HEIGHT) / 2;
  P = newwin(HEIGHT, WIDTH, starty, startx);
  float Internaltemp, FTE;
  float PotentiometerTemp;
  char codeI, codeP;
  codeI = 0xC1;
  codeP = 0xC2;
  halfdelay(10);
  do{
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    entry = wgetch(P);
    mvprintw(0,0,"Pressione ESC para retornar ao menu");
    Internaltemp = getTempUart(codeI,7);
    PotentiometerTemp = getTempUart(codeP, 7);
    bme280ReadValues(&TE, &PA, &HA);
    FTE = (float)(TE/100);
    setReference(PotentiometerTemp);
    pid = pidControl(Internaltemp);
    mvprintw(2,2,"TI: %.2f Celsius\n",Internaltemp);
    mvprintw(3,2,"TR: %.2f Celsius\n",PotentiometerTemp);
    mvprintw(4,2,"TE: %d Celsius\n",TE/100);
    mvprintw(5,2,"PID: %d\n",pid);
    mvprintw(9,2,"Modo selecionado: Potenciometro");
    lcdLoc(LINE1);
    typeln("TR: ");
    typeFloat(PotentiometerTemp);
    typeln(" TI: ");
    typeFloat(Internaltemp);
    lcdLoc(LINE2);
    typeln("TE: ");
    typeFloat(FTE);
    fprintf(f, "%d-%d-%d %d:%d:%d,%.2f,%.2f,%d,%d%%\n", 
    timeinfo->tm_mday,timeinfo->tm_mon+1,timeinfo->tm_year+1900,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec,PotentiometerTemp,Internaltemp,TE/100,pid);
    if(pid < 0){
      activateFan(pid);
    } else if(pid > 0) {
      activateResistor(pid);
    }
    refresh();
    sleep(1);    
  } while(entry != 27);
  turnOffResistor();
  turnOffFan();
}

void TScreen(){
  time_t rawtime;
  struct tm * timeinfo;
  
  WINDOW *T;
  float UserTemp, FTE;
  int pid = 0;
  initscr();
	clear();
  echo();
  mvprintw(0,0,"Informe a temperatura desejada em graus celsius: \n");
	scanw("%f",&UserTemp);
  clear();
  int entry, TE,PA,HA;
  startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;
  T = newwin(HEIGHT, WIDTH, starty, startx);
  float Internaltemp;
  char codeI;
  codeI = 0xC1;
  noecho();
  halfdelay(10);
  do{
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    entry = wgetch(T);
    mvprintw(0,0,"Pressione ESC para retornar ao menu");
    Internaltemp = getTempUart(codeI,7);
    setReference(UserTemp);
    pid = pidControl(Internaltemp);
    bme280ReadValues(&TE, &PA, &HA);
    FTE = (float)(TE/100);
    mvprintw(2,2,"TI: %.2f Celsius\n",Internaltemp);
    mvprintw(3,2,"TR: %.2f Celsius\n",UserTemp);
    mvprintw(4,2,"TE: %d Celsius\n",TE/100);
    mvprintw(5,2,"PID: %d\n",pid);
    mvprintw(9,2,"Modo selecionado: Teclado");
    lcdLoc(LINE1);
    typeln("TR: ");
    typeFloat(UserTemp);
    typeln(" TI: ");
    typeFloat(Internaltemp);
    lcdLoc(LINE2);
    typeln("TE: ");
    typeFloat(FTE);
    fprintf(f, "%d-%d-%d %d:%d:%d,%.2f,%.2f,%d,%d%%\n", 
    timeinfo->tm_mday,timeinfo->tm_mon+1,timeinfo->tm_year+1900,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec,UserTemp,Internaltemp,TE/100,pid);
    if(pid < 0){
      activateFan(pid);
    } else if(pid > 0) {
      activateResistor(pid);
    }
    refresh();
    sleep(1);
  } while(entry != 27);
  turnOffResistor();
  turnOffFan();
}