/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parser_model.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 13:34:26 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/06/29 16:20:33 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_ull				vm_get_value(char *sval)
{
	t_ull			value;
	t_ull			min;
	t_ull			max;

	min = (t_ull)INT_MIN;
	max = (t_ull)INT_MAX;
	if (!sval || !ft_isnumeric(sval))
		return (0);
	value = ft_atoill(sval);
	if (value > 0 && value < max)
		return (value);
	return (0);
}

static void			vm_sub_sort_champ(t_game *game)
{
	int				index;

	index = -1;
	while (++index < game->nbr_champs)
		game->champs[index]->id = (1 + index) * -1;
}

void				vm_sort_champ_id(t_game *game)
{
	t_champ			*champ;
	int				id;
	int				index;
	int				nbr_champs;

	index = -1;
	id = 0;
	nbr_champs = game->nbr_champs;
	while (++index < (nbr_champs - 1))
	{
		id = 0;
		while (id < (nbr_champs - index - 1))
		{
			if (game->champs[id]->id < game->champs[id + 1]->id)
			{
				champ = game->champs[id];
				game->champs[id] = game->champs[id + 1];
				game->champs[id + 1] = champ;
			}
			id++;
		}
	}
	vm_sub_sort_champ(game);
}

int					vm_opt_debug(int *pos, char **av, t_game *game)
{
	t_ull			value;

	if (av[*pos] && !game->deb_state)
	{
		if (!(value = vm_get_value(av[*pos + 1])))
			return (vm_catch_error(OPT_ERROR, av[*pos]));
		game->deb_state = value;
		*pos = *pos + 2;
		return (1);
	}
	else if (game->deb_state && av[*pos + 1])
		return (vm_catch_error(-5, av[*pos]));
	else if (!game->deb_state && !av[*pos + 1])
		return (vm_catch_error(OPT_ERROR, av[*pos]));
	return (vm_catch_error(OPT_ERROR, av[*pos]));
}

unsigned int		vm_endian_conversion(unsigned int value)
{
	return (((value >> 24) & 0x0ff)
			| ((value << 8) & 0xff0000)
			| ((value >> 8) & 0xff00)
			| ((value << 24) & 0xff000000));
}
