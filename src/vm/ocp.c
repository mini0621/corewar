/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 00:21:44 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/08 23:15:46 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
//return (0) for an error

t_ocp	ocp_nargshift(t_ocp ocp, int n_args)
{
	int i;

	i = MAX_ARGS_NUMBER - n_args - 1;
	while (i >= 0)
	{
//		ft_printf("arg count\n");
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
		//get each args type 
		type = get_typefromcode(0x03 & ocp);
		//and check if it is right
//		ft_printf("this %i %x\n",i, op->args[i]);
		if (!(type & op->args[i]))
			return (0);
		//and store the type in inst
//		ft_printf("arg %i is type %x \n",i, type);
		inst->args[i].type = type;
		i--;
		ocp = ocp >> 2;
	}
	return (1);
}

/* debug
int main()
{
	t_uc	a = 0x78;
	t_uc	b = 0xf8;
	t_uc	c = 0x5c;

	t_inst	ai;
	t_inst	bi;
	t_inst	ci;
	decode_ocp(&a, &ai);
	decode_ocp(&b, &bi);
	decode_ocp(&c, &ci);
	ft_printf("a %i %i %i\n", ai.args[0].type, ai.args[1].type, ai.args[2].type);
}
*/
