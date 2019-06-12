/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_visu_output.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 09:49:23 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/06/11 17:15:32 by mndhlovu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static char const	*g_header[] =
{
	"######  ####### ###### #######  ##    ####    ###      ##     #######",
	"###     #     # ###### ###      ###   ####   ####     ####    #######",
	"###     #     # ###    ######   ####  ####  #####    ##  ##   ###",
	"###     #     # ###    ###      #################   ########  ###",
	"####### ####### ###    #######  #################  ########## ###"
};

static void            vm_menu(t_game *game, t_visu *wind, int pause)
{
	int         		index;
	int					count;

	index = -1;
	count = 0;
	wprintw(wind->menu_win, "\n");
	wattron(wind->menu_win, (COLOR_PAIR(5) | A_BOLD));
	while (count < (int)(sizeof(g_header) / sizeof(g_header[0])))
		wprintw(wind->menu_win, "              %s\n", g_header[count++]);
	wattroff(wind->menu_win, (COLOR_PAIR(5) | A_BOLD));
	wattron(wind->menu_win, (COLOR_PAIR(8) | A_BOLD | A_UNDERLINE));
	mvwprintw(wind->menu_win, 8, 35, "Introducing contestants...\n");
	wattroff(wind->menu_win, (COLOR_PAIR(8) | A_BOLD | A_UNDERLINE));
	while (++index < game->nbr_champs)
	{
		wattron(wind->menu_win, (COLOR_PAIR(index + 1)));
		mvwprintw(wind->menu_win,10 + index, 2, "Player %i, weight %i bytes, \"%s\" (\"%s\") !\n",(-1 * game->champs[index]->id), game->champs[index]->prog_size, game->champs[index]->name, game->champs[index]->comment);
		wattroff(wind->menu_win, (COLOR_PAIR(1)));
	}
	wattron(wind->menu_win, (COLOR_PAIR(8)));
	mvwprintw(wind->menu_win,10 + index + 1, 2, "Cycle: %d, Total Number of lives: %d \
	Alive Calls: %d Decrease cycle to die with: %d\n", game->cycle, NBR_LIVE, game->live_count, CYCLE_DELTA);
	wattroff(wind->menu_win, (COLOR_PAIR(8)));
	if (pause)
	{
		wattron(wind->menu_win, (COLOR_PAIR(5) | A_BOLD));
		mvwprintw(wind->menu_win, 15, 35, "GAME PAUSED!! PRESS SPACE BAR TO CONTINUE\n");
		wattroff(wind->menu_win, (COLOR_PAIR(8) | A_BOLD));
	}
	else
	{
		wattron(wind->menu_win, (COLOR_PAIR(5) | A_BOLD));
		mvwprintw(wind->menu_win, 15, 35, "PRESS SPACE BAR TO PAUSE\n");
		wattroff(wind->menu_win, (COLOR_PAIR(8) | A_BOLD));
	}
}

static void	        vm_visu_extr(t_game *game, t_visu *win)
{
	int         index;
	int			pr;
	t_uc	*ptr;

	index = 0;
	ptr = game->memdump;
	pr = 0;
	while (index < MEM_SIZE)
	{
		if (!(index % 64))
		{
			wattron(win->dump_win, COLOR_PAIR(6));
			mvwprintw(win->dump_win, index / 64 + 1, 2, "%#06x", ptr - game->memdump);
			wattroff(win->dump_win, COLOR_PAIR(6));
			pr++;
		}
		wattron(win->dump_win, COLOR_PAIR(7) | A_BOLD);
		mvwprintw(win->dump_win, index / 64 + 1, index % 64 * 3 + 9, "%.2hhX ", *ptr);
		wattroff(win->dump_win, COLOR_PAIR(7) | A_BOLD);
		ptr++;
		index++;
	}	
}

void	        vm_visu_default(t_game *game, t_visu *win)
{
	int         index;
	int			pr;
	t_uc	*ptr;

	index = 0;
	ptr = game->memdump;
	pr = 0;
	while (index < MEM_SIZE)
	{
		if (!(index % 64))
		{
			wattron(win->dump_win, COLOR_PAIR(6));
			mvwprintw(win->dump_win, index / 64 + 1, 2, "%#06x", ptr - game->memdump);
			wattroff(win->dump_win, COLOR_PAIR(6));
			pr++;
		}
		wattron(win->dump_win, COLOR_PAIR(5) | A_BOLD);
		mvwprintw(win->dump_win, index / 64 + 1, index % 64 * 3 + 9, "%.2hhX ", *ptr);
		wattroff(win->dump_win, COLOR_PAIR(5) | A_BOLD);
		ptr++;
		index++;
	};
}

void	        visu_launcher(t_game *game, t_visu *visu, int pause)
{
	werase(visu->menu_win);
	werase(visu->dump_win);
	vm_menu(game, visu, pause);
	vm_visu_extr(game, visu);
	box(visu->dump_win, '*' , '*');
	box(visu->menu_win, '*' , '*');
	refresh();
	wnoutrefresh(visu->menu_win);
	wnoutrefresh(visu->dump_win);
	doupdate();
}




