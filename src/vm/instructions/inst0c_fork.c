/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst0c_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/16 23:50:35 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_fork(t_game *game, t_process *caller, t_inst *inst)
{
	t_list	*new;
	t_uc	*addr;

	if (!game || !caller || !inst)
		return ;
	if (!(new = prcs_new(game, caller->c_id)))
		return ;
	ft_printf("pc is %i for fork\n", caller->pc - game->memdump);
	addr = access_ptr(game->memdump, caller->pc, (int)(short)(inst->args[0].value.u_dir_val) % IDX_MOD);
	prcs_cpy((t_process *)(new->content), caller, addr);
	ft_lstadd(&(game->prcs), new);
	if (!(game->deb_state & 64))
		return ;
	inst->args[0].value.u_dir_val = addr - game->memdump;
	deb_64_log(game, inst, caller, game->nbr_prcs - 1);
}
