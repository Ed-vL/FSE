#include "../inc/tempScreen.h"
#include "../inc/client.h"


void TempScreen(){
  int startx = 0;
  int starty = 0;
  createClient();
  WINDOW *P;
  initscr();
  clear();
  noecho();
  int entry, temp, humidity;
  startx = (80 - WIDTH) / 2;
  starty = (24 - HEIGHT) / 2;
  P = newwin(HEIGHT, WIDTH, starty, startx);
  halfdelay(10);
  do{
   entry = wgetch(P);
   temp = sendMessage("T");
   humidity = sendMessage("H");
   mvprintw(0,0,"Pressione ESC para retornar");
   mvprintw(2,0,"Temperatura: %d Celsius",temp/100);
   mvprintw(3,0,"Umidade: %d%%",humidity);
   refresh();
  } while(entry != 27);
  closeClient();
}