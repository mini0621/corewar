/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst0f_lfork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/24 16:21:32 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_lfork(t_game *game, t_process *caller, t_inst *inst)
{
	t_uc	*addr;

	if (!game || !caller || !inst)
		return ;
	addr = access_ptr(game->memdump, caller->pc,
			(int)(short)(inst->args[0].value.u_dir_val));
	if (prcs_new(game, caller->c_id, addr, game->prcs) < 0)
		return ;
	prcs_cpy((t_process *)ft_arrget(game->prcs, game->prcs->last), caller);
	if (!(game->deb_state & 64))
		return ;
	inst->args[0].value.u_dir_val = addr - game->memdump;
	deb_64_log(game, inst, caller, game->nbr_prcs - 1);
}
