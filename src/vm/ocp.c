/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 00:21:44 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/27 02:28:56 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_ocp	ocp_nargshift(t_ocp ocp, int n_args)
{
	int i;

	i = MAX_ARGS_NUMBER - n_args - 1;
	while (i >= 0)
	{
		ocp = ocp >> 2;
		i--;
	}
	return (ocp);
}

static t_argtype	get_typefromcode(t_ocp code)
{
	if (code == REG_CODE)
		return (e_reg);
	if (code == DIR_CODE)
		return (e_dir);
	if (code == IND_CODE)
		return (e_ind);
	return (0);
}

static int	add_error_pc(t_argtype type, int dir)
{
	if (type == e_reg)
		return (1);
	if (type == e_ind)
		return (2);
	if (type == e_dir && dir)
		return (4);
	if (type == e_dir)
		return (2);
	else
		return (0);
}


int		decode_ocp(t_uc *addr, t_inst *inst)
{
	t_ocp		ocp;
	t_argtype	type;
	t_op		*op;
	int			i;
	int			newpc;
	int			err;

	err = 0;
	newpc = 0;
	ocp = *((t_ocp *)addr);
	op = get_op(inst);
	ocp = ocp_nargshift(ocp, op->n_args);
	i = op->n_args - 1;
	while (i >= 0)
	{
		type = get_typefromcode(0x03 & ocp);
		//ft_printf("this %i %x\n",i, op->args[i]);
		newpc += add_error_pc(type, op->dir_bytes);
		if (!(type & op->args[i]))
			err++;
		//ft_printf("arg %i is type %i \n",i, type);
		inst->args[i].type = type;
		i--;
		ocp = ocp >> 2;
	}
	return ((err) ? newpc : 0);
}
