/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst03_st.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/21 15:01:40 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_st(t_game *game, t_process *caller, t_inst *inst)
{
	t_dir_type	*i;
	t_uc		*addr;

	if (!game || !caller || !inst)
		return ;
	i = get_arg(caller, game->memdump, &(inst->args[0]), 1);
	caller->carry = (i && !(*i)) ? 1 : 0;
	if (inst->args[1].type == e_reg)
		ft_memcpy(get_arg(caller, game->memdump,
					&(inst->args[1]), 1), i, REG_SIZE);
	else
	{
		addr = access_ptr(game->memdump, caller->pc,
					(int)(signed short)(inst->args[1].value.u_ind_val) % IDX_MOD);
		write_dump(game->memdump, i, addr, REG_SIZE);
		if (game->visu)
			update_clr(game, addr - game->memdump, REG_SIZE, caller->c_id);
	}
	if (!(game->deb_state & 16))
		return ;
	if (inst->args[1].type != e_reg)
		inst->args[1].value.u_dir_val = addr - game->memdump;
	deb_16_log(game, inst, caller, (int)*i);
}
