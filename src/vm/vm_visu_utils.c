/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_visu_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 08:05:17 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/06/11 17:15:50 by mndhlovu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void                vm_init_visu(t_game *game, t_visu *visu)
{
    initscr();
	//cbreak();
    noecho();
	keypad(stdscr, TRUE);
	// nodelay(stdscr, TRUE);
    start_color();
    init_color(COLOR_WHITE, 220, 220, 220);
	init_pair(0, COLOR_GREEN, COLOR_BLACK);
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	init_pair(6, COLOR_YELLOW, COLOR_BLACK);
	init_pair(7, COLOR_BLUE, COLOR_WHITE);
    init_pair(8, COLOR_GREEN, COLOR_WHITE);
	visu->dump_win = newwin(MEM_SIZE / 64 + 2, 64 * 3 + 9, 0, 0);
	visu->menu_win = newwin(MEM_SIZE / 64 + 2, 100, 0, 64 * 3 + 8);
	curs_set(FALSE);
	visu_launcher(game, game->visu, 1);
}

void			end_visu(t_visu *visu)
{
	delwin(visu->dump_win);
	delwin(visu->menu_win);
	endwin();
}

static int		restart_all(t_game *game, int *pause)
{
	end_visu(game->visu);
	vm_init_visu(game, game->visu);
	*pause = 1;
	return (1);
}

int			output(t_game *game, int *pause)
{
	int			c;

	c = getch();
	if (c == 32)
	{
		*pause = (*pause) ? 0 : 1;
		game->pause = *pause;
	}
	else if (c == KEY_ENTER)
		return (0);
	else if (c == KEY_RESIZE)
		return (restart_all(game, pause));
	visu_launcher(game, game->visu, *pause);
	return (1);
}