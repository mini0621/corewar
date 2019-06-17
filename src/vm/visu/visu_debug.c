/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 22:14:12 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/17 23:08:25 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	draw_debug(t_game *game, t_visu *visu)
{
	WINDOW	*win;
	size_t	i;
	int		l;
	int		pre;
	char	*ptr;

	i = 0;
	win = visu->logs_win;
	ptr = &(game->logs[0]);
	pre = 0;
	l = 1;
	while (i < game->logs_len)
	{
		if (game->logs[i] == '\n')
		{
			wattron(win, COLOR_PAIR(1));
			mvwprintw(win, l, 2, "%.*s", 10, ptr);
			wattroff(win, COLOR_PAIR(1));
			l++;
			ptr = &(game->logs[i + 1]);
			pre = 0;
			continue ;
		}
		pre++;
		i++;
	}
}
