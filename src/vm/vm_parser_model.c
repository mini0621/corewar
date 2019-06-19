/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parser_model.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 13:34:26 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/06/11 03:09:20 by mnishimo         ###   ########.fr       */
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
    ft_printf("Bingo: %s\n", sval);
    if (value > min || value < max)
        return (value);
    return (-1);
}


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
