/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:18:54 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/08 19:02:12 by mnishimo         ###   ########.fr       */
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
		if (vm_file_reader(av[index], game) < 0)
			return (0);
		index++;
	}
	if (game->deb_state)
		vm_debug(1, ac, av, game);
	return (1);
}

static void		vm_store_instr(t_game *game, unsigned char *instr
		, int flag, unsigned int size)
{
	int			dif;
	int			index;
	int			id;
	int			nbr_champs;

	nbr_champs = game->nbr_champs;
	id = (int) game->champs[flag]->id;
	dif = -(id + 1) * (MEM_SIZE / nbr_champs);
	ft_memcpy(&(game->memdump[0]) + dif, instr, sizeof(t_uc) * size);
	free(instr);
}

static int		read_champs(t_game *game)
{
	int		i;
	int		nbr_champs;
	t_list	*n;

	i = 0;
	nbr_champs = game->nbr_champs;
	ft_printf("nbr champs %i\n", game->nbr_champs);
	ft_printf("death cycle %i\n", game->cycle_d);
	while (i < nbr_champs)
	{
		vm_store_instr(game, game->champs[i]->instr, i, game->champs[i]->prog_size);
		n = prcs_new(-i - 1);
		((t_process *)(n->content))->pc = &(game->memdump[0]) + i * (MEM_SIZE / game->nbr_champs); 
		ft_lstadd(&(game->prcs), n);
		i++;
	}
	return (1);
}

int			init_corewar(t_game *game, int ac, char **av)
{
	if (!vm_init_parser(ac, av, game))
		return (0);
	if (!read_champs(game))
		return (0);
	return (1);
}
