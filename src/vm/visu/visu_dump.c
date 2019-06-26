/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 09:49:23 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/06/24 17:29:31 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		draw_curs(t_game *game, t_visu *visu)
{
	int		cur;
	int		i;
	WINDOW	*win;

	win = visu->dump_win;
	cur = game->prcs->last;
	while (cur >= 0)
	{
		i = ((t_process *)ft_arrget(game->prcs, cur))->pc - game->memdump;
		wattron(win, COLOR_PAIR(visu->clr_map[i % 10] + 5) | A_BOLD);
		mvwprintw(win, i / 64 + 1, i % 64 * 3 + 9, "%.2hhX", game->memdump[i]);
		wattroff(win, COLOR_PAIR(visu->clr_map[visu->clr_map[i % 10]] + 5) | A_BOLD);
		cur--;
	}
}

void	        draw_dump(t_game *game, t_visu *visu)
{
	int	i;
	int	p;
	WINDOW	*win;

	i = 0;
	win = visu->dump_win;
	while (i < MEM_SIZE)
	{
		if (!(i % 64))
		{
			wattron(win, COLOR_PAIR(6));
			mvwprintw(win, i / 64 + 1, 2, "%#06x", i);
			wattroff(win, COLOR_PAIR(6));
		}
		if ((p = (int)visu->clr_map[i]) < 10)
			wattron(win, COLOR_PAIR(p) | A_BOLD);
		else
			wattron(win, COLOR_PAIR(p % 10 + 10) | A_BOLD);
		mvwprintw(win, i / 64 + 1, i % 64 * 3 + 9, "%.2hhX ", game->memdump[i]);
		if (p < 10)
			wattroff(win, COLOR_PAIR(p) | A_BOLD);
		else
			wattroff(win, COLOR_PAIR(p % 10 + 10) | A_BOLD);
		i++;
	}
	draw_curs(game, visu);
}
