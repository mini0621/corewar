/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_asm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 19:29:10 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/06 21:29:50 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	ft_end(int value, char **tmp)
{
	ft_memdel(tmp);
	return (value);
}

static int	ft_return_rf(int ret, int size_tmp)
{
	if (ret == -1)
		return (-1);
	if (ret == 0 && *size_tmp == 0)
		return (0);
	return (1);
}

static int	read_file(char **tmp, int *size_tmp, char **line, int *size_line)
{
	char	buf[BUFF_SIZE];
	int		ret;
	int		i;
	
	i = 0;
	while (ret = read(0, buf, BUFF_SIZE) > 0)
	{
		while (i < BUFF_SIZE && buff[i] != '\n')
			i++;
		if (buf[i] == '\n')
		{
			if (!(ft_realloc(*line, *size_line + i + 1)))
				return (-1);
			ft_memcpy(*line + *size_line, buf, i + 1);
			ft_memcpy(*tmp, buf + i + 1, BUFF_SIZE - i - 1);
			*size_tmp = BUFF_SIZE - i - 1;
			*size_line = *size_line + i + 1;
			break ;
		}
		if (!(ft_realloc(*line, BUFF_SIZE)))
			return (-1);
		ft_memcpy(*line + *size_line, buf, BUFF_SIZE);
		ft_bzero(buf, BUFF_SIZE);
	}
	return (ft_return_rf(ret, size_tmp));
}

static int	read_tmp(char **tmp, int *size_tmp, char **line, int *size_line)
{
	int		flag;

	flag = 0;
	*size_line = 0;
	if (*tmp == NULL)
		if (!(*tmp = ft_memalloc(BUFF_SIZE)))
			return (-1);
	while (*size_line < *size_tmp && tmp[*size_line] != '\n') // size = nb chars
	{
		line[0][size_line] = tmp[0][size_line];
		*size_line++;
	}
	if (tmp[*size_line] == '\n')
	{
		line[0][size_line] = tmp[0][size_line];
		*size_line++;
		flag = 1;
	}
	if (size_line)
	{
		ft_memmove(*tmp, *tmp + *size_line, *size_tmp - *size_line);
		*size_tmp = *size_tmp - *size_line;
		realloc(*line, size_line);
	}
	return (flag);
}

int			read_line_asm(char **line, int *end, int check)
{
	static char	*tmp;
	static int	size_tmp;
	int			size_line;
	char		buf[1];
	int			ret;

	if (!line || read(0, buf, 0) < 0 || BUFF_SIZE <= 0)
		return (-1);
	if (!check)
	{
		if (!(line = ft_memalloc(BUFF_SIZE)))
			return (ft_end(-1, &tmp));
		if ((ret = read_inside_tmp()) == 1) // 1 = \n - 0 = no \n - -1 error
			return (line_size);
		else if (ret == -1
			|| (ret = ft_read_file()) == -1) // -1 if error, 0 if EOF
			return (ft_end(-1, &tmp));
		else if (ret == 0)
		{
			*end = 1;
			return (ft_end(line_size, &tmp));
		}
		return (size_line);
	}
	return (ft_end(0, &tmp));
}
