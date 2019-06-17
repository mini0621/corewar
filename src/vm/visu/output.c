/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 08:05:17 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/06/17 23:04:53 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		restart_all(t_game *game, int *pause)
{
	end_visu(game->visu);
	init_visu(game, game->visu);
	*pause = 1;
	return (1);
}

void	update_all(t_game *game, t_visu *visu, int pause)
{
	werase(visu->menu_win);
	werase(visu->dump_win);
	if (game->deb_state)
		werase(visu->logs_win);
	draw_menu(game, visu, pause);
	draw_dump(game, visu);
	if (game->deb_state)
		draw_debug(game, visu);
	wattron(visu->dump_win, COLOR_PAIR(10));
	wattron(visu->menu_win, COLOR_PAIR(10));
	if (game->deb_state)
		wattron(visu->logs_win, COLOR_PAIR(10));
	wborder(visu->dump_win, '*', '*', '*', '*', '*', '*', '*', '*');
	wborder(visu->menu_win, '*', '*', '*', '*', '*', '*', '*', '*');
	if (game->deb_state)
		wborder(visu->logs_win, '*', '*', '*', '*', '*', '*', '*', '*');
	wattroff(visu->dump_win, COLOR_PAIR(10));
	wattroff(visu->menu_win, COLOR_PAIR(10));
	if (game->deb_state)
		wattroff(visu->logs_win, COLOR_PAIR(10));
	refresh();
	wnoutrefresh(visu->menu_win);
	wnoutrefresh(visu->dump_win);
	if (game->deb_state)
		wnoutrefresh(visu->logs_win);
	doupdate();
}

int			output(t_game *game, int *pause)
{
	int			c;

	*pause = (*pause == 2) ? 1 : *pause;
	c = getch();
	if (c == 32)
		*pause = (*pause) ? 0 : 1;
	else if (c == KEY_ENTER && game->deb_state)
		*pause = 2;
	else if (c == KEY_RESIZE)
		return (restart_all(game, pause));
	update_all(game, game->visu, *pause);
	return (1);
}
