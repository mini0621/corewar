/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:03:48 by sunakim           #+#    #+#             */
/*   Updated: 2019/06/06 14:15:32 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	error(t_pos *pos, int i)
{
	if (i == 1)
		ft_printf("Lexical error at [%d : %d]\n", pos->line, pos->col);
	else if (i == 2)
		ft_printf("Syntactic error at [%d : %d]\n", pos->line, pos->col);
	else
		ft_printf("Error\n");
}
