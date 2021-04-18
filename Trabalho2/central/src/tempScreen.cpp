#include "../inc/tempScreen.hpp"
#include "../inc/client.hpp"


void TempScreen(){
  int startx = 0;
  int starty = 0;
  createClient();
  WINDOW *P;
  initscr();
  clear();
  noecho();
  int entry, temp, umidity;
  startx = (80 - WIDTH) / 2;
  starty = (24 - HEIGHT) / 2;
  P = newwin(HEIGHT, WIDTH, starty, startx);
  halfdelay(10);
  do{
   entry = wgetch(P);
   temp = sendMessage("T");
   umidity = sendMessage("U");
   mvprintw(0,0,"Pressione ESC para retornar");
   mvprintw(2,0,"Temperatura: %d Celsius",temp);
   mvprintw(3,0,"Umidade: %d%%",umidity);
   refresh();
  } while(entry != 27);
  closeClient();
}