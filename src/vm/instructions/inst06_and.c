/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst06_and.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/24 12:39:44 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_and(t_game *game, t_process *caller, t_inst *inst)
{
	t_dir_type	res;
	t_dir_type	*i;

	if (!game || !caller || !inst)
		return ;
	if (!(i = get_arg(caller, game->memdump, &(inst->args[0]), 1)))
		return ;
	res = *i;
	if (!(i = get_arg(caller, game->memdump, &(inst->args[1]), 1)))
		return ;
	res = res & *i;
	caller->carry = (!res) ? 1 : 0;
	ft_memcpy(get_arg(caller, game->memdump, &(inst->args[2]), 0), &res, REG_SIZE);
	if (game->deb_state & 32)
		deb_32_log(game, inst, caller, res);
}
