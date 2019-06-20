/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parser_model.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 13:34:26 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/06/20 04:14:15 by mndhlovu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_ull               vm_get_value(char *sval)
{
    t_ull            value;
    t_ull            min;
    t_ull            max;

    min = (t_ull)INT_MIN;
    max = (t_ull)INT_MAX;
    if (!sval || !ft_isnumeric(sval))
        return (-1);
    value = ft_atoill(sval);
    if (value > min || value < max)
        return (value);
    return (-1);
}

// void                    vm_align_ids(t_game *game)
// {
//     int                 index;
//     int                 p_id;
//     int                 n_p_id;
//     int                 nxt_id;

//     index = 0;
//     while (index < game->nbr_champs)
//     {
//         p_id = game->champs[index]->id;
//         n_p_id = game->champs[index]->n_id;
//         if (index + 1 < game->nbr_champs)
//             nxt_id = game->champs[index + 1]->p_id;
//         if (n_p_id != 0)
//         {
//             if (p_id != n_p_id)
//             {

//             }
//         }
//     }
// }


unsigned int			vm_endian_conversion(unsigned int value)
{
	return (((value>>24) & 0x0ff)
			| ((value<<8) & 0xff0000)
			| ((value>>8) & 0xff00)
			| ((value<<24) & 0xff000000));
}



void                vm_debug(int flag, int ac, char **av, t_game *game)
{
	if (flag || ac || av || game)
		return ;
}
