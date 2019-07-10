/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst0e_lldi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/07/10 15:30:37 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			inst_lldi(t_game *game, t_process *caller, t_inst *inst)
{
	short		res;
	t_uc		*ind;
	t_dir_type	*i;

	if (!game || !caller || !inst)
		return ;
	if (!(i = get_arg(caller, game->memdump, &(inst->args[0]), 0)))
		return ;
	res = (short)*i;
	if (!(i = get_arg(caller, game->memdump, &(inst->args[1]), 0)))
		return ;
	res += (short)*i;
	ind = access_ptr(game->memdump, caller->pc, (int)res);
	if (!(i = get_arg(caller, game->memdump, &(inst->args[2]), 1)))
		return ;
	read_dump(game->memdump, ind, i, REG_SIZE);
	caller->carry = (!caller->regs[inst->args[2].value.u_reg_val]) ? 1 : 0;
	if (game->deb_state & 8)
		deb_8_log(game, inst, caller, (int)(ind - game->memdump));
}
