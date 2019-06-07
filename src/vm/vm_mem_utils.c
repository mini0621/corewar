/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_mem_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:36:55 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/05/30 15:37:07 by mndhlovu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void            vm_init_flags(t_game *game)
{
    game->nbr_cycle = 0;
    game->nbr_s_cycle = 0;
    game->nbr_champs = 0;
    game->cycle = 0;
    game->cycle_d = 0;
    game->c_checked = 0;
    game->cycle_to_die = 0;
    game->d_state = 0;
    game->n_state = 0;
    game->a_state = 0;
    game->s_state = 0;
    game->deb_state = 0;
    game->pl_state = 0;
    game->pv_number = 0;
    game->pl_number = 0;
}