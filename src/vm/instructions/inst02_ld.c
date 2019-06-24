/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst02_ld.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/24 13:13:19 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_ld(t_game *game, t_process *caller, t_inst *inst)
{
	t_dir_type	*i;
	t_dir_type	*dst;

	if (!game || !caller || !inst)
		return ;
	i = get_arg(caller, game->memdump, &(inst->args[0]), 1);
	if (!i)
		return ;
	caller->carry = (!(*i)) ? 1 : 0;
	dst = get_arg(caller, game->memdump, &(inst->args[1]), 1);
	ft_memcpy(dst, i, REG_SIZE);
	if (game->deb_state & 8)
		deb_8_log(game, inst, caller, (int)*i);	
}
