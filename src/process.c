/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:17:05 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/28 17:59:56 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

//when the cycle_to_die is 0
//check if someone died, if so delte them from the list
//after all the prcs are checked
//see if there is still champs.
//return 1 if all the players are dead
//???????????????????????????????????????????????? when to decrease the cycle_to_die?
//if cycle - cycle_c == max_check  then cycle_to_die -= cycle_delta and cycle_c = cycle
//cycle_d = cycle_to_die (reset)
static int	init_cycle()
{
	
}

void	process(t_game *game)
{
	t_list		*cur;
	t_process	*p;	

	if (!game->cycle_d && (game->end = init_cycle()))
		return ;
	//for every procss which is alive,
	cur = game->prcs;
	while (cur)
	{
		p = (t_process *)(cur->content);
		if (!p->wait_c)
			prcs_inst(game, champ);
		else
			p->wait_c -= 1;
		cur = cur->next;
	}
	game->cycle += 1;
	game->cycle_d -= 1;
}
