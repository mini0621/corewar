/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 08:05:17 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/06/26 22:17:58 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


static int	change_timeout(t_game *game, int delay)
{
	game->visu->sp = delay;
	timeout(VISU_SPEED * game->visu->sp);
	update_all(game, game->visu);
	return (0);
}

static int		restart_all(t_game *game)
{
	end_visu(game->visu);
	init_visu(game, game->visu);
	change_timeout(game, -1);
	return (0);
}

void	update_all(t_game *game, t_visu *visu)
{
	werase(visu->menu_win);
	werase(visu->dump_win);
	if (game->deb_state)
		werase(visu->logs_win);
	draw_menu(game, visu);
	draw_dump(game, visu);
	if (game->deb_state)
		draw_debug(game, visu);
	wattron(visu->dump_win, COLOR_PAIR(17));
	wattron(visu->menu_win, COLOR_PAIR(17));
	if (game->deb_state)
		wattron(visu->logs_win, COLOR_PAIR(17));
	wborder(visu->dump_win, '*', '*', '*', '*', '*', '*', '*', '*');
	wborder(visu->menu_win, '*', '*', '*', '*', '*', '*', '*', '*');
	if (game->deb_state)
		wborder(visu->logs_win, '*', '*', '*', '*', '*', '*', '*', '*');
	wattroff(visu->dump_win, COLOR_PAIR(17));
	wattroff(visu->menu_win, COLOR_PAIR(17));
	if (game->deb_state)
		wattroff(visu->logs_win, COLOR_PAIR(17));
	refresh();
	wnoutrefresh(visu->menu_win);
	wnoutrefresh(visu->dump_win);
	if (game->deb_state)
		wnoutrefresh(visu->logs_win);
	doupdate();
}

int			output(t_game *game)
{
	int			c;

	c = getch();
	if (c == 32)
		change_timeout(game, -1 * game->visu->sp);
	else if (c == 'n' && game->deb_state)
		change_timeout(game, -1);
	else if (c == KEY_RIGHT && (game->visu->sp <= 1000 && game->visu->sp >= -1000))
		return (change_timeout(game, 2 * game->visu->sp));
	else if (c == KEY_LEFT && (game->visu->sp > 1 || game->visu->sp < -1))
		return (change_timeout(game, game->visu->sp / 2));
	else if (c == KEY_RESIZE)
		return (restart_all(game));
	else if (c > 0)
		return (0);
	update_all(game, game->visu);
	return (1);
}
