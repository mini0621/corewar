/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:14:40 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/11 03:59:11 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_result(t_game *game, int win)
{
	if (win > 0)
		ft_hexdump(game->memdump);
	else if (game->cycle != game->nbr_cycle)
		ft_printf("winner is player %i\n", win);
	else
		ft_hexdump(game->memdump);
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
		init_visu(&game, game.visu);
	end = 0;
	pause = (game.visu) ?  1 : 0;
	while (!end || pause)
	{
		if (!pause)
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
