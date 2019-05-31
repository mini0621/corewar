/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst0a_ldi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/01 00:10:58 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_ldi(t_game *game, t_process *caller, t_inst *inst)
{
	t_dir_type	res;

	if (!game || !caller || !inst)
		return ;
	res = *get_arg(caller, game->memdump, &(inst->args[0]), 1)
			+ *get_arg(caller, game->memdump, &(inst->args[1]), 1);
	ft_memcpy(get_arg(caller, game->memdump, &(inst->args[2]), 1),
		access_ptr(game->memdump, caller->pc, (size_t)res % IDX_MOD), REG_SIZE);
}
