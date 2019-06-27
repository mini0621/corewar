/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 14:29:51 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/27 12:08:48 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	color_conv(short c, short r, short g, short b)
{
	init_color(COLORS - c, (int)(r * 1000 / 255), (int)(g * 1000 / 255),
			(int)(b * 1000 / 255));
}

static void	get_colors(void)
{
	start_color();
	color_conv(11, 255 , 184, 184);
	color_conv(12, 249, 255, 155);
	color_conv(13, 68, 219, 223);
	color_conv(14, 181, 255, 159);
	color_conv(15, 197, 17, 98);
	color_conv(16, 245, 127, 23);
	color_conv(17, 1, 87, 155);
	color_conv(18, 27, 94, 32);
	color_conv(19, 255, 235, 238);
	color_conv(20, 255, 253, 231);
	color_conv(21, 225, 245, 254);
	color_conv(22, 232, 245, 233);
	color_conv(23, 0, 135, 68);
	color_conv(24, 205, 220, 57);
	color_conv(1, 180, 180, 180);
	color_conv(2, 0, 40, 0);
	color_conv(3, 244, 67, 54);
}

static void	get_pairs(void)
{
	init_pair(1, COLORS - 11, COLOR_BLACK);
	init_pair(2, COLORS - 12, COLOR_BLACK); // champ 2
	init_pair(3, COLORS - 13, COLOR_BLACK); //champ 3
	init_pair(4, COLORS - 14, COLOR_BLACK); //champ 4
	init_pair(5, COLOR_BLACK, COLORS - 1); //defalt pc cursor
	init_pair(6, COLORS - 15, COLORS - 19); // pc of champ 1
	init_pair(7, COLORS - 16, COLORS - 20); // pc of champ 2
	init_pair(8, COLORS - 17, COLORS - 21); // pc of champ 3
	init_pair(9, COLORS - 18, COLORS - 22); // pc of champ 4
	init_pair(10, COLORS - 1, COLOR_BLACK); //defalt memdump
	init_pair(11, COLORS - 15, COLOR_BLACK); // new written by champ 1
	init_pair(12, COLORS - 16, COLOR_BLACK); // new written by champ 1
	init_pair(13, COLORS - 17, COLOR_BLACK); // new written by champ 1
	init_pair(14, COLORS - 18, COLOR_BLACK); // new written by champ 1
	init_pair(15, COLORS - 24, COLOR_BLACK); // main2
	init_pair(16, COLORS - 23, COLOR_BLACK); // main
	init_pair(17, COLORS - 2, COLORS - 2); //box
	init_pair(18, COLORS - 3, COLOR_BLACK); //box
}

void	init_visu(t_game *game, t_visu *visu)
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	timeout(VISU_SPEED * visu->sp);
	get_colors();
	get_pairs();
	visu->dump_win = newwin(MEM_SIZE / 64 + 4, 64 * 3 + 10, 0, 0);
	if (game->deb_state)
	{
		visu->menu_win = newwin((MEM_SIZE / 64 + 4) / 2 + 2
				, 100, 0, 64 * 3 + 10);
		visu->logs_win = newwin((MEM_SIZE / 64 + 4) / 2
				, 100, (MEM_SIZE / 64 + 2) / 2 + 1, 64 * 3 + 10);
		scrollok(visu->logs_win, TRUE);
	}
	else
		visu->menu_win = newwin(MEM_SIZE / 64 + 4
				, 100, 0, 64 * 3 + 10);
	scrollok(visu->menu_win, TRUE);
	curs_set(FALSE);
	update_all(game, game->visu);
}
