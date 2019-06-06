/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 21:33:39 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/06 22:28:02 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>

int	read_line_asm(char **line, int *end, int check, int fd);

int	main(int argc, char **argv)
{
	char	*line;
	int		end;
	int		check;
	int		fd;
	int		size;

	if (argc == 1)
		return (printf("no file\n"));
	check = 1;
	end = 0;
	fd = open(argv[1], O_RDONLY);
	size = read_line_asm(&line, &end, check, fd);
	printf("size = %d\n", size);
	printf("%c ", *line);
	return (0);
}
