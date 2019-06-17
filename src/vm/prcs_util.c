/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prcs_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:30:30 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/17 17:07:14 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_list	*prcs_new(t_game *game, int c_id)
{
	t_process	prcs;
	t_list		*lst;

	ft_bzero(&prcs, sizeof(t_process));
	prcs.c_id = c_id;
	prcs.p_id = game->nbr_prcs;
	game->nbr_prcs += 1;
	game->prcs_count += 1;
	prcs.regs[0] = c_id;
	if (!(lst = ft_lstnew(&prcs, sizeof(t_process))))
		return (NULL);
	return (lst);
}

void	prcs_cpy(t_process *dst, t_process *src, t_uc *addr)
{
	ft_memcpy(&(dst->regs), &(src->regs), sizeof(t_dir_type) * REG_NUMBER);
	dst->carry = src->carry;
	dst->pc = addr;
	dst->wait_c = decode_wait(addr);
}
