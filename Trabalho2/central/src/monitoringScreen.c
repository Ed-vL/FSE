#include "../inc/monitoringScreen.h"
#include "../inc/client.h"

int startx = 0;
int starty = 0;
int L1,L2,L3,L4,A1,A2,P1,P2,S1,S2,S3,S4,S5,S6;

void getState(){
  L1 = sendMessage("ML1\0");
  L2 = sendMessage("ML2\0");
  L3 = sendMessage("ML3\0");
  L4 = sendMessage("ML4\0");
  A1 = sendMessage("MA1\0");
  A2 = sendMessage("MA2\0");
  P1 = sendMessage("MP1\0");
  P2 = sendMessage("MP2\0");
  S1 = sendMessage("MS1\0");
  S2 = sendMessage("MS2\0");
  S3 = sendMessage("MS3\0");
  S4 = sendMessage("MS4\0");
  S5 = sendMessage("MS5\0");
  S6 = sendMessage("MS6\0");
}

void MonitoringScreen(){
  createClient();
  int entry;
  
  WINDOW *P;
  initscr();
  clear();
  noecho();
  startx = (80 - WIDTH) / 2;
  starty = (24 - HEIGHT) / 2;
  P = newwin(HEIGHT, WIDTH, starty, startx);
  getState();
  halfdelay(10);
  mvprintw(1,0,"Lâmpada 01 (Cozinha): %d",L1);
  mvprintw(2,0,"Lâmpada 02 (Sala): %d",L2);
  mvprintw(3,0,"Lâmpada 03 (Quarto 01): %d",L3);
  mvprintw(4,0,"Lâmpada 04 (Quarto 02): %d",L4);
  mvprintw(5,0,"Ar-condicionado 01 (Quarto 01): %d",A1);
  mvprintw(6,0,"Ar-condicionado 02 (Quarto 02): %d",A2);
  mvprintw(7,0,"Sensor de Presença 01 (Sala): %d",P1);
  mvprintw(8,0,"Sensor de Presença 02 (Cozinha): %d",P2);
  mvprintw(9,0,"Sensor Abertura 01 (Porta Cozinha): %d",S1);
  mvprintw(10,0,"Sensor Abertura 02 (Janela Cozinha): %d",S2);
  mvprintw(11,0,"Sensor Abertura 03 (Porta Sala): %d",S3);
  mvprintw(12,0,"Sensor Abertura 04 (Janela Sala): %d",S4);
  mvprintw(13,0,"Sensor Abertura 05 (Janela Quarto 01): %d",S5);
  mvprintw(14,0,"Sensor Abertura 06 (Janela Quarto 02): %d",S6);
  do{
    entry = wgetch(P);
    mvprintw(0,0,"Pressione ESC para retornar");
    refresh();
  } while(entry != 27);
  closeClient();
}
