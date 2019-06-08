/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_asm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 19:29:10 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/07 16:32:50 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <stdlib.h>

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

static int	read_file(char **tmp, int *size_tmp, char **line, int *size_line, const int fd)
{
	char	buf[BUFF_SIZE_COR];
	int		ret;
	int		i;

	i = 0;
	while ((ret = read(fd, buf, BUFF_SIZE_COR)) > 0)
	{
		while (i < BUFF_SIZE_COR - 1 && buf[i] != '\n')
			i++;
		if (buf[i] == '\n')
		{
			if (!(*line = realloc(*line, *size_line + i + 1)))
				return (-1);
			ft_memcpy(*line + *size_line, buf, i + 1);
			ft_memcpy(*tmp, buf + i + 1, ret - i - 1);
			*size_tmp = ret - i - 1;
			*size_line = *size_line + i + 1;
			break ;
		}
		if (!(*line = realloc(*line, ret)))
			return (-1);
		ft_memcpy(*line + *size_line, buf, ret);
		ft_bzero(buf, BUFF_SIZE_COR);
	}
	return (ft_return_rf(ret, *size_tmp));
}

static int	read_tmp(char **tmp, int *size_tmp, char **line, int *size_line)
{
	int		flag;

	flag = 0;
	if (*tmp == NULL)
		if (!(*tmp = ft_memalloc(BUFF_SIZE_COR)))
			return (-1);
	while (*size_line < *size_tmp && tmp[0][*size_line] != '\n') // size = nb chars
	{
		line[0][*size_line] = tmp[0][*size_line];
		(*size_line)++;
	}
	if (tmp[0][*size_line] == '\n')
	{
		line[0][*size_line] = tmp[0][*size_line];
		(*size_line)++;
		flag = 1;
	}
	if (size_line)
	{
		ft_memmove(*tmp, *tmp + *size_line, *size_tmp - *size_line);
		*size_tmp = *size_tmp - *size_line;
		*line = realloc(*line, *size_line);
	}
	return (flag);
}

int			read_bytes(char **line, int error, const int fd)
{
	static char	*tmp;
	static int	size_tmp;
	int			size_line;
	char		buf[1];
	int			ret;

	if (!line || fd < 0 || read(fd, buf, 0) < 0 || BUFF_SIZE_COR <= 0)
		return (-1);
	size_line = 0;
	if (!error)
	{
		if (!(*line = ft_memalloc(BUFF_SIZE_COR)))
			return (ft_end(-1, &tmp));
		if ((ret = read_tmp(&tmp, &size_tmp, line, &size_line)) == 1) // 1 = \n - 0 = no \n - -1 error
			return (size_line);
		else if (ret == -1
			|| (ret = read_file(&tmp, &size_tmp, line, &size_line, fd)) == -1) // -1 if error, 0 if EOF
			return (ft_end(-1, &tmp));
		if (size_line || size_tmp)
			return (size_line);
	}
	return (ft_end(0, &tmp));
}
