/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst0b_sti.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/11 01:25:42 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_sti(t_game *game, t_process *caller, t_inst *inst)
{
	t_dir_type	res;
	t_uc		*addr;
	t_dir_type	val;

	if (!game || !caller || !inst)
		return ;
	res = (short)(*get_arg(caller, game->memdump, &(inst->args[0]), 1))
 	 		+ (short)(*get_arg(caller, game->memdump, &(inst->args[1]), 1));
	caller->carry = (!res) ? 1 : 0;
	addr = access_ptr(game->memdump, caller->pc, (int)res % IDX_MOD);
	read_dump(game->memdump, addr, &val, REG_SIZE);
	if (inst->args[2].type == e_reg)
		ft_memcpy(get_arg(caller, game->memdump,
					&(inst->args[2]), 1), &val, REG_SIZE);
	else
		write_dump(game->memdump, &val, access_ptr(game->memdump, caller->pc,
					(int)(short)(inst->args[2].value.u_ind_val)), REG_SIZE);
	if (!(game->deb_state))
		return ;
	inst->args[0].value.u_dir_val = addr - game->memdump;
	if (inst->args[2].type != e_reg)
		inst->args[1].value.u_dir_val = access_ptr(game->memdump, caller->pc,
				(int)(short)(inst->args[2].value.u_ind_val)) - game->memdump;
	get_debug(game, inst, caller, NULL);
}
