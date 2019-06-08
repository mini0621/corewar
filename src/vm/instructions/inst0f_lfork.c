/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst0f_lfork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/08 16:36:14 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_lfork(t_game *game, t_process *caller, t_inst *inst)
{
	t_list	*new;

	ft_printf("long fork!\n");
	if (!game || !caller || !inst)
		return ;
	if (!(new = prcs_new(caller->c_id)))
		return ;
	inst->args[0].type = e_dir;
	prcs_cpy((t_process *)(new->content), caller, (t_uc *)get_arg(caller, game->memdump, &(inst->args[0]), 0));
	ft_lstadd(&(game->prcs), new);
}
