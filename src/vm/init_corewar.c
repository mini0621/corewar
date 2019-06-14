/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:18:54 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/14 15:59:48 by mnishimo         ###   ########.fr       */
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
	// if (game->deb_state)
	// 	vm_debug(1, ac, av, game);
	return (1);
}

static int		vm_store_instr(t_game *game, int fd
		, int pos, unsigned int size)
{
	int			dif;
	int			id;
	int			nbr_champs;
	t_list	*n;

	nbr_champs = game->nbr_champs;
	id = (int) game->champs[pos]->id;
	dif = -(id + 1) * (MEM_SIZE / nbr_champs);
	if (lseek(fd, 2192, SEEK_SET) < 0
		|| read(fd, &(game->memdump[0]) + dif, size) < 0)
		return (0);
	n = prcs_new(id);
	((t_process *)(n->content))->pc = &(game->memdump[0]) + dif; 
	((t_process *)(n->content))->wait_c = decode_wait(&(game->memdump[0]) + dif);
	ft_lstadd(&(game->prcs), n);
	game->champs[pos]->color = pos;
	return (1);
}

static int		read_champs(t_game *game)
{
	int		i;
	int		nbr_champs;

	i = 0;
	nbr_champs = game->nbr_champs;
	if (!game->visu)
		ft_printf("Introducing contestants...\n");
	while (i < nbr_champs)
	{
		if (!vm_store_instr(game, game->champs[i]->fd, i, game->champs[i]->prog_size))
			return (0);
		if (!game->visu)
			ft_printf("* Player %i, weighing %u bytes, \"%s\" (\"%s\") !\n",
					i + 1, game->champs[i]->prog_size, game->champs[i]->name,
					game->champs[i]->comment);
		i++;
	}
	return (1);
}

int			init_corewar(t_game *game, int ac, char **av)
{
	if (!vm_init_parser(ac, av, game))
		return (0);
	if (!read_champs(game))
	{
		free_game(game);
		return (0);
	}
	if (game->deb_state)
		game->logs = ft_strnew(0);
	return (1);
}
