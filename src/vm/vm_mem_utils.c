/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_mem_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:36:55 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/07/01 10:55:38 by mndhlovu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			vm_init_flags(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	game->nbr_cycle = ULLONG_MAX;
	game->cycle_d = CYCLE_TO_DIE;
	game->cycle_to_die = CYCLE_TO_DIE;
	game->print_off = 0;
	game->winner = -1;
	game->nbr_prcs = 1;
	ft_bzero(game->memdump, sizeof(t_uc) * MEM_SIZE);
}

void			endian_conv(void *value, size_t size)
{
	t_uc		tmp;
	size_t		i;

	if (size < 1 || !value)
		return ;
	i = 0;
	if (size == 2)
	{
		tmp = *(int *)value & 0xff;
		*(int *)value = (*(int *)value >> 8 & 0xff)
			| (*(int *)value << 8 & 0xff00);
		return ;
	}
	while (i < size / 2)
	{
		tmp = ((t_uc *)value)[size - i - 1];
		((t_uc *)value)[size - i - 1] = *((t_uc *)value + i);
		*((t_uc *)value + i) = tmp;
		i++;
	}
}
