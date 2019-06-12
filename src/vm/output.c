/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:42:02 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/08 22:10:20 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void print_dump(WINDOW *win, t_uc *dump)
{
	t_uc	*ptr;
	int		i;
	int		j;

	ptr = dump;
	i = 0;
	while (i < MEM_SIZE)
	{
		if (!(i % 64))
			mvwprintw(win, i / 64 + 1 , 2, "%#06x", ptr - dump);
		mvwprintw(win, i / 64 + 1, i % 64 * 3 + 9, "%.2hhX ", *ptr);
		ptr++;
		i++;
	}
}

void	print_menu(WINDOW *win, t_game *game, int pause, int c)
{
	mvwprintw(game->visu->menu_win, 2, 5, "COREWAR");
	if (pause)
		mvwprintw(game->visu->menu_win, 3, 5, "PAUSED ");
	else
		mvwprintw(game->visu->menu_win, 3, 5, "PRESS SPACE to PAUSE");	
	wattron(win, A_BOLD | COLOR_PAIR(1));
	mvwprintw(game->visu->menu_win, 5, 5, "P1: hey %d", c);
	wattroff(win, A_BOLD | COLOR_PAIR(1));
	wattron(win, CLR_P2);
	mvwprintw(game->visu->menu_win, 8, 5, "P2: yay");
	wattroff(win, CLR_P2);
}

void	output(t_game *game, int *pause)
{
	int	c;

	c = getch();
	if (c == 32)
	{
		*pause = (*pause) ? 0 : 1;
	}
	else if (c == KEY_RESIZE)
		return (restart_all(game, pause));
	update_all(game, game->visu, *pause, c);
}
