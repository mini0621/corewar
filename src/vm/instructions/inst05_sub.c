/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst05_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/31 23:52:05 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_sub(t_game *game, t_process *caller, t_inst *inst)
{

	t_dir_type	res;

	ft_printf("sub!\n");
	if (!game || !caller || !inst)
		return ;
	res = *get_arg(caller, game->memdump, &(inst->args[0]), 0)
		- *get_arg(caller, game->memdump, &(inst->args[1]), 0);
	ft_memcpy(get_arg(caller, game->memdump, &(inst->args[2]), 0), &res, REG_SIZE);
}
