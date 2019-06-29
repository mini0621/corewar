/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 09:49:23 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/06/29 11:42:39 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	draw_curs(t_game *game, t_visu *visu)
{
	int			cur;
	int			i;
	t_process	*p;

	cur = game->prcs->last;
	while (cur >= 0)
	{
		p = (t_process *)ft_arrget(game->prcs, cur);
		i = p->pc - game->memdump;
		wattron(visu->dump_win, COLOR_PAIR(-1 * p->c_id + 5) | A_BOLD);
		mvwprintw(visu->dump_win, i / 64 + 2, i % 64 * 3 + 9, "%.2hhX",
				game->memdump[i]);
		wattroff(visu->dump_win, COLOR_PAIR(p->c_id * -1 + 5) | A_BOLD);
		cur--;
	}
}

static int	change_clr(short p)
{
	if (!p)
		return (10);
	else if (p < 10)
		return (p);
	else
		return (p % 10 + 10);
}

void		draw_dump(t_game *game, t_visu *visu)
{
	int			i;
	int			p;

	i = -1;
	while (++i < MEM_SIZE)
	{
		if (!(i % 64))
		{
			wattron(visu->dump_win, COLOR_PAIR(16));
			mvwprintw(visu->dump_win, i / 64 + 2, 2, "%#06x", i);
			wattroff(visu->dump_win, COLOR_PAIR(16));
		}
		p = change_clr(visu->clr_map[i]);
		wattron(visu->dump_win, COLOR_PAIR(p) | A_BOLD);
		mvwprintw(visu->dump_win, i / 64 + 2, i % 64 * 3 + 9,
				"%.2hhX ", game->memdump[i]);
		wattroff(visu->dump_win, COLOR_PAIR(p) | A_BOLD);
	}
	draw_curs(game, visu);
}
