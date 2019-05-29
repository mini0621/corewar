/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 21:34:04 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/28 22:10:55 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.c"


//updating caller pc and wait_c
void	update_caller(t_process *caller, t_op *op)
{

}

static void	exec_inst(t_game *game, t_process *caller, t_inst *inst)
{
	//read op->opcode and call the right asm_fucntion
}

//decode, excute, update pc
void	prcs_inst(t_game *game, t_process *caller)
{
	t_ut	*dump;
	t_inst	inst;

	dump = game->memdump;
	ft_bzero(&inst, sizeof(t_inst));
	//read all the info needed for exec
	if (!decode(dump, caller->pc, &inst))
		return ;
	//exec
	exec_inst(game, caller, &inst);
	//update caller->pc  and caller->wait_c by reffering op = op_tab[inst->op_index]
	update_caller(caller, op_tab[inst->op_index]);	
}
