/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst10_aff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/21 15:39:05 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_aff(t_game *game, t_process *caller, t_inst *inst)
{
	char	c;

	if (!game || !caller || !inst)
		return ;
	c = (char)*get_arg(caller, game->memdump, &(inst->args[0]), 0);
	caller->carry = (!c) ? 1 : 0;
	if (game->print_off && game->print_off != 1)
		ft_printf("%c", c);
}
