/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 21:34:04 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/28 00:07:07 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.c"
//decode, excute, update pc
void	exec_inst(t_game *game, t_process *caller)
{
	t_ut	*dump;
	t_args	args;
	e_op	index;

	dump = game->memdump;
	//read all the info needed for exec
	index = decode(dump, caller->pc, &inst);
	//exec
	caller->
}
