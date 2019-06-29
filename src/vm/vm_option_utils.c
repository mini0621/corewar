/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_option_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 13:33:28 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/06/28 23:43:05 by mndhlovu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_option			g_options[] = {
	{"-n", vm_opt_n},
	{"-dump", vm_opt_dump},
	{"-p", vm_opt_print},
	{"-de", vm_opt_debug},
	{"-v", vm_opt_visu}
};

int					vm_opt_dump(int *pos, char **av, t_game *game)
{
	t_ull			value;

	if (av[*pos + 1] && !game->d_state)
	{
		if (!(value = vm_get_value(av[*pos + 1])))
			return (vm_catch_error(OPT_ERROR, av[*pos]));
		game->d_state = 1;
		game->nbr_cycle = value;
		*pos = *pos + 2;
		return (1);
	}
	else if (game->d_state && av[*pos + 1])
		return (vm_catch_error(-5, av[*pos]));
	else if (!game->d_state && !av[*pos + 1])
		return (vm_catch_error(OPT_ERROR, av[*pos]));
	return (vm_catch_error(OPT_ERROR, av[*pos]));
}

int					vm_opt_print(int *pos, char **av, t_game *game)
{
	t_ull			value;

	if (av[*pos + 1] && !game->print_off && !game->visu)
	{
		if (!(value = vm_get_value(av[*pos + 1])))
			return (vm_catch_error(OPT_ERROR, av[*pos]));
		game->print_off = value;
		*pos = *pos + 2;
		return (1);
	}
	else if (game->print_off && av[*pos + 1])
		return (vm_catch_error(-5, av[*pos]));
	else if (!game->print_off && !av[*pos + 1])
		return (vm_catch_error(OPT_ERROR, av[*pos]));
	return (vm_catch_error(OPT_ERROR, av[*pos]));
}

int					vm_opt_visu(int *pos, char **av, t_game *game)
{
	if (game && av && *pos)
	{
		game->visu = (t_visu *)malloc(sizeof(t_visu));
		ft_bzero(game->visu, sizeof(t_visu));
		game->visu->sp = -1;
		*pos = *pos + 1;
		game->print_off = 3;
		return (1);
	}
	return (vm_catch_error(OPT_ERROR, av[*pos]));
}

int					vm_opt_n(int *pos, char **av, t_game *game)
{
	t_ull			value;

	if (!game->n_state && av[*pos + 1]
			&& vm_is_player(av[*pos + 2]))
	{
		if (!(value = vm_get_value(av[*pos + 1])))
			return (vm_catch_error(OPT_ERROR, av[*pos]));
		game->n_state = 1;
		game->pl_number = value;
		*pos = *pos + 2;
		return (1);
	}
	else if (game->n_state && av[*pos + 1])
		return (vm_catch_error(-5, av[*pos]));
	else if (!game->n_state && !av[*pos + 1])
		return (vm_catch_error(OPT_ERROR, av[*pos]));
	return (vm_catch_error(OPT_ERROR, av[*pos]));
}

int					vm_opt_reader(int *pos, char **av
					, t_game *game, int *flag)
{
	int				index;

	index = 0;
	while (index < (int)(sizeof(g_options) / sizeof(g_options[0])))
	{
		if (!ft_strcmp(av[*pos], g_options[index].option))
		{
			if (!g_options[index].f(pos, av, game))
			{
				*flag = 0;
				return (0);
			}
			*flag = 1;
			break ;
		}
		else
			*flag = 0;
		index++;
	}
	return (1);
}
