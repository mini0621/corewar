/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_mem_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:36:55 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/06/08 19:10:03 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void            vm_init_flags(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
    game->cycle_d = CYCLE_TO_DIE;
    game->cycle_to_die = CYCLE_TO_DIE;
    game->d_state = 0;
    game->n_state = 0;
    game->a_state = 0;
    game->s_state = 0;
    game->deb_state = 0;
    game->pl_state = 0;
    game->pv_number = 0;
    game->pl_number = 0;
    game->visu = 0;
    ft_bzero(&(game->memdump[0]), MEM_SIZE * sizeof(t_uc));
}
