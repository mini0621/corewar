/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:14:40 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/17 20:49:18 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_result(t_game *game, int win)
{
	if (game->logs)
	{
		print_debug(game);
		free(game->logs);
	}
	if (game->visu)
		return ;
	if (!game->nbr_cycle || game->cycle == game->nbr_cycle)
		ft_hexdump(game->memdump);
	else if (win < 0 && win >= -game->nbr_champs)
		ft_printf("Contestant %i, \"%s\", has won\n", -win, game->champs[-win - 1]->name);
}

int		main(int argc, char **argv)
{
	t_game	game;
	int		end;
	int		pause;

	if (argc < 2)
		return (vm_catch_error(US_ERROR, NULL));
	if (!init_corewar(&game, argc, argv))
		return (0);
	end = (!game.nbr_cycle) ? 1 : 0;
	pause = (game.visu) ?  1 : 0;
	while (!end || pause)
	{
		if (!pause || pause == 2)
			end = process(&game);
		if (game.visu)
			output(&game, &pause);
	}
	print_result(&game, end);
	if (game.visu)
		end_visu(game.visu);
	free_game(&game);
	return (0);
}
