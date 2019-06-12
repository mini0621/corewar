/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:17:05 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/12 16:43:58 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int count_alivechamps(t_game *game, t_champ **champs)
{
	int i;
	int end;
	int win;

	win = -1;
	end = 0;
	i = 0;
	while (i < game->nbr_champs)
	{
		if ((*champs + i)->live_c)
		{
			end++;
			win = (*champs + i)->id;
		}
		else
			get_debug(game, NULL, NULL, *champs + i);
		i++;
	}
	if (!end || end == 1)
		return (win);
	i = 0;
	while ((*champs + i))
	{
		if ((*champs + i)->live_c)
			champs[i]->live_c = 0;
		i++;
	}
	return (0);
}

static int is_end(t_game *game, t_champ **champs, t_list **prcs)
{
	t_list *cur;
	t_list *pre;

	cur = *prcs;
	pre = NULL;
	while (cur)
	{
		if (((t_process *)(cur->content))->is_alive)
		{
			((t_process *)(cur->content))->is_alive = 0;
			pre = (!pre) ? cur: pre->next;
			cur = cur->next;
			continue;
		}
		ft_lstsub(prcs, cur);
		ft_lstdelone(&cur, &del_lstprcs);
		cur = (!pre) ? *prcs : pre->next;
		pre = (cur == *prcs) ? NULL : pre;
	}
	game->cycle_to_die -= CYCLE_DELTA;
	game->cycle_d = game->cycle_to_die;
	return (count_alivechamps(game, champs));
}

int process(t_game *game)
{
	t_list *cur;
	t_process *p;
	int		win;

	reset_debug(game);
	get_debug(game, NULL, NULL, NULL);
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
	game->cycle += 1;
	game->cycle_d -= 1;
	print_debug(game);
	return ((game->nbr_cycle == game->cycle) ? 1 : 0);
}
