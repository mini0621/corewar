/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_visu_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 08:05:17 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/07/01 17:41:39 by mndhlovu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				dis_init_visu(t_game *game, t_visu *visu, int pl_num)
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	start_color();
	init_color(COLOR_WHITE, 220, 220, 220);
	init_pair(0, COLOR_GREEN, COLOR_BLACK);
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_WHITE);
	init_pair(6, COLOR_YELLOW, COLOR_BLACK);
	init_pair(7, COLOR_BLUE, COLOR_WHITE);
	init_pair(8, COLOR_GREEN, COLOR_WHITE);
	init_pair(9, COLOR_WHITE, COLOR_BLACK);
	visu->raw_win = newwin(CHAMP_MAX_SIZE / 64 + 6, 64 * 3 + 9, 0, 0);
	visu->out_win = newwin(game->length + 8, 64 * 3 + 9, 12, 0);
	visu->menu_win = newwin(CHAMP_MAX_SIZE / 64 + 3, 100, 0, 64 * 3 + 9);
	curs_set(FALSE);
	dis_visu_launcher(game, game->visu, pl_num);
}

void				dis_end_visu(t_visu *visu)
{
	delwin(visu->raw_win);
	delwin(visu->menu_win);
	delwin(visu->out_win);
	endwin();
}

static void			dis_restart_all(t_game *game, int p_num)
{
	dis_end_visu(game->visu);
	dis_init_visu(game, game->visu, p_num);
}

static int			dis_output_util(t_game *game, int *flag, int *p_num)
{
	ft_bzero(&(game->dismemdump[0]), CHAMP_MAX_SIZE * sizeof(t_uc));
	*p_num = vm_load_player(game);
	if (*p_num == -1)
	{
		*flag = 0;
		dis_end_visu(game->visu);
		return (0);
	}
	game->length = 0;
	return (1);
}

int					dis_output(t_game *game, int p_num, int *flag)
{
	if (getch() == KEY_RIGHT)
	{
		if (!(dis_output_util(game, flag, &p_num)))
			return (0);
		if (!dis_multi_util(game, p_num))
			return (dis_catch_error(-2, NULL));
		dis_sub_handler(game, p_num);
		if (!(dis_write_output(game, p_num)))
		{
			*flag = 0;
			dis_end_visu(game->visu);
			return (0);
		}
		dis_restart_all(game, p_num);
	}
	if (!(dis_write_output(game, p_num)))
	{
		*flag = 0;
		dis_end_visu(game->visu);
		return (0);
	}
	dis_init_visu(game, game->visu, p_num);
	return (1);
}
