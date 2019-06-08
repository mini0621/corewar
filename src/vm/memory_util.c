/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 21:13:21 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/08 22:18:33 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_uc	*access_ptr(t_uc *dump, t_uc *pc, int offset)
{
	while (offset / MEM_SIZE)
		offset %= MEM_SIZE;
	if (offset < 0)
		offset = MEM_SIZE + offset; 
	if (pc - dump + offset < MEM_SIZE)
		return (pc + offset);
	return (dump + ((pc - dump + offset) % MEM_SIZE));
}

static void	endian_conv(void *value, size_t size)
{
	t_uc	tmp;
	int		i;

	i = 0;
	while (i < size / 2)
	{
		tmp = ((t_uc *)value)[size - i - 1];
		((t_uc *)value)[size - i - 1] = *((t_uc *)value + i);
		*((t_uc *)value + i) = tmp;
		i++;
	}
}

void	read_dump(t_uc *dump, t_uc *src, void *dst, size_t size)
{
	size_t	wr;
	
	ft_printf("read src-dump %llu\n", src -dump);
	if (src - dump + size > MEM_SIZE)
	{
		wr = MEM_SIZE - (src - dump);
		ft_memcpy(dst, src, wr);
		ft_memcpy(dst + size, src, size - wr);
	}
	else
		ft_memcpy(dst, src, size);
	endian_conv(dst, size);
	ft_printf("read %x\n", *(int *)dst);
}

void	write_dump(t_uc *dump, void *src, t_uc *dst, size_t size)
{
	size_t	rd;

	if (dst - dump + size > MEM_SIZE)
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
	int			i;

	if (arg->type == e_reg)
	{
		i = (int)(arg->value.u_reg_val);
		return ((i > 0 && i < REG_NUMBER) ? &(caller->regs[i - 1]) : NULL);
	}
	else if (arg->type == e_dir)
		return (&(arg->value.u_dir_val));
	else if (rstr)
		return ((t_dir_type *)(access_ptr(dump, caller->pc,
					(size_t)(arg->value.u_ind_val) % IDX_MOD)));
	else
		return ((t_dir_type *)(access_ptr(dump, caller->pc,
					(size_t)(arg->value.u_ind_val))));
}
