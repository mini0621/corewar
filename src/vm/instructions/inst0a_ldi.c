/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst0a_ldi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/11 00:22:05 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_ldi(t_game *game, t_process *caller, t_inst *inst)
{
	short	res;
	t_uc	*ind;
	
	if (!game || !caller || !inst)
		return ;
	res = (short)(*get_arg(caller, game->memdump, &(inst->args[0]), 1))
		+ (short)(*get_arg(caller, game->memdump, &(inst->args[1]), 1));
	caller->carry = (!res) ? 1 : 0;
	ind = access_ptr(game->memdump, caller->pc, (int)res % IDX_MOD);
	read_dump(game->memdump, ind, get_arg(caller, game->memdump, &(inst->args[2]), 1), REG_SIZE);
	if (!(game->deb_state))
		return ;
	inst->args[0].value.u_dir_val = ind - game->memdump;
	get_debug(game, inst, caller, NULL);
	
}
