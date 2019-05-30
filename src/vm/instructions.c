/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 21:34:04 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/30 15:12:02 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


//updating caller pc and wait_c
void	update_caller(t_process *caller, t_op *op)
{
	//update caller->pc  and caller->wait_c by reffering op = op_tab[inst->op_index]
}

static void	exec_inst(t_game *game, t_process *caller, t_inst *inst)
{
	//read op->opcode and call the right asm_fucntion
	t_opcode	c;
	if (!(c = ((t_op *)(inst->op))->opcode))
		return ;
}

//decode, excute, update pc
void	prcs_inst(t_game *game, t_process *caller)
{
	t_uc	*dump;
	t_inst	inst;

	dump = game->memdump;
	ft_bzero(&inst, sizeof(t_inst));
	//read all the info needed for exec
	if (!decode(dump, caller->pc, &inst))
		return ;
	exec_inst(game, caller, &inst);
	update_caller(caller, (t_op *)(inst.op));	
}
