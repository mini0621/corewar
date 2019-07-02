/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis_gen_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 08:29:22 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/07/02 08:48:13 by mndhlovu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void					dis_sub_handler(t_dis_game *game, int p_num)
{
	t_instr_node		*node;
	int					index;

	node = game->file[p_num]->instr_nodes;
	index = 0;
	if (node != NULL)
	{
		while (node)
		{
			dis_get_instr(game, node);
			node = node->next;
			index++;
		}
	}
	game->file[p_num]->dis_state = 1;
}

int						dis_write_output(t_dis_game *game, int p_num)
{
	int					fd;
	t_inst_store		*inst;

	if (!(inst = game->store))
		return (0);
	if ((fd = open(game->file[p_num]->output_file
					, O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
		return (dis_catch_error(IO_ERROR, game->file[p_num]->output_file));
	ft_dprintf(fd, ".name\t\t\"%s\"\n", game->file[p_num]->name);
	ft_dprintf(fd, ".comment\t\"%s\"\n\n", game->file[p_num]->comment);
	while (inst)
	{
		ft_dprintf(fd, "%s", inst->instr);
		inst = inst->next;
	}
	if ((fd = close(fd)) < 0)
		return (dis_catch_error(IO_ERROR, game->file[p_num]->output_file));
	ft_printf("%s File successfully created\n"
			, game->file[p_num]->output_file);
	return (1);
}
