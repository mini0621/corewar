/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 21:34:04 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/25 17:14:56 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	prcs_inst(t_game *game, size_t p_index)
{
	t_uc	*dump;
	t_uc	*newpc;
	t_inst	inst;
	t_process *caller;

	if (game->prcs_count + 5 > game->prcs->nbr_elem
			&& ft_arrresize(game->prcs, game->prcs->nbr_elem * 2) < 0)
		return ;
	caller = (t_process *)ft_arrget(game->prcs, p_index);
	dump = game->memdump;
	ft_bzero(&inst, sizeof(t_inst));
	inst.op = (void *)decode_op(caller->op);
	newpc = decode(dump, caller->pc, &inst);
	if (inst.op)
		(get_op(&inst))->function(game, caller, &inst);
	if (!inst.op || !((get_op(&inst))->opcode == e_zjmp && caller->carry))
		caller->pc = newpc;
	caller->op = *(caller->pc);
	caller->wait_c = decode_wait(caller->pc);
}
