/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 19:25:09 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/05 21:01:08 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "visu.h"

static void	del_prcs(void *cnt, size_t size)
{
	if (size)
		free(cnt);
}

void	free_game(t_game *game)
{
	int	i;

	//free all the prcs
	ft_lstdel(&(game->prcs), &del_prcs);
	//free all the champs
	i = 0;
	while (game->champs[i])
	{
		free(game->champs[i]);
		game->champs[i] = NULL;
		i++;
	}
}
