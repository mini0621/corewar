/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst09_zjmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/11 02:09:23 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_zjmp(t_game *game, t_process *caller, t_inst *inst)
{
	int	offset;

	if (!game || !caller || !inst || !caller->carry)
		return ;
	offset = (int)(short)(inst->args[0].value.u_dir_val);
	ft_printf("this? %i\n", offset);
	caller->pc = access_ptr(game->memdump, caller->pc, offset);
	if (!game->deb_state)
		return ;
	inst->args[0].value.u_dir_val = caller->pc - game->memdump;
	get_debug(game, inst, caller, NULL);
}
