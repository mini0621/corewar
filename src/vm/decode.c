/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 18:06:40 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/30 18:52:49 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


t_op    g_op_tab[17] =
{
	{0, 0, {0}, 0, 0, 0, 0, 0, NULL},
	{e_live, 1, {T_DIR}, 10, 0, 0, 0, 4, &inst_live},
	{e_ld, 2, {T_DIR | T_IND, T_REG}, 5, 1, 1, 1, 4, &inst_ld},
	{e_st, 2, {T_REG, T_IND | T_REG}, 5, 1, 1, 1, 0, &inst_st},
	{e_add, 3, {T_REG, T_REG, T_REG}, 10, 1, 0, 1, 0, &inst_add},
	{e_sub, 3, {T_REG, T_REG, T_REG}, 10, 1, 0, 1, 0, &inst_sub},
	{e_and, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6,
		1, 1, 1, 4, &inst_and},
	{e_or, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6,
		1, 1, 1, 4, &inst_or},
	{e_xor, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6,
		1, 1, 1, 4, &inst_xor},
	{e_zjmp, 1, {T_DIR}, 20, 0, 0, 0, 2, &inst_zjmp},
	{e_ldi, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 25,
		1, 1, 1, 2, &inst_ldi},
	{e_sti, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 25,
		1, 1, 1, 2, &inst_sti},
	{e_fork, 1, {T_DIR}, 800, 0, 1, 0, 2, &inst_fork},
	{e_lld, 2, {T_DIR | T_IND, T_REG}, 10, 1, 0, 1, 4, &inst_lld},
	{e_lldi, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 50,
		1, 0, 1, 2, &inst_lldi},
	{e_lfork, 1, {T_DIR}, 1000, 0, 0, 0, 2, &inst_lfork},
	{e_aff, 1, {T_REG}, 2, 1, 0, 1, 0, &inst_aff}
};

//search for the inst i
//return -1 for error
static t_op	*decode_op(t_uc *pc)
{
	t_opcode	code;

	if (*pc > 0x0f)
		return (NULL);
	code = (t_opcode)(*pc);
	return (&(g_op_tab[(int)code]));
}

//store all the args required,
//check with inst->op if args are correct and callable
//if not callable return 0
//this is just READING and it wont restrict/reffer the args
static int	decode_args(t_ull *dump, t_inst *inst, t_uc *addr)
{
	//read according to type and dir_size in op
	//here probably better to do mem restrictions and mem cycling adjustment
	return (1);
}

//decode the inst and store it into t_inst, 
//in case of error return 0
int			decode(t_uc *dump, t_uc *pc, t_inst *inst)
{
	t_uc	*addr;

	addr = pc;
	if (!(inst->op = (void *)decode_op(pc)))
		return (0);
	//read for argments
	if ((get_op(inst))->ocp && !decode_ocp(++addr, inst))
		return (0);
	if (!decode_args(dump, inst, ++addr))
		return (0);
	return (1);
}
