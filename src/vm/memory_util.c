/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 21:13:21 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/11 01:52:41 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_uc	*access_ptr(t_uc *dump, t_uc *pc, int offset)
{
	//ft_printf("offset = %i\n", offset);
	while (offset / MEM_SIZE)
		offset %= MEM_SIZE;
	if (offset < 0)
		offset = MEM_SIZE + offset; 
	if (pc - dump + offset < MEM_SIZE)
		return (pc + offset);
	return (dump + ((pc - dump + offset) % MEM_SIZE));
}

void	endian_conv(void *value, size_t size)
{
	t_uc	tmp;
	int		i;

	if (size < 1)
		return ;
	i = 0;
	while (i < size / 2)
	{
		tmp = ((t_uc *)value)[size - i - 1];
		((t_uc *)value)[size - i - 1] = *((t_uc *)value + i);
		*((t_uc *)value + i) = tmp;
		i++;
	}
}

void	debug_hex(void *dst, size_t size)
{
	int i = 0;
	ft_printf("hex read :");
	while (i < size)
	{
		ft_printf(" %hhx", *(t_reg_type *)(dst + i));
		i++;
	}
	ft_printf("\n");
}

void	read_dump(t_uc *dump, t_uc *src, void *dst, size_t size)
{
	size_t	wr;
	
//	ft_printf("read src-dump %llu\n", src -dump);
	if (src - dump + size > MEM_SIZE)
	{
		wr = MEM_SIZE - (src - dump);
		ft_memcpy(dst, src, wr);
		ft_memcpy(dst + size, src, size - wr);
	}
	else
		ft_memcpy(dst, src, size);
	endian_conv(dst, size);
	debug_hex(dst, size);
	//ft_printf("check %x\n", *(int *)dst);
	
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
	endian_conv(dst, size);
}

t_dir_type	*get_arg(t_process *caller, t_uc *dump, t_arg *arg, int rstr)
{
	int			i;

	if (arg->type == e_reg)
	{
		i = (int)(arg->value.u_reg_val);
		return ((i > 0 && i < REG_NUMBER) ? &(caller->regs[i - 1]) : NULL);
	}
	else if (arg->type == e_dir)
		return (&(arg->value.u_dir_val));
	i = (rstr) ? (int)(signed short)(arg->value.u_ind_val) % IDX_MOD
		: (int)(signed short)(arg->value.u_ind_val);
	ft_memcpy(&(arg->value.u_dir_val), access_ptr(dump, caller->pc, i), REG_SIZE);
	endian_conv(&(arg->value.u_dir_val), REG_SIZE);
	return (&(arg->value.u_dir_val));
}
