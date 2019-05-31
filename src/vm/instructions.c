/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 21:34:04 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/31 21:03:28 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
		(get_op(&inst))->function(game, caller, &inst);
	caller->pc = newpc;
	caller->wait_c = (get_op(&inst))->wait;
}
