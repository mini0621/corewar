/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 19:25:09 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/24 16:01:51 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "visu.h"

void	free_game(t_game *game)
{
	int	i;

	ft_arrdel(&(game->prcs));
	i = 0;
	while (game->champs[i])
	{
		free(game->champs[i]);
		game->champs[i] = NULL;
		i++;
	}
	if (game->visu)
	{
		end_visu(game->visu);
		free(game->visu);
	}
}
