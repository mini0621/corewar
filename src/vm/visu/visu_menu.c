/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 09:49:23 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/06/17 22:32:30 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static char const	*g_header[] =
{
	"######  ####### ###### #######  ##    ####    ###      ##     #######",
	"###     #     # ###### ###      ###   ####   ####     ####    #######",
	"###     #     # ###    ######   ####  ####  #####    ##  ##   ###    ",
	"###     #     # ###    ###      #################   ########  ###    ",
	"####### ####### ###    #######  #################  ########## ###    "
};

static void		draw_header(WINDOW *win)
{
	int	count;

	count = 0;
	wprintw(win, "\n");
	wattron(win, (COLOR_PAIR(5) | A_BOLD));
	while (count < (int)(sizeof(g_header) / sizeof(g_header[0])))
		wprintw(win, "%84s\n", g_header[count++]);
	wattroff(win, (COLOR_PAIR(5) | A_BOLD));

}

static int		draw_champs(t_game *game, WINDOW *win)
{
	int	index;
	
	index = -1;
	wattron(win, (COLOR_PAIR(1) | A_BOLD | A_UNDERLINE));
	mvwprintw(win, 8, 35, "Introducing contestants...\n");
	wattroff(win, (COLOR_PAIR(1) | A_BOLD | A_UNDERLINE));
	while (++index < game->nbr_champs)
	{
		wattron(win, (COLOR_PAIR(index + 1)));
		mvwprintw(win,10 + index, 2, "Player %i, weight %i bytes, \"%s\" (\"%s\") !\n",(-1 * game->champs[index]->id), game->champs[index]->prog_size, game->champs[index]->name, game->champs[index]->comment);
		wattroff(win, (COLOR_PAIR(index + 1)));
	}
	return (index);
}

static void		draw_debug_menu(WINDOW *win)
{
		wattron(win, (COLOR_PAIR(1) | A_BOLD));
		mvwprintw(win, 6, 35, "debug mode: on");
		mvwprintw(win, 22, 35, "PRESS ENTER TO GET NEXT_CYCLE");
		wattroff(win, (COLOR_PAIR(1) | A_BOLD));
}

void            draw_menu(t_game *game, t_visu *wind, int pause)
{
	int	index;

	draw_header(wind->menu_win);
	index = draw_champs(game, wind->menu_win);
	wattron(wind->menu_win, (COLOR_PAIR(1)));
	mvwprintw(wind->menu_win,11 + index, 2, "Cycle: %d", game->cycle);
	mvwprintw(wind->menu_win, 12 + index, 2,
		"Total Number of lives: %d Alive Calls: %d",
		game->prcs_count, game->live_count);
	mvwprintw(wind->menu_win, 13 + index, 2,
			"Decrease cycle to die with: %d", CYCLE_DELTA);
	wattroff(wind->menu_win, (COLOR_PAIR(1)));
	wattron(wind->menu_win, (COLOR_PAIR(1) | A_BOLD));
	if (pause)
		mvwprintw(wind->menu_win, 20, 35, "GAME PAUSED!! PRESS SPACE BAR TO CONTINUE\n");
	else
		mvwprintw(wind->menu_win, 20, 35, "PRESS SPACE BAR TO PAUSE\n");
	wattroff(wind->menu_win, (COLOR_PAIR(1) | A_BOLD));
	if (game->deb_state)
		draw_debug_menu(wind->menu_win);
}
