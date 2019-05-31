/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst0e_lldi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/01 00:17:19 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_lldi(t_game *game, t_process *caller, t_inst *inst)
{
	t_dir_type	res;

	if (!game || !caller || !inst)
		return ;
	res = *get_arg(caller, game->memdump, &(inst->args[0]), 0)
		+ *get_arg(caller, game->memdump, &(inst->args[1]), 0);
	ft_memcpy(get_arg(caller, game->memdump, &(inst->args[2]), 0),
			access_ptr(game->memdump, caller->pc, (size_t)res), REG_SIZE);
}
