/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 18:06:40 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/30 00:48:13 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

//search for the inst i
//return -1 for error
static t_op	*decode_op(t_uc *pc)
{
	
}

//store all the args required,
//check with inst->op if args are correct and callable
//if not callable return 0
//this is just READING and it wont restrict/reffer the args
static int	decode_args(t_ull *dump, t_inst *inst, t_uc *addr)
{
	//read according to type and dir_size in op
	//here probably better to do mem restrictions and mem cycling adjustment
}

//decode the inst and store it into t_inst, 
//in case of error return 0
int			decode(t_uc *dump, t_uc *pc, t_inst *inst)
{
	t_uc	*addr;

	addr = pc;
	if (!(inst->op = decode_opindex(pc)))
		return (0);
	//read for argments
	if (inst->op->ocp && !decode_ocp(++addr, inst))
		return (0);
	if (!decode_args(inst, ++addr))
		return (0);
	return (1);
}
