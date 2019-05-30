/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:17:05 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/30 15:52:53 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

//when the cycle_to_die is 0
//check if someone died, if so delte them from the list
//after all the prcs are checked
//see if there is still champs.
//return 1 if all the players are dead
//decrease it every time cycle_d became 0
//if cycle - cycle_c == max_check  then cycle_to_die -= cycle_delta and cycle_c = cycle
//cycle_d = cycle_to_die (reset)
static int	count_alivechamps(t_game *game, t_champ **champs)
{
	int	i;
	int	end;

	end = 0;
	i = 0;
	while ((*champs + i))
	{
		if ((*(champs + i))->live_c)
			end++;
		i++;
	}
	if (!end || end == 1)
		return (1);
	i = 0;
	while ((*champs + i))
	{
		if ((*(champs + i))->live_c)
			champs[i]->live_c = 0;
		i++;
	}
	return (0);
}

static int	is_end(t_game *game, t_champ **champs, t_list *prcs)
{
	t_list	*cur;
	t_list	*pre;

	cur = prcs;
	pre = NULL;
	while (cur)
	{
		if (((t_process *)(cur->content))->is_alive)
		{
			((t_process *)(cur->content))->is_alive = 0;
			continue ;
		}
		// sub with pre variable is better but allocated memory will change this
		ft_lstsub(&prcs, cur);
		ft_lstdel(&cur, &del_lstprcs);
		cur = (!pre) ? prcs : pre->next;
		pre = (cur == prcs) ? NULL : pre->next;
		cur = cur->next;
	}
	return (count_alivechamps(game, champs));	
}

//return 1 if the game is ended (no champ is alive)
int		process(t_game *game)
{
	t_list		*cur;
	t_process	*p;	

	if (!game->cycle_d && is_end(game, game->champs, game->prcs))
		return (1);
	//for every procss which is alive,
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
	return (0);
}
