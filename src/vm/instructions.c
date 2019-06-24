/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 21:34:04 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/24 11:37:09 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	prcs_inst(t_game *game, t_process *caller)
{
	t_uc	*dump;
	t_uc	*newpc;
	t_inst	inst;

	dump = game->memdump;
	ft_bzero(&inst, sizeof(t_inst));
	newpc = decode(dump, caller->pc, &inst);
	if (inst.op)
		(get_op(&inst))->function(game, caller, &inst);
	if (inst.op && !((get_op(&inst))->opcode == e_zjmp && caller->carry))
		caller->pc = newpc;
	caller->wait_c = (decode_wait(caller->pc));
}
