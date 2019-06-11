/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst03_st.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/11 01:25:40 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_st(t_game *game, t_process *caller, t_inst *inst)
{
	t_dir_type	*i;

	if (!game || !caller || !inst)
		return ;
	i = get_arg(caller, game->memdump, &(inst->args[0]), 1);
	caller->carry = (i && !(*i)) ? 1 : 0;
	if (inst->args[1].type == e_reg)
		ft_memcpy(get_arg(caller, game->memdump,
					&(inst->args[2]), 1), i, REG_SIZE);
	else
		write_dump(game->memdump, i, access_ptr(game->memdump, caller->pc,
					(int)(short)(inst->args[2].value.u_ind_val)), REG_SIZE);
	if (!game->deb_state)
		return ;
	inst->args[0].value.u_dir_val = *i;
	if (inst->args[1].type != e_reg)
		inst->args[1].value.u_dir_val =
			access_ptr(game->memdump, caller->pc,
				(int)(short)(inst->args[2].value.u_ind_val)) - game->memdump;
	get_debug(game, inst, caller, NULL);
}
