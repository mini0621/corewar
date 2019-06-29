/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 08:05:17 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/06/29 11:05:59 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			end_visu(t_visu *visu)
{
	delwin(visu->dump_win);
	delwin(visu->menu_win);
	if (visu->logs_win)
		delwin(visu->logs_win);
	endwin();
	use_default_colors();
}

void			update_clr(t_game *game, int dst, size_t size, int id)
{
	size_t		rd;
	t_uc		*dump;
	short		*map;
	int			i;

	i = -1;
	map = &(game->visu->clr_map[0]);
	dump = game->memdump;
	if (dst + size > MEM_SIZE)
	{
		rd = MEM_SIZE - dst;
		while (++i < (int)rd)
			map[dst + i] = 110 - id;
		i = -1;
		while (++i < (int)(size - rd))
			map[dst + i] = 110 - id;
	}
	else
		while (++i < (int)size)
			map[dst + i] = 110 - id;
}
