/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:14:40 by mnishimo          #+#    #+#             */
/*   Updated: 2019/07/01 17:40:12 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			print_result(t_game *game, int win)
{
	if (game->logs)
		free(game->logs);
	if (game->visu)
		return ;
	if (game->d_state)
		ft_hexdump(game->memdump);
	else if (win < 0 && win >= -game->nbr_champs)
		ft_printf("Contestant %i, \"%s\", has won\n",
			game->champs[-win - 1]->n_id, game->champs[-win - 1]->name);
}

int				main(int argc, char **argv)
{
	t_game		game;
	int			end;

	if (argc < 2)
		return (vm_catch_error(US_ERROR, NULL));
	if (!init_corewar(&game, argc, argv))
		return (0);
	if (!game.nbr_champs)
	{
		free_game(&game);
		return (vm_catch_error(US_ERROR, NULL));
	}
	end = (!game.nbr_cycle) ? 1 : 0;
	while (!end || game.visu)
	{
		if (game.visu && !output(&game))
			continue ;
		if (!end)
			end = process(&game);
	}
	print_result(&game, end);
	free_game(&game);
	return (0);
}
