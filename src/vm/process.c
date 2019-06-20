/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:17:05 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/20 14:36:09 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int count_alivechamps(t_game *game, t_champ **champs)
{
	int i;
	int end;

	end = 0;
	i = game->nbr_champs - 1;
	while (i >= 0)
	{
		if (champs[i]->prcs_c)
		{
			end++;
			game->winner = champs[i]->id;
		}
		else
			get_debug(game, *champs + i);
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
		game->cycle_to_die -= CYCLE_DELTA;
	}
	game->live_count = 0;
	game->check_c = (game->check_c == MAX_CHECKS) ? 0 : game->check_c + 1;	
	game->cycle_d = game->cycle_to_die;
}

static int is_end(t_game *game, t_champ **champs, t_list **prcs)
{
	t_list *cur;
	t_list *pre;
	t_process	*p;

	cur = *prcs;
	reset_prcs_c(game);
	pre = NULL;
	while (cur)
	{
		p = (t_process *)(cur->content);
		if (p->is_alive)
		{
			game->champs[-1 * p->c_id - 1]->prcs_c += 1;
			p->is_alive = 0;
			pre = (!pre) ? cur: pre->next;
			cur = cur->next;
			continue;
		}
		game->prcs_count -= 1;
		ft_lstsub(prcs, cur);
		ft_lstdelone(&cur, &del_lstprcs);
		cur = (!pre) ? *prcs : pre->next;
		pre = (cur == *prcs) ? NULL : pre;
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

int process(t_game *game)
{
	t_list *cur;
	t_process *p;
	int		win;

	reset_debug(game);
	game->cycle += 1;
	game->cycle_d -= 1;
	get_debug(game, NULL);
	if (!game->cycle_d && (win = is_end(game, &(game->champs[0]), &(game->prcs))))
		return (win);
	cur = game->prcs;
	while (cur)
	{
		p = (t_process *)(cur->content);
		if (!p->wait_c)
			prcs_inst(game, (t_process *)(cur->content));
		else
			p->wait_c -= 1;
		cur = cur->next;
	}
	print_debug(game);
	update_visu_clrmap(game->visu);
	return ((game->nbr_cycle == game->cycle) ? 1 : 0);
}
