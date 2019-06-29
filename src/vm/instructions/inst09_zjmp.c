/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst09_zjmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/29 00:29:57 by mndhlovu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			inst_zjmp(t_game *game, t_process *caller, t_inst *inst)
{
	int			offset;

	if (!game || !caller || !inst)
		return ;
	offset = (int)(signed short)inst->args[0].value.u_dir_val;
	if (caller->carry && offset)
		caller->pc = access_ptr(game->memdump, caller->pc, offset % IDX_MOD);
	if (!(game->deb_state & 64))
		return ;
	inst->args[0].value.u_dir_val = (int)(caller->pc - game->memdump);
	deb_64_log(game, inst, caller, offset);
}
