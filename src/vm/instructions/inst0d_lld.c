/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst0d_lld.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/01 00:16:08 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_lld(t_game *game, t_process *caller, t_inst *inst)
{
	ft_printf("lld!\n");
	if (!game || !caller || !inst)
		return ;
	ft_memcpy(get_arg(caller, game->memdump, &(inst->args[1]), 0),
			get_arg(caller, game->memdump, &(inst->args[0]), 0), REG_SIZE);
}
