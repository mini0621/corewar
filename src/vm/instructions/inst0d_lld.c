/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst0d_lld.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/29 00:37:09 by mndhlovu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			inst_lld(t_game *game, t_process *caller, t_inst *inst)
{
	t_dir_type	*i;
	t_dir_type	*dst;

	if (!game || !caller || !inst)
		return ;
	if (!(i = get_arg(caller, game->memdump, &(inst->args[0]), 0)))
		return ;
	caller->carry = (i && !(*i)) ? 1 : 0;
	if (!(dst = get_arg(caller, game->memdump, &(inst->args[1]), 0)))
		return ;
	ft_memcpy(dst, i, REG_SIZE);
	if (game->deb_state & 8)
		deb_8_log(game, inst, caller, (int)*i);
}
