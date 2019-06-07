/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst01_live.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/07 16:13:24 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_live(t_game *game, t_process *caller, t_inst *inst)
{
	t_champ		*p;
	t_dir_type	id;

	ft_printf("live!\n");
	if (!game || !caller || !inst)
		return ;
	id = *get_arg(caller, game->memdump, &(inst->args[0]), 0);
	p = game->champs[0];
	while (p)
	{
		if (p->id == id)
		{
			p->live_c++;
			if (p->id == caller->c_id)
				caller->is_alive = 1;
			break ;
		}
		p++;
	}
}
