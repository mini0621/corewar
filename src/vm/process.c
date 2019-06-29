/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:17:05 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/29 11:30:03 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	count_alivechamps(t_game *game, t_champ **champs)
{
	int	i;
	int	end;

	end = 0;
	i = game->nbr_champs - 1;
	while (i >= 0)
	{
		if (champs[i]->prcs_c && champs[i]->live_c)
		{
			end++;
			game->winner = champs[i]->id;
		}
		else
		{
			champs[i]->live_c = 0;
			get_debug(game, *champs + i, 0);
		}
		i--;
	}
	if (!end)
		return (game->winner);
	return (0);
}

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
}

static int	is_end(t_game *game, t_champ **champs)
{
	int			i;
	t_process	*p;

	i = game->prcs->last;
	reset_prcs_c(game);
	while (i >= 0)
	{
		p = (t_process *)ft_arrget(game->prcs, i);
		if (p && p->is_alive)
		{
			game->champs[-1 * p->c_id - 1]->prcs_c += 1;
			p->is_alive = 0;
			i--;
			continue;
		}
		get_debug(game, NULL, p->p_id);
		game->prcs_count -= 1;
		ft_arrsub(game->prcs, i);
		i--;
	}
	update_cycles(game);
	return (count_alivechamps(game, champs));
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
	if (!game->cycle_d && (win = is_end(game, &(game->champs[0]))))
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
