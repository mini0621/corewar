/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:07:53 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/08 16:14:13 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
//asm
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
