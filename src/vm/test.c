/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:14:40 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/06 19:26:40 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "visu.h"

int	main(void)
{
	t_game	game;
	int		end;
	int		pause;

	init_visu(&game);
	end = 0;
	pause = 1;
	while (end < 10000 || pause)
	{
		output(&game, &end, &pause);
		if (!pause)
			end++;
	}
	free_game(&game);
	end_visu(&(game.visu));
	return (0);
}
