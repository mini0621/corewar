/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_mem_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:36:55 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/06/16 22:52:18 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void            vm_init_flags(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	game->nbr_cycle = ULLONG_MAX;
    game->cycle_d = CYCLE_TO_DIE;
    game->cycle_to_die = CYCLE_TO_DIE;
    game->nbr_prcs = 1;
    ft_bzero(&(game->memdump[0]), MEM_SIZE * sizeof(t_uc));
}
