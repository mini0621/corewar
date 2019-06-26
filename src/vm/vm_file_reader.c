/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_file_reader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 13:43:17 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/06/26 08:00:37 by mndhlovu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int              vm_is_player(char *str)
{
    if (str != NULL)
    {
        if (ft_strlen(str) > 4)
        {
            if (ft_strstr(str, ".cor"))
            return (1);
        }
    }
    return (0);
}

int                     vm_file_reader(char *file, t_game *game
                , int *flag, int *index)
{
    int                 fd;
    int                 ret;

    if (vm_is_player(file))
    {
        if ((fd = open(file, O_RDONLY)) < 0)
            return (vm_catch_error(IO_ERROR, file));
        ret = vm_primary_parser(fd, game);
        if (ret == -1)
            return (vm_catch_error(ret, NULL));
        if (ret == -2)
            return (vm_catch_error(ret, NULL));
        if (ret == -3)
            return (vm_catch_error(ret, NULL));
        if (ret == -4)
            return (vm_catch_error(ret, NULL));
		if (ret == -5)
			return (vm_catch_error(ret, file));
        *flag = 1;
        *index = *index + 1;
        return (1);
    }
    return (1);
}
