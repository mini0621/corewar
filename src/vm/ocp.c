/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 00:21:44 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/25 17:24:40 by mnishimo         ###   ########.fr       */
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

int		decode_ocp(t_uc *addr, t_inst *inst)
{
	t_ocp		ocp;
	t_argtype	type;
	t_op		*op;
	int			i;

	ocp = *((t_ocp *)addr);
	op = get_op(inst);
	if (op->n_args > MAX_ARGS_NUMBER)
		return (0);
	ocp = ocp_nargshift(ocp, op->n_args);
	i = op->n_args - 1;
	while (i >= 0)
	{
		type = get_typefromcode(0x03 & ocp);
		//ft_printf("this %i %x\n",i, op->args[i]);
		if (!(type & op->args[i]))
			return (0);
		//ft_printf("arg %i is type %i \n",i, type);
		inst->args[i].type = type;
		i--;
		ocp = ocp >> 2;
	}
	return (1);
}
