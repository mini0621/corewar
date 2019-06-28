/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:18:54 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/28 10:51:10 by mndhlovu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int			vm_init_parser(int ac, char **av, t_game *game)
{
	int				index;
	int				er_flag;

	index = 1;
	er_flag = 0;
	while (index < ac)
	{
		if (!vm_opt_reader(&index, av, game, &er_flag))
			return (0);
		if (!vm_file_reader(av[index], game, &er_flag, &index))
			return (0);
		if (!er_flag)
			return (vm_catch_error(IO_ERROR, av[index]));
	}
	return (1);
}

static void			init_clr_map(t_game *game, int c_id
					, int dif, unsigned int size)
{
	unsigned int	i;
	short			*map;

	i = 0;
	map = &(game->visu->clr_map[0]);
	while (i < size)
	{
		map[dif + i] = -1 * c_id;
		i++;
	}
}

static int			vm_store_instr(t_game *game, int fd
					, int pos, unsigned int size)
{
	int				dif;
	int				id;
	int				nbr_champs;

	nbr_champs = game->nbr_champs;
	id = (int)game->champs[pos]->id;
	dif = -(id + 1) * (MEM_SIZE / nbr_champs);
	if (lseek(fd, 2192, SEEK_SET) < 0
		|| read(fd, &(game->memdump[0]) + dif, size) < 0)
		return (0);
	if (prcs_new(game, id, game->memdump + dif, game->prcs) < 0)
		return (0);
	if (game->visu)
		init_clr_map(game, id, dif, size);
	return (1);
}

static int			read_champs(t_game *game)
{
	int				i;
	int				nbr_champs;

	i = 0;
	nbr_champs = game->nbr_champs;
	if (!game->visu && nbr_champs)
		ft_printf("Introducing contestants...\n");
	while (i < nbr_champs)
	{
		if (!vm_store_instr(game, game->champs[i]->fd
					, i, game->champs[i]->prog_size))
			return (0);
		if (!game->visu)
			ft_printf("* Player %i, weighing %u bytes, \"%s\" (\"%s\") !\n",
					i + 1, game->champs[i]->prog_size, game->champs[i]->name,
					game->champs[i]->comment);
		i++;
	}
	return (1);
}

int					init_corewar(t_game *game, int ac, char **av)
{
	vm_init_flags(game);
	if (!vm_init_parser(ac, av, game))
	{
		free_game(game);
		return (0);
	}
	vm_sort_champ_id(game);
	if (!(game->prcs = ft_arrnew(sizeof(t_process), game->nbr_champs * 10)))
		return (0);
	if (!read_champs(game))
	{
		free_game(game);
		return (0);
	}
	if (game->deb_state)
		game->logs = ft_strnew(0);
	if (game->visu)
		init_visu(game, game->visu);
	return (1);
}
