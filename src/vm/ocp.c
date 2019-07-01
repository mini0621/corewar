/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 00:21:44 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/29 11:28:21 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_ocp					ocp_nargshift(t_ocp ocp, int n_args)
{
	int					i;

	i = MAX_ARGS_NUMBER - n_args - 1;
	while (i >= 0)
	{
		ocp = ocp >> 2;
		i--;
	}
	return (ocp);
}

static t_argtype		get_typefromcode(t_ocp code)
{
	if (code == REG_CODE)
		return (e_reg);
	if (code == DIR_CODE)
		return (e_dir);
	if (code == IND_CODE)
		return (e_ind);
	return (0);
}

static int				add_error_pc(t_argtype type, int dir)
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

int						decode_ocp(t_uc *addr, t_inst *inst)
{
	t_ocp		ocp;
	t_argtype	type;
	int			i;
	int			newpc;
	int			err;

	err = 0;
	newpc = 0;
	ocp = ocp_nargshift(*((t_ocp *)addr), (get_op(inst))->n_args);
	i = (get_op(inst))->n_args - 1;
	while (i >= 0)
	{
		type = get_typefromcode(0x03 & ocp);
		newpc += add_error_pc(type, (get_op(inst))->dir_bytes);
		if (!type || !(type & (get_op(inst))->args[i]))
			err++;
		inst->args[i].type = type;
		i--;
		ocp = ocp >> 2;
	}
	if (err)
		inst->op = NULL;
	return ((err) ? newpc : 0);
}
