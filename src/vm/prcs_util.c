/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prcs_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:30:30 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/11 02:33:45 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_list	*prcs_new(int c_id)
{
	t_process	prcs;
	t_list		*lst;

	ft_bzero(&prcs, sizeof(t_process));
	prcs.c_id = c_id;
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
}
