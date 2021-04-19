#include "../inc/alarmScreen.h"
#include "../inc/server.h"


char *option[] = { 
			"Alternar Alarme",
            "Voltar"
		  };
          
int n_option = sizeof(option) / sizeof(char *);

void clearLin(int y)
{
    move(y, 0);
    clrtoeol();
}

void print_option(WINDOW *menu_win, int highlight)
{
	int x, y, i;	
	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for(i = 0; i < n_option; ++i)
	{	if(highlight == i + 1)
		{	wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", option[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", option[i]);
		++y;
	}
	wrefresh(menu_win);
}

void AlarmScreen(){
  bool AlarmControl = getAlarm();
  int startx = 0;
  int starty = 0;
  WINDOW *menu_win;
  int highlight = 1;
  int choice = 0;
  int c;
  initscr();
  noecho();
  cbreak();
  startx = (80 - WIDTH) / 2;
  starty = (24 - HEIGHT) / 2;
  menu_win = newwin(HEIGHT, WIDTH, starty, startx);
  keypad(menu_win, TRUE);
  mvprintw(0, 0, "Use as setas do teclado para navegar, presisone Enter para selecionar");
  if(!AlarmControl){
	clearLin(2);
    mvprintw(2, 0, "Alarme Desligado");   
  } else {
	clearLin(2);
    mvprintw(2, 0, "Alarme Ligado");
  }
  refresh();
  print_option(menu_win, highlight);
	while(1)
	{	c = wgetch(menu_win);
		switch(c)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = n_option;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_option)
					highlight = 1;
				else 
					++highlight;
				break;
			case 10:
				choice = highlight;
				break;
			default:
				refresh();
				break;
		}
		print_option(menu_win, highlight);
		if(choice != 0)
			break;
	}
  switch (choice) {
  case 1:
    toggleAlarm();
    AlarmScreen();
	break;
  case 2:
    clear();
    break;
  }
}