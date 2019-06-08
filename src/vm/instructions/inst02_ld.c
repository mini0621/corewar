/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst02_ld.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/08 23:10:09 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_ld(t_game *game, t_process *caller, t_inst *inst)
{
	t_dir_type	*i;
	int			*reg;

	if (!game || !caller || !inst)
		return ;
	i = get_arg(caller, game->memdump, &(inst->args[0]), 1);
	reg = (int *)get_arg(caller, game->memdump, &(inst->args[1]), 1);
	if (game->deb_state)
		ft_printf("ld! %x into %i\n", *i, *reg);
	caller->carry = (i && !(*i)) ? 1 : 0;
	ft_memcpy(reg, i, REG_SIZE);
}
