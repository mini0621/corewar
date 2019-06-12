/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst0b_sti.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/12 19:14:44 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_sti(t_game *game, t_process *caller, t_inst *inst)
{
	int			res;
	t_uc		*addr;

	if (!game || !caller || !inst)
		return ;
	res = (short)(*get_arg(caller, game->memdump, &(inst->args[1]), 1))
		+ (short)(*get_arg(caller, game->memdump, &(inst->args[2]), 1));
 	res %= IDX_MOD;
	caller->carry = (!res) ? 1 : 0;
	addr = access_ptr(game->memdump, caller->pc, (int)res % IDX_MOD);
	write_dump(game->memdump, get_arg(caller, game->memdump, &(inst->args[0]), 1), addr, REG_SIZE);
	if (!(game->deb_state))
		return ;
	inst->args[0].value.u_dir_val = (int)*get_arg(caller, game->memdump, &(inst->args[0]), 1);
	inst->args[1].value.u_dir_val = addr - game->memdump;
	get_debug(game, inst, caller, NULL);
}
