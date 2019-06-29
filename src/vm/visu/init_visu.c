/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 14:29:51 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/29 00:47:28 by mndhlovu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		get_colors(void)
{
	start_color();
	init_color(COLOR_WHITE, 220, 220, 220);
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_BLUE);
	init_pair(6, COLOR_CYAN, COLOR_BLUE);
	init_pair(7, COLOR_CYAN, COLOR_BLUE);
	init_pair(8, COLOR_GREEN, COLOR_BLUE);
	init_pair(9, COLOR_GREEN, COLOR_BLUE);
	init_pair(10, COLOR_WHITE, COLOR_WHITE);
	init_pair(11, COLOR_BLUE, COLOR_WHITE);
	init_pair(12, COLOR_BLUE, COLOR_WHITE);
	init_pair(13, COLOR_GREEN, COLOR_WHITE);
	init_pair(14, COLOR_GREEN, COLOR_WHITE);
}

void			init_visu(t_game *game, t_visu *visu)
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	timeout(VISU_SPEED * visu->sp);
	get_colors();
	visu->dump_win = newwin(MEM_SIZE / 64 + 2, 64 * 3 + 9, 0, 0);
	if (game->deb_state)
	{
		visu->menu_win = newwin((MEM_SIZE / 64 + 2) / 2 + 1
				, 100, 0, 64 * 3 + 8);
		visu->logs_win = newwin((MEM_SIZE / 64 + 2) / 2
				, 100, (MEM_SIZE / 64 + 2) / 2, 64 * 3 + 8);
		scrollok(visu->logs_win, TRUE);
	}
	else
		visu->menu_win = newwin(MEM_SIZE / 64 + 2
				, 100, 0, 64 * 3 + 8);
	scrollok(visu->menu_win, TRUE);
	curs_set(FALSE);
	update_all(game, game->visu);
}
