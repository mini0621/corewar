/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst10_aff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/01 00:20:35 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_aff(t_game *game, t_process *caller, t_inst *inst)
{
	ft_printf("aff!\n");
	if (!game || !caller || !inst)
		return ;
	ft_printf("%c", (char)*get_arg(caller, game->memdump, &(inst->args[0]), 0));
}
