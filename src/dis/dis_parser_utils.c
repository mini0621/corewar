/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 04:56:12 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/07/02 09:04:18 by mndhlovu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int				dis_is_vfile(char *str)
{
	if (str != NULL)
	{
		if (ft_strlen(str) > 4)
		{
			if (!ft_strcmp(ft_strrchr(str, '.'), ".cor"))
				return (1);
		}
	}
	return (0);
}

int						dis_load_player(t_dis_game *game)
{
	int					nbr_champs;
	int					index;
	int					fd;

	nbr_champs = game->nbr_champs;
	index = 0;
	while (index < nbr_champs)
	{
		if (!game->file[index]->dis_state)
		{
			fd = game->file[index]->fd;
			if (((lseek(fd, 2192, SEEK_SET)) < 0)
					|| ((read(fd, &(game->dismemdump[0])
								, game->file[index]->prog_size)) < 0))
				return (-1);
			return (index);
		}
		index++;
	}
	return (-1);
}

int						dis_file_reader(char *file, t_dis_game *game
						, int *flag, int *index)
{
	int					fd;
	int					ret;

	if (dis_is_vfile(file))
	{
		if ((fd = open(file, O_RDONLY)) < 0)
			return (dis_catch_error(IO_ERROR, file));
		ret = dis_source_parser(fd, file, game);
		if (ret < 0 && ret > -5)
			return (dis_catch_error(ret, file));
		*flag = 1;
		*index = *index + 1;
		return (1);
	}
	return (1);
}
