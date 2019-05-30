/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/05/30 17:51:36 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
//maybe delete the description part?
//

t_op    g_op_tab[17] =
{
	{0, 0, {0}, 0, 0, 0, 0, 0, NULL},
	{e_live, 1, {T_DIR}, 10, 0, 0, 0, 4, &inst_01},
	{e_ld, 2, {T_DIR | T_IND, T_REG}, 5, 1, 1, 1, 4, &inst_02},
	{e_st, 2, {T_REG, T_IND | T_REG}, 5, 1, 1, 1, 0, &inst_03},
	{e_add, 3, {T_REG, T_REG, T_REG}, 10, 1, 0, 1, 0, &inst_04},
	{e_sub, 3, {T_REG, T_REG, T_REG}, 10, 1, 0, 1, 0, &inst_05},
	{e_and, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6,
		1, 1, 1, 4, &inst_06},
	{e_or, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6,
		1, 1, 1, 4, &inst_07},
	{e_xor, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6,
		1, 1, 1, 4, &inst_08},
	{e_zjmp, 1, {T_DIR}, 20, 0, 0, 0, 2, &inst_02},
	{e_ldi, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 25,
		1, 1, 1, 2, &inst_09},
	{e_sti, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 25,
		1, 1, 1, 2, &inst_0a},
	{e_fork, 1, {T_DIR}, 800, 0, 1, 0, 2, &inst_0b},
	{e_lld, 2, {T_DIR | T_IND, T_REG}, 10, 1, 0, 1, 4, &inst_0c},
	{e_lldi, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 50,
		1, 0, 1, 2, &inst_0d},
	{e_lfork, 1, {T_DIR}, 1000, 0, 0, 0, 2, &inst_0e},
	{e_aff, 1, {T_REG}, 2, 1, 0, 1, 0, &inst_0f}
};
