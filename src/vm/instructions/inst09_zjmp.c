/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst09_zjmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/08 16:14:23 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_zjmp(t_game *game, t_process *caller, t_inst *inst)
{
	if (!game || !caller || !inst || !caller->carry)
		return ;
	inst->args[0].type = e_dir;
	caller->pc = access_ptr(game->memdump, caller->pc, *get_arg(caller, game->memdump, &(inst->args[0]), 1));
}
