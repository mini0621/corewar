/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst0b_sti.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/10 00:05:56 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_sti(t_game *game, t_process *caller, t_inst *inst)
{
	t_dir_type	res;
	t_uc		*ind;

	if (!game || !caller || !inst)
		return ;
	res = *get_arg(caller, game->memdump, &(inst->args[1]), 1)
		+ *get_arg(caller, game->memdump, &(inst->args[2]), 1);
	caller->carry = (!res) ? 1 : 0;
	ind = access_ptr(game->memdump, caller->pc, (size_t)res % IDX_MOD);
	ft_memcpy(ind, get_arg(caller, game->memdump, &(inst->args[0]), 1), REG_SIZE);
	if (!(game->deb_state))
		return ;
	inst->args[0].value.u_dir_val = ind - game->memdump;
	get_debug(game, inst, caller, NULL);
}
