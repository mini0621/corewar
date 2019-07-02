/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:10:02 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/07/02 13:23:13 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void				dis_init_state(t_dis_game *game, t_game *vgame)
{
	ft_bzero(game, sizeof(t_dis_game));
	ft_bzero(vgame, sizeof(t_game));
}

static int				dis_init_parser(int ac, char **av, t_dis_game *game)
{
	int					index;
	int					e_flag;

	index = 1;
	e_flag = 0;
	while (index < ac)
	{
		if (ft_strequ(av[index], "-debug"))
		{
			game->deb_state = 1;
			index++;
			e_flag = 1;
		}
		if (!dis_file_reader(av[index], game, &e_flag, &index))
			return (0);
		if (!e_flag)
			return (dis_catch_error(IO_ERROR, av[index]));
		e_flag = 0;
	}
	return (1);
}

static int				dis_extras(t_dis_game *game)
{
	int					pl_num;

	pl_num = dis_load_player(game);
	if (pl_num == -1)
		return (-1);
	if (!dis_multi_util(game, pl_num))
		return (dis_catch_error(-2, NULL));
	dis_sub_handler(game, pl_num);
	return (pl_num);
}

int						main(int ac, char **av)
{
	t_dis_game			game;
	t_game				vgame;
	int					pl_num;
	int					flag;

	flag = 1;
	if (ac < 2)
		return (dis_catch_error(US_ERROR, NULL));
	dis_init_state(&game, &vgame);
	if (!dis_init_parser(ac, av, &game))
		return (free_all(&game));
	if (!game.deb_state)
	{
		if ((pl_num = dis_extras(&game)) != -1)
			if (!(dis_write_output(&game, pl_num)))
				return (free_all(&game));
	}
	else if (game.deb_state && ((pl_num = dis_extras(&game)) != -1))
	{
		if (!(dis_write_output(&game, pl_num)))
			return (free_all(&game));
		dis_debug(&game, pl_num);
	}
	return (free_all(&game));
}
