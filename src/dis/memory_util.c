/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 21:13:21 by mnishimo          #+#    #+#             */
<<<<<<< HEAD:srcs/memory_util.c
/*   Updated: 2019/06/20 07:08:10 by mndhlovu         ###   ########.fr       */
=======
/*   Updated: 2019/07/01 12:04:56 by mndhlovu         ###   ########.fr       */
>>>>>>> master:src/vm/memory_util.c
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_uc			*access_ptr(t_uc *dump, t_uc *pc, int offset)
{
	while (offset / MEM_SIZE)
		offset %= MEM_SIZE;
	if (offset < 0)
		offset = MEM_SIZE + offset;
	if (pc - dump + offset < MEM_SIZE)
		return (pc + offset);
	return (dump + ((pc - dump + offset) % MEM_SIZE));
}

void			debug_hex(void *dst, size_t size)
{
	size_t		i;

	i = 0;
	ft_printf("hex read :");
	while (i < size)
	{
		ft_printf(" %hhx", *(t_reg_type *)(dst + i));
		i++;
	}
	ft_printf("\n");
}

void			read_dump(t_uc *dump, t_uc *src, void *dst, size_t size)
{
	size_t		wr;

	if (src - dump + size > MEM_SIZE)
	{
		wr = MEM_SIZE - (src - dump);
		ft_memcpy(dst, src, wr);
		ft_memcpy(dst + wr, dump, size - wr);
	}
	else
		ft_memcpy(dst, src, size);
	endian_conv(dst, size);
}

void			write_dump(t_uc *dump, void *src, t_uc *dst, size_t size)
{
	size_t		rd;

	endian_conv(src, size);
	if (dst - dump + size > MEM_SIZE)
	{
		rd = MEM_SIZE - (dst - dump);
		ft_memcpy(dst, src, rd);
		ft_memcpy(dump, src + rd, size - rd);
	}
	else
		ft_memcpy(dst, src, size);
	endian_conv(src, size);
}

t_dir_type		*get_arg(t_process *caller, t_uc *dump, t_arg *arg, int rstr)
{
	int			i;

	if (arg->type == e_reg)
	{
		i = (int)(signed short)arg->value.u_reg_val;
		return ((i > 0 && i <= REG_NUMBER) ? &(caller->regs[i - 1]) : NULL);
	}
	else if (arg->type == e_dir)
		return (&(arg->value.u_dir_val));
	i = (rstr) ? (int)(signed short)(arg->value.u_ind_val) % IDX_MOD
		: (int)(signed short)(arg->value.u_ind_val);
	arg->value.u_dir_val = 0;
	read_dump(dump, access_ptr(dump, caller->pc, i)
			, &(arg->value.u_dir_val), REG_SIZE);
	return (&(arg->value.u_dir_val));
}
