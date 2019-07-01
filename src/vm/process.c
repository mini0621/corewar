/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:17:05 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/29 18:15:36 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	update_cycles(t_game *game)
{
	if (game->live_count > NBR_LIVE || game->check_c == MAX_CHECKS)
	{
		game->cycle_to_die = (game->cycle_to_die <= CYCLE_DELTA) ?
		1 : game->cycle_to_die - CYCLE_DELTA;
	}
	game->live_count = 0;
	game->check_c = (game->check_c == MAX_CHECKS) ? 0 : game->check_c + 1;
	game->cycle_d = game->cycle_to_die;
	if (game->deb_state & 2)
		ft_printf("  cycle_d: %i\n", game->cycle_d);
}

static int	is_end(t_game *game)
{
	int			i;
	t_process	*p;

	i = game->prcs->last;
	reset_prcs_c(game);
	while (i >= 0)
	{
		p = (t_process *)ft_arrget(game->prcs, i);
		if (p && p->is_alive)
			game->champs[-1 * p->c_id - 1]->prcs_c += 1;
		else
		{
			get_debug(game, NULL, p->p_id);
			game->prcs_count -= 1;
			ft_arrsub(game->prcs, i);
		}
		p->is_alive = 0;
		i--;
	}
	update_cycles(game);
	return ((game->prcs_count < 1) ? game->winner : 0);
}

static void	update_visu_clrmap(t_visu *visu)
{
	int	i;

	if (!visu)
		return ;
	i = 0;
	while (i < MEM_SIZE)
	{
		if (visu->clr_map[i] > 10)
			visu->clr_map[i] -= 10;
		i++;
	}
}

int			process(t_game *game)
{
	int				i;
	t_process		*p;
	int				win;

	reset_debug(game);
	game->cycle += 1;
	game->cycle_d -= 1;
	get_debug(game, NULL, 0);
	if (!game->cycle_d && (win = is_end(game)))
		return (win);
	i = game->prcs->last;
	while (i >= 0)
	{
		p = (t_process *)ft_arrget(game->prcs, i);
		if (!p->wait_c)
			prcs_inst(game, i);
		else
			p->wait_c -= 1;
		i--;
	}
	print_debug(game);
	update_visu_clrmap(game->visu);
	return ((game->nbr_cycle == game->cycle) ? 1 : 0);
}
