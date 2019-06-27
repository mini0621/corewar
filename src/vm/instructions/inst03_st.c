/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst03_st.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/27 13:14:46 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_st(t_game *game, t_process *caller, t_inst *inst)
{
	t_dir_type	*i;
	t_dir_type	*j;
	t_uc		*addr;

	if (!game || !caller || !inst
		|| !(i = get_arg(caller, game->memdump, &(inst->args[0]), 1)))
		return ;
	if (inst->args[1].type == e_reg
		&& !(j = get_arg(caller, game->memdump, &(inst->args[1]), 1)))
			return ;
	if (inst->args[1].type == e_reg)
		ft_memcpy(j, i, REG_SIZE);
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
