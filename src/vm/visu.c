/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:42:02 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/06 21:32:19 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	update_all(t_game *game, t_visu *visu, int pause)
{
	print_dump(visu->dump_win, game->memdump);
	print_menu(visu->menu_win, game, pause);
	box(visu->dump_win, '*' , '*');
	box(visu->menu_win, '*' , '*');
	refresh();
	wnoutrefresh(visu->menu_win);
	wnoutrefresh(visu->dump_win);
	doupdate();
}

void	restart_all(t_game *game, int *pause)
{
	end_visu(game->visu);
	init_visu(game, game->visu);
	*pause = 1;
}

static void visu_color()
{
	start_color();
	init_pair(CLR_P1, 1, 0);
	//init_color();
	//init_pair(CLR_C1, 1, 2);
	
}

void	init_visu(t_game *game, t_visu *visu)
{
	initscr();
	visu_color();
	cbreak();
	scrollok(stdscr, TRUE);
	keypad(stdscr, TRUE);
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr,TRUE);
	scrollok(visu->dump_win, TRUE);
	visu->dump_win = newwin(MEM_SIZE / 64 + 2, 64 * 3 + 9, 0, 0);
	visu->menu_win = newwin(MEM_SIZE / 64 + 2, 100, 0, 64 * 3 + 8);
	update_all(game, game->visu, 1);
}

void	end_visu(t_visu *visu)
{
	delwin(visu->dump_win);
	delwin(visu->menu_win);
	endwin();
}
