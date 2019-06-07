/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_option_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 13:33:28 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/06/07 14:57:11 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_option		 g_options[] = {
	{"-n", vm_opt_n},
	{"-d", vm_opt_dump},
	{"-de", vm_opt_debug},
	{"-a", vm_opt_aff},
	{"-s", vm_opt_soption},
	{"-v", vm_opt_visu}
};

int                     vm_opt_dump(int pos
		, char **av, t_game *game)
{
	t_ull               value;

	if (av[pos + 1] && !game->d_state)
	{
		if ((value = vm_get_value(av[pos + 1])) == (t_ull) -1)
			return (0);
		game->d_state = 1;
		game->nbr_cycle = value;
	}
	return (1);
}

int                     vm_opt_soption(int pos, char **av, t_game *game)
{
	t_ull               value;

	if (av[pos + 1] && !game->s_state)
	{
		if ((value = vm_get_value(av[pos + 1])) == (t_ull) -1)
			return (0);
		game->s_state = 1;
		game->nbr_s_cycle = value;
	}
	return (1);
}


int                     vm_opt_visu(int pos
		, char **av, t_game *game)
{
	game->visu = (t_visu *)malloc(sizeof(t_visu));
	return (1);
}


int                     vm_opt_n(int pos
		, char **av, t_game *game)
{
	t_ull               value;

	if (!game->n_state && av[pos + 1])
	{
		if ((value = vm_get_value(av[pos + 1])) == (t_ull) -1)
			return (0);
		game->n_state = 1;
		game->pl_number = value;
	}
	return (1);
}

int                     vm_opt_debug(int pos
		, char **av, t_game *game)
{
	if (av[pos] && !game->deb_state)
		game->deb_state = 1;
	return (1);
}

int                     vm_opt_aff(int pos
		, char **av, t_game *game)
{
	if (av[pos] && !game->a_state)
		game->a_state = 1;
	return (1);
}

int                     vm_opt_reader(int pos, char **av, t_game *game)
{
	int                 index;

	index = 0;
	while (index < (int)(sizeof(g_options) / sizeof(g_options[0])))
	{
		if (!ft_strcmp(av[pos], g_options[index].option))
		{
			if (!g_options[index].f(pos, av, game))
				return (vm_catch_error(OPT_ERROR, av[index]));
		}
		index++;
	}
	return (1);
}
