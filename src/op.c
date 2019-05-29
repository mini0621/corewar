/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/05/29 17:57:06 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "corewar.h"
//maybe delete the description part?
//

t_op    op_tab[17] =
{
	{"live", 1, {T_DIR}, 10, 0, 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 5, 1, 1, 1},
	{"st", 2, {T_REG, T_IND | T_REG}, 5, 1, 1, 1},
	{"add", 3, {T_REG, T_REG, T_REG}, 10, 1, 0, 1},
	{"sub", 3, {T_REG, T_REG, T_REG}, 10, 1, 0, 1},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6,
		1, 1, 1},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6,
		1, 1, 1},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 6,
		1, 1, 1},
	{"zjmp", 1, {T_DIR}, 20, 0, 0, 0},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 25,
		1, 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 25,
		1, 1, 1},
	{"fork", 1, {T_DIR}, 800, 0, 1, 0},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 10, 1, 0, 1},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 50,
		1, 0, 1},
	{"lfork", 1, {T_DIR}, 1000, 0, 0, 0},
	{"aff", 1, {T_REG}, 2, 1, 0, 1},
	{0, 0, {0}, 0, 0, 0, 0}
};
