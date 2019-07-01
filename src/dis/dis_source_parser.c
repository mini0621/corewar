/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis_source_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 04:18:40 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/07/01 17:42:54 by mndhlovu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int			dis_error_exit(int fd, int flag, t_file *file)
{
	close(fd);
	free(file);
	return (flag);
}

static int			dis_verify_magic(int fd)
{
	unsigned int	magic;

	if ((read(fd, &magic, sizeof(unsigned int))) < 0)
		return (0);
	magic = dis_endian_conversion(magic);
	if (magic == (unsigned int)COREWAR_EXEC_MAGIC)
		return (fd);
	return (0);
}

static void			dis_pri_processor(char *file, int pv_number
					, t_file *champ, t_game *game)
{
	char			*tmp;
	char			*str;

	tmp = ft_strndup(file, ft_strlen(file) - 4);
	if (!(str = ft_strjoin(tmp, ".s")))
	{
		ft_strdel(&tmp);
		return ;
	}
	ft_strdel(&tmp);
	champ->output_file = str;
	champ->file_name = file;
	champ->instr_nodes = NULL;
	champ->dis_state = 0;
	champ->col = pv_number;
	game->file[pv_number] = champ;
	(game->pv_number)++;
	(game->nbr_champs)++;
	ft_strdel(&str);
}

int					dis_source_parser(int fd, char *file, t_game *game)
{
	unsigned int	prog_size;
	t_file			*new;

	if (game->pv_number < MAX_PLAYERS)
	{
		if (!(new = (t_file *)malloc(sizeof(t_file))))
			return (-2);
		if (!(fd = dis_verify_magic(fd)))
			return (dis_error_exit(fd, -1, new));
		if ((read(fd, new->name, sizeof(unsigned char) *
						PROG_NAME_LENGTH)) < 0)
			return (dis_error_exit(fd, -2, new));
		if (((lseek(fd, 136, SEEK_SET)) < 0)
				|| ((read(fd, &prog_size, sizeof(unsigned int))) < 0))
			return (dis_error_exit(fd, -2, new));
		prog_size = dis_endian_conversion(prog_size);
		if ((read(fd, new->comment, sizeof(unsigned char) *
						COMMENT_LENGTH)) < 0)
			return (dis_error_exit(fd, -2, new));
		new->fd = fd;
		new->prog_size = prog_size;
		dis_pri_processor(file, game->pv_number, new, game);
		return (1);
	}
	return (-4);
}
