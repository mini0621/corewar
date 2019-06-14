/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:14:40 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/14 16:06:43 by mnishimo         ###   ########.fr       */
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
	vm_init_flags(&game);
	if (!init_corewar(&game, argc, argv))
		return (0);
	if (game.visu)
		vm_init_visu(&game, game.visu);
	end = (!game.nbr_cycle) ? 1 : 0;
	pause = (game.visu) ?  1 : 0;
	while (!end || pause)
	{
		if (!game.pause || !pause)
			end = process(&game);
		if (game.visu)
			if (!output(&game, &pause))
				break ;
	}
	print_result(&game, end);
	if (game.visu)
		end_visu(game.visu);
	free_game(&game);
	getch();
	endwin();
	return (0);
}
