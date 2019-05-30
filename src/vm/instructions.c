/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 21:34:04 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/30 23:21:36 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	exec_inst(t_game *game, t_process *caller, t_inst *inst)
{
	//read op->opcode and call the right asm_fucntion
	t_inst_func		func;

	func = (get_op(inst))->function;
	func(game, caller, inst);
}

//decode, excute, update pc
void	prcs_inst(t_game *game, t_process *caller)
{
	t_uc	*dump;
	t_uc	*newpc;
	t_inst	inst;

	dump = game->memdump;
	ft_bzero(&inst, sizeof(t_inst));
	//read all the info needed for exec
	newpc = decode(dump, caller->pc, &inst);
	if (inst.op)
		exec_inst(game, caller, &inst);
	caller->pc = newpc;
	caller->wait_c = (get_op(&inst))->wait;
}
