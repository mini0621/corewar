/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state_s.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 22:32:35 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/09 23:03:32 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	check_state_s(t_pos *pos, t_tkn *tkn)
{
	if (syntactic_sm[pos->state_s][0] == -2)
		pos->state_s = syntactic_sm[pos->state_s][1];
	if (syntactic_sm[pos->state_s][0] == -3)
		pos->state_s = ((t_op_asm*)(tkn->value))->op_state_s;
}
