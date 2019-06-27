/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 09:49:23 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/06/27 13:32:42 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		draw_curs(t_game *game, t_visu *visu)
{
	int		cur;
	int		i;
	WINDOW	*win;
	t_process *p;

	win = visu->dump_win;
	cur = game->prcs->last;
	while (cur >= 0)
	{
		p = (t_process *)ft_arrget(game->prcs, cur);
		i = p->pc - game->memdump;
		if (p->p_id == 45)
			wattron(win, COLOR_PAIR(17) | A_BOLD);
		else
			wattron(win, COLOR_PAIR(p->c_id * -1  + 5) | A_BOLD);
		mvwprintw(win, i / 64 + 2, i % 64 * 3 + 9, "%.2hhX", game->memdump[i]);
		if (p->p_id == 45)
			wattroff(win, COLOR_PAIR(17) | A_BOLD);
		else
			wattroff(win, COLOR_PAIR(p->c_id * -1 + 5) | A_BOLD);
		cur--;
	}
}

static	int	change_clr(short p)
{
	if (!p)
		return (10);
	else if (p < 10)
		return (p);
	else
		return (p % 10 + 10);
}

void	        draw_dump(t_game *game, t_visu *visu)
{
	int	i;
	int	p;
	WINDOW	*win;

	i = 0;
	win = visu->dump_win;;
	while (i < MEM_SIZE)
	{
		if (!(i % 64))
		{
			wattron(win, COLOR_PAIR(16));
			mvwprintw(win, i / 64 + 2, 2, "%#06x", i);
			wattroff(win, COLOR_PAIR(16));
		}
		p = change_clr(visu->clr_map[i]);
		wattron(win, COLOR_PAIR(p) | A_BOLD);
		mvwprintw(win, i / 64 + 2, i % 64 * 3 + 9, "%.2hhX ", game->memdump[i]);
		wattroff(win, COLOR_PAIR(p) | A_BOLD);
		i++;
	}
	draw_curs(game, visu);
}
