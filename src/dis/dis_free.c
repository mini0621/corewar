/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 10:12:45 by mnishimo          #+#    #+#             */
/*   Updated: 2019/07/02 12:09:51 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	del_inst(void *content, size_t size)
{
	t_instr_node	*nd;

	if (size != sizeof(t_instr_node))
		return ;
	nd = (t_instr_node *)content;
	free(nd->instr);
	free(nd);
}

void	del_store(void *content, size_t size)
{
	t_inst_store	*nd;

	if (size != sizeof(t_inst_store))
		return ;
	nd = (t_inst_store *)content;
	free(nd->instr);
	free(nd);
}

int		free_all(t_dis_game *game)
{
	int		i;

	free(game->visu);
	i = 0;
	if (i < game->nbr_champs)
	{
		ft_lstdel(&(game->file[i]->instr_nodes), &del_inst);
		free(game->file[i]->output_file);
		free(game->file[i]);
		i++;
	}
	return (0);
}
