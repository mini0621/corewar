/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 22:14:12 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/29 11:13:09 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		draw_debug(t_game *game, t_visu *visu)
{
	int		l;
	char	*start;
	char	*end;

	start = &(game->logs[0]);
	l = 3;
	wattron(visu->logs_win, COLOR_PAIR(18));
	while ((end = ft_strchr(start, '\n')) && end != start)
	{
		*end = '\0';
		mvwprintw(visu->logs_win, l, 5, "%s", start);
		*end = '\n';
		start = end + 1;
		l++;
	}
	wattroff(visu->logs_win, COLOR_PAIR(18));
}
