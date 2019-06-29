/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 09:49:23 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/06/29 05:24:35 by mndhlovu         ###   ########.fr       */
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

static void			draw_header(WINDOW *win)
{
	int				count;

	count = 0;
	wprintw(win, "\n");
	wattron(win, (COLOR_PAIR(5) | A_BOLD));
	while (count < (int)(sizeof(g_header) / sizeof(g_header[0])))
		wprintw(win, "%84s\n", g_header[count++]);
	wattroff(win, (COLOR_PAIR(5) | A_BOLD));
}

static int			draw_champs(t_game *game, WINDOW *win)
{
	int				index;
	int				l;

	index = -1;
	l = 10;
	wattron(win, (COLOR_PAIR(1) | A_BOLD | A_UNDERLINE));
	mvwprintw(win, 8, 35, "Introducing contestants...\n");
	wattroff(win, (COLOR_PAIR(1) | A_BOLD | A_UNDERLINE));
	while (++index < game->nbr_champs)
	{
		wattron(win, (COLOR_PAIR(index + 1)));
		mvwprintw(win, l, 2, "Player %i, weight %i bytes"
				, game->champs[index]->n_id, game->champs[index]->prog_size);
		mvwprintw(win, l + 1, 2, "\"%s\" (\"%s\") !"
				, game->champs[index]->name, game->champs[index]->comment);
		mvwprintw(win, l + 2, 2, "last arrive process: %i, alive count: %i"
				, game->champs[index]->prcs_c, game->champs[index]->live_c);
		wattroff(win, (COLOR_PAIR(index + 1)));
		l += 4;
	}
	return (l);
}

static void			draw_debug_menu(WINDOW *win, int index)
{
	wattron(win, (COLOR_PAIR(1) | A_BOLD));
	mvwprintw(win, index++, 35, "debug mode: on   n: next cycle");
	wattroff(win, (COLOR_PAIR(1) | A_BOLD));
}

static void			draw_menu_util(t_game *game, t_visu *wind, int *index)
{
	draw_header(wind->menu_win);
	*index = draw_champs(game, wind->menu_win);
	wattron(wind->menu_win, (COLOR_PAIR(1)));
	mvwprintw(wind->menu_win, *index++, 2, "Cycle: %d", game->cycle);
	mvwprintw(wind->menu_win, *index++, 2,
			"Total Number of lives: %d Alive Calls: %d",
			game->prcs_count, game->live_count);
}

void				draw_menu(t_game *game, t_visu *wind)
{
	int				index;

	draw_menu_util(game, wind, &index);
	mvwprintw(wind->menu_win, index++, 2,
			"Cycle to die: %d, decreasing with: %d"
			, game->cycle_to_die, CYCLE_DELTA);
	wattroff(wind->menu_win, (COLOR_PAIR(1)));
	wattron(wind->menu_win, (COLOR_PAIR(1) | A_BOLD));
	if (wind->sp < 0)
		mvwprintw(wind->menu_win, index++
				, 35, "GAME PAUSED!! PRESS SPACE BAR TO CONTINUE\n");
	else
		mvwprintw(wind->menu_win, index++
				, 35, "PRESS SPACE BAR TO PAUSE\n");
	if (wind->sp > 0)
		mvwprintw(wind->menu_win, index++
				, 35, "Play interval: %i milliseconds", wind->sp * 10);
	else
		mvwprintw(wind->menu_win, index++
				, 35, "Play interval: %i milliseconds", wind->sp * (-10));
	wattroff(wind->menu_win, (COLOR_PAIR(1) | A_BOLD));
	if (game->deb_state)
		draw_debug_menu(wind->menu_win, index);
}
