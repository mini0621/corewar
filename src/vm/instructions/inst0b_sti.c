/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst0b_sti.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/29 00:34:01 by mndhlovu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			inst_sti(t_game *game, t_process *caller, t_inst *inst)
{
	short		res;
	t_dir_type	*i;
	t_uc		*addr;

	if (!game || !caller || !inst)
		return ;
	if (!(i = get_arg(caller, game->memdump, &(inst->args[1]), 1)))
		return ;
	res = (short)*i;
	if (!(i = get_arg(caller, game->memdump, &(inst->args[2]), 1)))
		return ;
	res = (res + (short)*i) % IDX_MOD;
	addr = access_ptr(game->memdump, caller->pc, (int)res);
	write_dump(game->memdump, get_arg(caller, game->memdump,
				&(inst->args[0]), 1), addr, REG_SIZE);
	if (game->visu)
		update_clr(game, addr - game->memdump, REG_SIZE, caller->c_id);
	if (!(game->deb_state & 16))
		return ;
	inst->args[1].value.u_dir_val = addr - game->memdump;
	deb_16_log(game, inst, caller, (int)*get_arg(caller,
				game->memdump, &(inst->args[0]), 1));
}
