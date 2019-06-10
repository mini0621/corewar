/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst01_live.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/10 00:09:37 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
	if (!(game->deb_state))
		return ;
	inst->args[0].value.u_dir_val = (t_dir_type)id;
	get_debug(game, inst, caller, NULL);
}
