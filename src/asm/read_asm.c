/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_asm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 19:29:10 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/25 10:18:10 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	ft_end(int value, char **tmp)
{
	ft_memdel((void**)tmp);
	return (value);
}

static int	ft_return_rf(int ret, int size_tmp)
{
	if (ret == -1)
		return (-1);
	if (ret == 0 && size_tmp == 0)
		return (0);
	return (1);
}

static int	read_file(char **tmp, char **line, int *sizes, const int fd)
{
	char	buf[BUFF_SIZE_COR];
	int		ret;

	while ((ret = read(fd, buf, BUFF_SIZE_COR)) > 0)
	{
		sizes[2] = 0;
		while (sizes[2] < ret - 1 && buf[sizes[2]] != '\n')
			(sizes[2])++;
		if (buf[sizes[2]] == '\n')
		{
			if (!(*line = realloc(*line, sizes[1] + sizes[2] + 1)))
				return (-1);
			ft_memcpy(*line + sizes[1], buf, sizes[2] + 1);
			ft_memcpy(*tmp, buf + sizes[2] + 1, ret - sizes[2] - 1);
			sizes[0] = ret - sizes[2] - 1;
			sizes[1] = sizes[1] + sizes[2] + 1;
			break ;
		}
		if (!(*line = realloc(*line, sizes[1] + ret)))
			return (-1);
		ft_memcpy(*line + sizes[1], buf, ret);
		sizes[1] = sizes[1] + ret;
		ft_bzero(buf, BUFF_SIZE_COR);
	}
	return (ft_return_rf(ret, sizes[0]));
}

static int	read_tmp(char **tmp, char **line, int sizes[], int flag)
{
	if (*tmp == NULL)
		if (!(*tmp = ft_memalloc(BUFF_SIZE_COR)))
			return (-1);
	while (sizes[1] < sizes[0] && tmp[0][sizes[1]] != '\n')
	{
		line[0][sizes[1]] = tmp[0][sizes[1]];
		sizes[1]++;
	}
	if (sizes[0] && tmp[0][sizes[1]] == '\n')
	{
		line[0][sizes[1]] = tmp[0][sizes[1]];
		sizes[1]++;
		flag = 1;
	}
	if (sizes[1])
	{
		ft_memmove(*tmp, *tmp + sizes[1], sizes[0] - sizes[1]);
		ft_bzero(*tmp + sizes[0] - sizes[1], sizes[1]);
		sizes[0] = sizes[0] - sizes[1];
		if (!(*line = realloc(*line, sizes[1])))
			return (-1);
	}
	return (flag);
}

/*
** sizes[0] == size_tmp - sizes[1] == size_line - sizes[2] == buf_to_\n
*/

int			read_bytes(char **line, int error, const int fd)
{
	static char	*tmp;
	static int	sizes[3];
	char		buf[1];
	int			ret;
	int			flag;

	if (!line || fd < 0 || read(fd, buf, 0) < 0 || BUFF_SIZE_COR <= 0)
		return (-1);
	sizes[1] = 0;
	flag = 0;
	if (!error)
	{
		if (!(*line = ft_memalloc(BUFF_SIZE_COR)))
			return (ft_end(-1, &tmp));
		if ((ret = read_tmp(&tmp, line, sizes, flag)) == 1)
			return (sizes[1]);
		else if (ret == -1
			|| (ret = read_file(&tmp, line, sizes, fd)) == -1)
			return (ft_end(-1, &tmp));
		if (sizes[1] || sizes[0])
			return (sizes[1]);
	}
	return (ft_end(0, &tmp));
}
