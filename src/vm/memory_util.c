/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 21:13:21 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/01 00:22:26 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_uc	*access_ptr(t_uc *dump, t_uc *pc, size_t offset)
{
	if (pc - dump + offset < MEM_SIZE)
		return (pc + offset);
	return (dump + ((pc - dump + offset) % MEM_SIZE));
}

void	read_dump(t_uc *dump, t_uc *src, void *dst, size_t size)
{
	size_t	wr;

	if (src - dump + size <= MEM_SIZE)
	{
		wr = MEM_SIZE - (src - dump);
		ft_memcpy(dst, src, wr);
		ft_memcpy(dst + size, src, size - wr);
	}
	else
		ft_memcpy(dst, src, size);
}

void	write_dump(t_uc *dump, void *src, t_uc *dst, size_t size)
{
	size_t	rd;

	if (dst - dump + size <= MEM_SIZE)
	{
		rd = MEM_SIZE - ((t_uc *)src - dump);
		ft_memcpy(dst, src, rd);
		ft_memcpy(dst + size, src, size - rd);
	}
	else
		ft_memcpy(dst, src, size);
}

t_dir_type	*get_arg(t_process *caller, t_uc *dump, t_arg *arg, int rstr)
{
	t_dir_type	*ret;

	if (arg->type == e_reg)
		return (&(caller->regs[(int)(arg->value.u_reg_val)]));
	else if (arg->type == e_dir)
		return (&(arg->value.u_dir_val));
	else if (rstr)
		return ((t_dir_type *)(access_ptr(dump, caller->pc,
					(size_t)(arg->value.u_ind_val) % IDX_MOD)));
	else
		return ((t_dir_type *)(access_ptr(dump, caller->pc,
					(size_t)(arg->value.u_ind_val))));
}
