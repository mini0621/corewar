/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst01_live.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/16 02:49:03 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	deb_4_log(t_game *game, int p_id, int c_id, int id)
{
	char	*tmp;
	int		l;

	tmp = NULL;
	l = ft_asprintf(&tmp, "process %i(champ %i): live for champ(%i)!\n",
			p_id, c_id, id);
	update_logs(game, &tmp, l);
}

void	inst_live(t_game *game, t_process *caller, t_inst *inst)
{
	int	i;
	int	id;

	if (!game || !caller || !inst)
		return ;
	inst->args[0].type = e_dir;
	id = *(int *)get_arg(caller, game->memdump, &(inst->args[0]), 0);
	i = 0;
	while (game->champs[i])
	{
		if (game->champs[i]->id == id)
		{
			(game->champs[i]->live_c)++;
			if (game->champs[i]->id == caller->c_id)
				caller->is_alive = 1;
			break ;
		}
		i++;
	}
	if (game->deb_state & 4)
		deb_4_log(game, caller->p_id, caller->c_id, id);
}
