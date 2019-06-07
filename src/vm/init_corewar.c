/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:18:54 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/30 14:30:45 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int				vm_init_parser(int ac, char **av, t_game *game)
{
	int			index;

	index = 1;
	while (index < ac)
	{
		if (!vm_opt_reader(index, av, game))
			return (0);
		if (!vm_file_reader(av[index], game))
			return (0);
		index++;
	}
	if (game->deb_state)
		vm_debug(1, ac, av, game);
	return (1);
}

//creates process
t_process	*init_prcs(int id, t_uc *pc)
{
	return (NULL);
}


//can you please verify that I am storing the instructions in the way
//you want them. I quite understood the logic but did not find
//a better way of placing the instructions to memory
static void		vm_store_instr(t_game *game, unsigned char *instr
				, int flag, unsigned int size)
{
	int			dif;
	int			index;
	unsigned int	prog_size;
	int			id;
	int			nbr_champs;

	nbr_champs = game->nbr_champs;
	id = (int) game->champs[flag]->id;
	if (id == 0)
		id++;
	dif = id * (MEM_SIZE / nbr_champs);
	ft_memcpy(game->memdump[dif], instr, size);
}

//malloc all the champs and copy the instructions into memdump
static int		read_champs(t_game *game)
{
	int			index;
	int			nbr_champs;


	index = 0;
	nbr_champs = game->nbr_champs;
	while (index < nbr_champs)
	{
		if (!vm_store_instr(game, game->champs[index]->instr
		, index, game->champs[index]->prog_size))
			return (0);
		index++;
	}
	return (1);
}

//read all the options, store champs, init game and read infos
//if error, return 0
int			init_corewar(t_game *game, int ac, char **av)
{
	int		index;

	if (!vm_init_parser(ac, av, game))
		return (0);
	if (!read_champs(game))
		return (0);
	//create the first prcs then store them in game->prcs
	/*
	if (ac < 2 || !(arg = get_options(av)))
		return (0);
	if (!read_champs(game, arg))
		return (0);
	*/
	return (1);
}
