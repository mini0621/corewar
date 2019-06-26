/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prcs_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:30:30 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/25 15:25:03 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	prcs_new(t_game *game, int c_id, t_uc *pc, t_arr *arr)
{
	t_process	prcs;

	ft_bzero(&prcs, sizeof(t_process));
	prcs.c_id = c_id;
	prcs.carry = 0;
	prcs.p_id = game->nbr_prcs;
	prcs.regs[0] = c_id;
	if (pc)
	{
		prcs.pc = pc;
		prcs.op = *pc;
		prcs.wait_c = decode_wait(pc);
	}
	game->nbr_prcs += 1;
	game->prcs_count += 1;
	return (ft_arradd(arr, &prcs, sizeof(t_process), -1));
}

void	prcs_cpy(t_process *dst, t_process *src)
{
	if (!dst || !src)
		return ;
	ft_memcpy(dst->regs, src->regs, sizeof(t_dir_type) * REG_NUMBER);
	dst->carry = src->carry;
}
