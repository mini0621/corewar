/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 04:18:12 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/07/01 17:42:32 by mndhlovu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void				dis_init_state(t_game *game)
{
	game->deb_state = 0;
	game->nbr_champs = 0;
	game->visu_state = 0;
	game->deb_state = 0;
	game->pv_number = 0;
	game->length = 0;
	game->store = NULL;
	if (!(game->visu = (t_visu *)malloc(sizeof(t_visu))))
		return ;
	ft_bzero(game->visu, sizeof(t_visu));
	ft_bzero(&(game->dismemdump[0]), CHAMP_MAX_SIZE * sizeof(t_uc));
}

static int			dis_init_parser(int ac, char **av, t_game *game)
{
	int				index;
	int				e_flag;

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
		if (ft_strequ(av[index], "-v"))
		{
			game->visu_state = 1;
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

static int          dis_extras(t_game *game)
{
    int             pl_num;
    pl_num = vm_load_player(game);
    if (pl_num == -1)
        return (-1);
    if (!dis_multi_util(game, pl_num))
        return (dis_catch_error(-2, NULL));
    dis_sub_handler(game, pl_num);
    return (pl_num);
}

static int			dis_free_game(t_game *game)
{
	int				i;

	i = 0;
	while (game->file[i])
	{
		free(game->file[i]);
		game->file[i] = NULL;
		i++;
	}
	if (game->visu)
	{
		dis_end_visu(game->visu);
		free(game->visu);
	}
	return (0);
}

int					main(int ac, char **av)
{
	t_game			game;
	int				pl_num;
	int				flag;

    flag = 1;
    if (ac < 2)
        return (dis_catch_error(US_ERROR, NULL));
    dis_init_state(&game);
    if (!dis_init_parser(ac, av, &game))
        return (dis_free_game(&game));
    if (!game.deb_state && !game.visu_state)
    {
        while ((pl_num = dis_extras(&game)) != -1)
            if (!(dis_write_output(&game, pl_num)))
                return (dis_free_game(&game));
    }
    if (game.deb_state && !game.visu_state)
    {
        ft_printf("\t\tDEBUG MODE\t\t\n");
        while ((pl_num = dis_extras(&game)) != -1)
        {
            if (!(dis_write_output(&game, pl_num)))
                return (0);
            dis_debug(&game, pl_num);
        }
    }
    if (game.visu_state && !game.deb_state)
    {
        pl_num = dis_extras(&game);
        if (pl_num != -1)
			while (flag)
				dis_output(&game, pl_num, &flag);  
    }
    return (dis_free_game(&game));
}
