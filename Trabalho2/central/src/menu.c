#include "../inc/menu.h"
#include "../inc/monitoringScreen.h"
#include "../inc/actionScreen.h"
#include "../inc/client.h"
#include "../inc/tempScreen.h"
#include "../inc/alarmScreen.h"

char *choices[] = { 
			"Monitorar Portas, Janelas e Lâmpadas",
			"Monitorar Temperatura e umidade",
            "Acionar aparelhos",
			"Configurar Alarme",
            "Sair"
		  };
int n_choices = sizeof(choices) / sizeof(char *);

void menu()
{	WINDOW *menu_win;
	int highlight = 1;
	int choice = 0;
	int c;

	initscr();
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;
		
	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win, TRUE);
	mvprintw(0, 0, "Use as setas do teclado para navegar, presisone Enter para escolher uma opcao");
	refresh();
	print_menu(menu_win, highlight);
	while(1)
	{	c = wgetch(menu_win);
		switch(c)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = n_choices;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices)
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
		print_menu(menu_win, highlight);
		if(choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}
  switch (choice) {
  case 1:
    MonitoringScreen();
    menu();
	break;
  case 2:
  	clear();
	TempScreen();
	menu();
	break;
  case 3:
  	clear();
	createClient();
    ActionScreen();
	menu();
  case 4:
	clear();
    AlarmScreen();
	menu();
  case 5:
    clear();
	erase();
    endwin();
	break;
  }

}


void print_menu(WINDOW *menu_win, int highlight)
{
	int x, y, i;	


	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for(i = 0; i < n_choices; ++i)
	{	if(highlight == i + 1) /* High light the present choice */
		{	wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", choices[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		++y;
	}
	wrefresh(menu_win);
}