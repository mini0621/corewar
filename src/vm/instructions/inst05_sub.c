/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst05_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/24 12:40:03 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_sub(t_game *game, t_process *caller, t_inst *inst)
{
	t_dir_type	*i;
	int			res;

	if (!game || !caller || !inst)
		return ;
	if (!(i = get_arg(caller, game->memdump, &(inst->args[0]), 0)))
		return ;
	res	= (int)*i;
	if (!(i = get_arg(caller, game->memdump, &(inst->args[1]), 0)))
		return ;
	res	-= (int)*i;
	caller->carry = (!res) ? 1 : 0;
	ft_memcpy(get_arg(caller, game->memdump, &(inst->args[2]), 0), &res, REG_SIZE);
	if (game->deb_state & 32)
		deb_32_log(game, inst, caller, res);
}
