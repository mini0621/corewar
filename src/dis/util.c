/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:20:47 by allefebv          #+#    #+#             */
/*   Updated: 2019/07/02 16:23:22 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	opcode_is_valid(t_uc x)
{
	if (16 > (uint32_t)((x) - 1))
		return (1);
	return (0);
}

int	reg_is_valid(int x)
{
	if (REG_NUMBER > (uint32_t)((x) - 1))
		return (1);
	return (0);
}
