/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst03_st.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/31 23:48:57 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_st(t_game *game, t_process *caller, t_inst *inst)
{
	ft_printf("st!\n");
	if (!game || !caller || !inst)
		return ;
	ft_memcpy(get_arg(caller, game->memdump, &(inst->args[1]), 1),
			get_arg(caller, game->memdump, &(inst->args[0]), 1), REG_SIZE);
}
