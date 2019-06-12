/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:14:40 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/11 03:04:54 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_result(t_game *game, int win)
{
	if (game->cycle != game->nbr_cycle)
		ft_printf("winner is player %i\n", win);
}

int		main(int argc, char **argv)
{
	t_game	game;
	t_visu	visu;
	int		end;
	int		pause;

	if (argc < 2)
		return (vm_catch_error(US_ERROR, NULL));
	vm_init_flags(&game);
	if (!init_corewar(&game, argc, argv))
		return (0);
	if (game.visu)
	{
		//init_visu(&game, game.visu);
		pause = (game.visu) ?  1 : 0;
		vm_init_visu(&game, game.visu);
		//visu_launcher(&game, &visu);
	}
	end = 0;
	pause = (game.visu) ?  1 : 0;
	while (!end || pause)
	{
		if (!pause)
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
