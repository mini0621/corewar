/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis_visu_extr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 14:15:14 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/07/02 11:35:08 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void					dis_print_node(t_visu *win, t_dis_game *game)
{
	int					index;
	t_list				*inst;

	index = 0;
	if (!(inst = game->store))
		return ;
	wattron(win->out_win, (COLOR_PAIR(9) | A_BOLD));
	while (inst)
	{
		mvwprintw(win->out_win, 5 + index, 2, "%s",((t_inst_store *)(inst->content))->instr);
		inst = inst->next;
		index++;
	}
	wattroff(win->out_win, (COLOR_PAIR(9) | A_BOLD));
}

void					dis_debug(t_dis_game *game, int p_num)
{
	int					index;
	t_list				*inst;

	index = 0;
	if (!(inst = game->store))
		return ;
	ft_printf("%sSTART OF PLAYER FILE: %s\n"
			, CLR_RED, game->file[p_num]->file_name);
	ft_printf(".name\t\t\"%s\"\n", game->file[p_num]->name);
	ft_printf(".comment\t\"%s\"\n\n", game->file[p_num]->comment);
	while (inst)
	{
		ft_printf("%s%s", CLR_GREEN, ((t_inst_store *)(inst->content))->instr);
		inst = inst->next;
		index++;
	}
	ft_printf("%sEND OF PLAYER FILE: %s\n"
			, CLR_RED, game->file[p_num]->file_name);
}
