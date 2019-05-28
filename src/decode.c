/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 18:06:40 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/28 18:28:15 by mnishimo         ###   ########.fr       */
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
static int	decode_args(t_inst *inst, t_uc *addr)
{

}

//decode the inst and store it into t_inst, 
//in case of error return 0
int			decode(t_uc *dump, t_uc *pc, t_inst *inst)
{
	if (!(inst->op = decode_opindex(pc)))
		return (0);
	//read for argments
	if (!decode_args(inst, pc + 1))
		return (0);
	return (1);
}
