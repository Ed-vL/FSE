#include "../inc/alarmScreen.hpp"
#include "../inc/server.hpp"


char *options[] = { 
			"Alternar Alarme",
            "Voltar"
		  };
          
int n_options = sizeof(options) / sizeof(char *);
int AlarmControl = 0;
void print_options(WINDOW *menu_win, int highlight)
{
	int x, y, i;	
	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for(i = 0; i < n_options; ++i)
	{	if(highlight == i + 1) /* High light the present choice */
		{	wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", options[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", options[i]);
		++y;
	}
	wrefresh(menu_win);
}

void AlarmScreen(){
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
  mvprintw(2, 0, "Alarme Desligado");
  refresh();
  print_options(menu_win, highlight);
	while(1)
	{	c = wgetch(menu_win);
		switch(c)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = n_options;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_options)
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
		print_options(menu_win, highlight);
		if(choice != 0)
			break;
	}
  switch (choice) {
  case 1:
    toggleAlarm();
    if(AlarmControl){
        mvprintw(2, 0, "Alarme Desligado");
        AlarmControl = 0;
        refresh();
    } else {
         mvprintw(2, 0, "Alarme Ligado");
         AlarmControl = 1;
         refresh();
    }
    AlarmScreen();
	break;
  case 2:
    clear();
    break;
  }
}