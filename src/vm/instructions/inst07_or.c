/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst07_or.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/08 23:10:56 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_or(t_game *game, t_process *caller, t_inst *inst)
{
	t_dir_type	res;

	if (game->deb_state)
		ft_printf("or!\n");
	if (!game || !caller || !inst)
		return ;
	res = (*get_arg(caller, game->memdump, &(inst->args[0]), 1)
			| *get_arg(caller, game->memdump, &(inst->args[1]), 1));
	caller->carry = (!res) ? 1 : 0;
	ft_memcpy(get_arg(caller, game->memdump, &(inst->args[2]), 0), &res, REG_SIZE);
}
