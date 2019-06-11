/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst04_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/11 03:19:57 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_add(t_game *game, t_process *caller, t_inst *inst)
{
	t_dir_type	res;

	if (!game || !caller || !inst)
		return ;
	res = *get_arg(caller, game->memdump, &(inst->args[0]), 0)
		+ *get_arg(caller, game->memdump, &(inst->args[1]), 0);
	caller->carry = (!res) ? 1 : 0;
	ft_memcpy(get_arg(caller, game->memdump, &(inst->args[2]), 0), &res, REG_SIZE);
	if (!(game->deb_state))
		return ;
	inst->args[0].value.u_dir_val = res;
	get_debug(game, inst, caller, NULL);
	
}
