/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 18:06:40 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/21 16:15:17 by mnishimo         ###   ########.fr       */
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

int	decode_wait(t_uc *pc)
{
	t_opcode	code;

	if (!(*pc) || *pc > 0x0f)
		return (0);
	code = (t_opcode)(*pc);
	return (g_op_tab[(int)code].wait -1);
}

static t_op	*decode_op(t_uc *pc)
{
	t_opcode	code;

	if (!(*pc) || *pc > 0x0f)
		return (NULL);
	code = (t_opcode)(*pc);
	return (&(g_op_tab[(int)code]));
}

static t_uc	*decode_args(t_uc *dump, t_inst *inst, t_uc *addr)
{
	int	i;
	int	l;
	t_uc	*ptr;
	t_op	*op;
	size_t	size;

	i = 0;
	op = get_op(inst);
	l = op->n_args;
	ptr = addr;
	//ft_printf("op is %i\n", op->opcode);
	//ft_printf("l is %i\n", l);
	//ft_printf("addr is %hhx\n", *ptr);
	while (i < l)
	{
		size = (inst->args[i].type != e_reg) ? 4: 1;
		if (inst->args[i].type == e_ind
				|| (inst->args[i].type == e_dir && !op->dir_bytes))
			size = 2;
		//ft_printf("size? %u\n", size);
		if (inst->args[i].type == e_reg)
			read_dump(dump, ptr, (void *)&(inst->args[i].value.u_reg_val), size);
		else if (inst->args[i].type == e_ind)
			read_dump(dump, ptr, (void *)&(inst->args[i].value.u_ind_val), size);
		else if (inst->args[i].type == e_dir)
			read_dump(dump, ptr, (void *)&(inst->args[i].value.u_dir_val), size);
		ptr = access_ptr(dump, ptr, size);
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
	//	ft_printf("addr1 is %i\n", addr - dump);
	if (!(inst->op = (void *)decode_op(addr)))
		return (access_ptr(dump, addr, 1));
	addr = access_ptr(dump, addr, 1);
	if ((get_op(inst))->ocp)
	{
		if (!decode_ocp(addr, inst))
			return (access_ptr(dump, addr, 1));
		addr = access_ptr(dump, addr, 1);
	}
	else
		inst->args[0].type = e_dir;
	//	ft_printf("addr2 is %i\n", addr - dump);
	addr = decode_args(dump, inst, addr);
	//	ft_printf("addr3 is %i\n", addr - dump);
	return (addr);
}
