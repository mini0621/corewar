/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_visu_output.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 09:49:23 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/07/02 09:52:30 by mndhlovu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void				dis_menu(t_dis_game *game, t_visu *wind, int p_num)
{
	wattron(wind->menu_win, (COLOR_PAIR(9) | A_BOLD | A_UNDERLINE));
	mvwprintw(wind->menu_win, 2, 40, "DISASSEMBLER");
	wattroff(wind->menu_win, (COLOR_PAIR(9) | A_BOLD | A_UNDERLINE));
	wattron(wind->menu_win, (COLOR_PAIR(8)));
	mvwprintw(wind->menu_win, 3, 2, "FILE ID %d, Size %d bytes\n"
			, p_num, game->file[p_num]->prog_size);
	mvwprintw(wind->menu_win, 4, 2, "File: %s\n", game->file[p_num]->file_name);
	mvwprintw(wind->menu_win, 5, 2, "Saving as: %s\n"
			, game->file[p_num]->output_file);
	mvwprintw(wind->menu_win, 6, 2, "Waiting list: %d\n"
			, (game->nbr_champs - p_num) - 1);
	mvwprintw(wind->menu_win, 8, 20, "CLICK LEFT TO CONTINUE");
	mvwprintw(wind->menu_win, 10, 25, "mndhlovu, mnishimo, sunakim, allefebv");
	wattroff(wind->menu_win, (COLOR_PAIR(8)));
	wattron(wind->raw_win, (COLOR_PAIR(9) | A_BOLD | A_UNDERLINE));
	mvwprintw(wind->raw_win, 2, 80, "COREWAR FILE\n");
	wattroff(wind->raw_win, (COLOR_PAIR(9) | A_BOLD | A_UNDERLINE));
	wattron(wind->raw_win, (COLOR_PAIR(9) | A_BOLD));
	mvwprintw(wind->raw_win, 4, 1, "PLAYER NAME: %s, COMMENT: (%s)"
			, game->file[p_num]->name, game->file[p_num]->comment);
	wattroff(wind->raw_win, (COLOR_PAIR(9) | A_BOLD));
}

static void				dis_visu_raw(t_dis_game *game, t_visu *win)
{
	int					index;
	int					pr;
	t_ucc				*ptr;

	index = 0;
	ptr = game->dismemdump;
	pr = 0;
	while (index < CHAMP_MAX_SIZE)
	{
		if (!(index % 64))
		{
			wattron(win->raw_win, COLOR_PAIR(6));
			mvwprintw(win->raw_win, (index / 64) + 5, 1
					, "%#06x", ptr - game->dismemdump);
			wattroff(win->raw_win, COLOR_PAIR(6));
			pr++;
		}
		wattron(win->raw_win, COLOR_PAIR(7) | A_BOLD);
		mvwprintw(win->raw_win, (index / 64) + 5
				, index % 64 * 3 + 9, "%.2hhX ", *ptr);
		wattroff(win->raw_win, COLOR_PAIR(7) | A_BOLD);
		wattroff(win->raw_win, COLOR_PAIR(7) | A_BOLD);
		index++;
	}
}

void					dis_visu_out(t_dis_game *game
						, t_visu *win, int p_num)
{
	wattron(win->out_win, (COLOR_PAIR(9) | A_BOLD | A_UNDERLINE));
	mvwprintw(win->out_win, 2, 80, "SOURCE FILE");
	wattroff(win->out_win, (COLOR_PAIR(9) | A_BOLD | A_UNDERLINE));
	wattron(win->out_win, (COLOR_PAIR(9) | A_BOLD));
	mvwprintw(win->out_win, 3, 2, ".name %s\n", game->file[p_num]->name);
	mvwprintw(win->out_win, 4, 2, ".comment %s\n"
			, game->file[p_num]->comment);
	wattroff(win->out_win, (COLOR_PAIR(9) | A_BOLD));
	dis_print_node(win, game);
}

void					dis_visu_launcher(t_dis_game *game
						, t_visu *visu, int p_num)
{
	werase(visu->menu_win);
	werase(visu->raw_win);
	werase(visu->out_win);
	dis_menu(game, visu, p_num);
	dis_visu_raw(game, visu);
	dis_visu_out(game, visu, p_num);
	scrollok(visu->out_win, TRUE);
	wattron(visu->out_win, COLOR_PAIR(5));
	wattron(visu->raw_win, COLOR_PAIR(5));
	wattron(visu->menu_win, COLOR_PAIR(5));
	wborder(visu->raw_win, '*', '*', '*', '*', '*', '*', '*', '*');
	wborder(visu->out_win, '*', '*', '*', '*', '*', '*', '*', '*');
	wborder(visu->menu_win, '*', '*', '*', '*', '*', '*', '*', '*');
	wattroff(visu->out_win, COLOR_PAIR(5));
	wattroff(visu->raw_win, COLOR_PAIR(5));
	wattroff(visu->menu_win, COLOR_PAIR(5));
	refresh();
	wnoutrefresh(visu->menu_win);
	wnoutrefresh(visu->raw_win);
	wnoutrefresh(visu->out_win);
	doupdate();
}
