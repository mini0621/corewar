/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst04_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 00:17:55 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/06/29 00:19:31 by mndhlovu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			inst_add(t_game *game, t_process *caller, t_inst *inst)
{
	int			res;
	t_dir_type	*i;

	if (!game || !caller || !inst)
		return ;
	if (!(i = get_arg(caller, game->memdump, &(inst->args[0]), 0)))
		return ;
	res = (int)*i;
	if (!(i = get_arg(caller, game->memdump, &(inst->args[1]), 0)))
		return ;
	res += (int)*i;
	caller->carry = (!res) ? 1 : 0;
	ft_memcpy(get_arg(caller, game->memdump
				, &(inst->args[2]), 0), &res, REG_SIZE);
	if (game->deb_state & 32)
		deb_32_log(game, inst, caller, res);
}
