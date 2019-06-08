/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst0d_lld.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/08 23:12:02 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_lld(t_game *game, t_process *caller, t_inst *inst)
{
	t_dir_type	*i;
	
	if (game->deb_state)
		ft_printf("lld!\n");
	if (!game || !caller || !inst)
		return ;
	i = get_arg(caller, game->memdump, &(inst->args[0]), 0);
		caller->carry = (i && !(*i)) ? 1 : 0;
	ft_memcpy(get_arg(caller, game->memdump, &(inst->args[1]), 0),
			i, REG_SIZE);
}
