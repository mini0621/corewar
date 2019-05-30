/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 18:06:40 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/30 23:08:42 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


t_op    g_op_tab[17] =
{
	{0, 0, {0}, 0, 0, 0, 0, 0, NULL},
	{e_live, 1, {T_DIR}, 10, 0, 0, 0, 1, &inst_live},
	{e_ld, 2, {T_DIR | T_IND, T_REG}, 5, 1, 1, 1, 1, &inst_ld},
	{e_st, 2, {T_REG, T_IND | T_REG}, 5, 1, 1, 1, 0, &inst_st},
	{e_add, 3, {T_REG, T_REG, T_REG}, 10, 1, 0, 1, 0, &inst_add},
	{e_sub, 3, {T_REG, T_REG, T_REG}, 10, 1, 0, 1, 0, &inst_sub},
	{e_and, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6,
		1, 1, 1, 1, &inst_and},
	{e_or, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6,
		1, 1, 1, 1, &inst_or},
	{e_xor, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6,
		1, 1, 1, 1, &inst_xor},
	{e_zjmp, 1, {T_DIR}, 20, 0, 0, 0, 0, &inst_zjmp},
	{e_ldi, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 25,
		1, 1, 1, 0, &inst_ldi},
	{e_sti, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 25,
		1, 1, 1, 0, &inst_sti},
	{e_fork, 1, {T_DIR}, 800, 0, 1, 0, 0, &inst_fork},
	{e_lld, 2, {T_DIR | T_IND, T_REG}, 10, 1, 0, 1, 1, &inst_lld},
	{e_lldi, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 50,
		1, 0, 1, 0, &inst_lldi},
	{e_lfork, 1, {T_DIR}, 1000, 0, 0, 0, 0, &inst_lfork},
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
//reading ind is always 2 bytes?
static t_uc	*read_morebytes(t_uc *dump, t_uc *ptr, t_op *op, t_arg *arg)
{
	int	size;
	int	wr;

	wr = 0;
	size = (op->dir_bytes) ? 4 : 2;
	if (ptr - dump + size < MEM_SIZE)
		arg->value.dir_val = (op->dir_bytes) ? *((uint32_t *)ptr) : *((uint16_t *)ptr);
	else if (ptr - dump < MEM_SIZE)
	{
		wr = MEM_SIZE - (ptr - dump);
		ft_memcpy(&(arg->value.dir_val), ptr, sizeof(t_uc) * wr);
		ft_memcpy(&(arg->value.dir_val) + sizeof(t_uc) * wr, ptr, sizeof(t_uc) * (size - wr));
	}
	if (wr)
		return (dump + (size - wr));
	return (ptr + size);
}

//store all the args required,
//check with inst->op if args are correct and callable
//if not callable return 0
//this is just READING and it wont restrict/reffer the args
static t_uc	*decode_args(t_ull *dump, t_inst *inst, t_uc *addr)
{
	int	i;
	int	l;
	t_uc	*ptr;
	t_op	*op;

	i = 0;
	op = get_op(inst);
	l = op->n_args;
	ptr = addr;
	//read according to type and dir_size in op
	while (i < l)
	{
		if (inst->args[i].type != e_reg)
			ptr = read_morebytes(dump, ptr, get_op(inst), &(inst->args[i]));
		else
		{
			inst->args[i].value.reg_val = *ptr;
			ptr = (ptr - dump == MEM_SIZE) ? dump : ptr + 1;
		}
		i++;
	}
	return (ptr);
}

//decode the inst and store it into t_inst, 
//in case of error return 0
//in error how many should we plus the pc
t_uc		*decode(t_uc *dump, t_uc *pc, t_inst *inst)
{
	t_uc	*addr;

	addr = pc;
	if (!(inst->op = (void *)decode_op(pc)))
		return ((pc - dump == MEM_SIZE) ? pc + 1 : dump);
	//read for argments
	if (addr - dump > MEM_SIZE - 1)
		addr = dump;
	if ((get_op(inst))->ocp)
	{
		if (!decode_ocp(addr, inst))
			return ((pc - dump == MEM_SIZE) ? pc + 1 : dump);
		addr++;
	}
	addr = decode_args(dump, inst, addr);
	return (addr);
}
