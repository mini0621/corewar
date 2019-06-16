/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst09_zjmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/16 22:48:29 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_zjmp(t_game *game, t_process *caller, t_inst *inst)
{
	int	offset;

	if (!game || !caller || !inst)
		return ;
	if (caller->carry)
	{
		offset = (int)(short)(inst->args[0].value.u_dir_val) % IDX_MOD;
		caller->pc = access_ptr(game->memdump, caller->pc, offset);
	}
	if (!(game->deb_state & 64))
		return ;
	inst->args[0].value.u_dir_val = caller->pc - game->memdump;
	deb_64_log(game, inst, caller, 0);
}
