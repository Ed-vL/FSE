#include "../inc/actionScreen.hpp"
#include "../inc/client.hpp"


char *options[] = { 
			"Lâmpada 01 (Cozinha)",
			"Lâmpada 02 (Sala)",
            "Lâmpada 03 (Quarto 01)",
			"Lâmpada 04 (Quarto 02)",
            "Ar-Condicionado 01 (Quarto 01)",
            "Ar-Condicionado 02 (Quarto 02)",
            "Voltar"
		  };

int n_options = sizeof(options) / sizeof(char *);
int L1control = 0,L2control = 0, L3control = 0, L4control = 0, A1control = 0, A2control = 0;
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

void ActionScreen(){
  int startx = 0;
  int starty = 0;
  char * message;
  WINDOW *menu_win;
  int highlight = 1;
  int choice = 0;
  int c, res;
  initscr();
  noecho();
  cbreak();
  startx = (80 - WIDTH) / 2;
  starty = (24 - HEIGHT) / 2;
  menu_win = newwin(HEIGHT, WIDTH, starty, startx);
  keypad(menu_win, TRUE);
  mvprintw(0, 0, "Use as setas do teclado para navegar, presisone Enter para acionar o aparelho desejado");
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
    res = sendMessage("L1\0");
    if(res){
        if(!L1control){
            mvprintw(1, 0,"Lâmpada 01 acionada!");
            refresh();
            L1control = 1;
        } else {
            mvprintw(1, 0,"Lâmpada 01 desligada!");
            refresh();
            L1control = 0;
        }
    }
    ActionScreen();
	break;
  case 2:
    res = sendMessage("L2\0");
    if(res){
        if(!L2control){
            mvprintw(2, 0,"Lâmpada 02 acionada!");
            refresh();
            L2control = 1;
        } else {
            mvprintw(2, 0,"Lâmpada 02 desligada!");
            refresh();
            L2control = 0;
        }
    }
    ActionScreen();
	break;
  case 3:
    res = sendMessage("L3\0");
    if(res){
        if(!L3control){
            mvprintw(3, 0,"Lâmpada 03 acionada!");
            refresh();
            L3control = 1;
        } else {
            mvprintw(3, 0,"Lâmpada 03 desligada!");
            refresh();
            L3control = 0;
        }
    }
    ActionScreen();
	break;
  case 4:
    res = sendMessage("L4\0");
    if(res){
        if(!L4control){
            mvprintw(4, 0,"Lâmpada 04 acionada!");
            refresh();
            L4control = 1;
        } else {
            mvprintw(4, 0,"Lâmpada 04 desligada!");
            refresh();
            L4control = 0;
        }
    }
    ActionScreen();
	break;

  case 5:
    res = sendMessage("A1\0");
    if(res){
        if(!A1control){
            mvprintw(5, 0,"Ar-Condicionado 01 acionada!");
            refresh();
            A1control = 1;
        } else {
            mvprintw(5, 0,"Ar-Condicionado 01 desligada!");
            refresh();
            A1control = 0;
        }
    }
    ActionScreen();
	break;
  case 6:
    res = sendMessage("A2\0");
    if(res){
        if(!A2control){
            mvprintw(6, 0,"Ar-Condicionado 02 acionada!");
            refresh();
            A2control = 1;
        } else {
            mvprintw(6, 0,"Ar-Condicionado 02 desligada!");
            refresh();
            A2control = 0;
        }
    }
    ActionScreen();
	break;
  case 7:
    closeClient();
    clear();
    break;
  }
}