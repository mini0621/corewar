/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 17:35:24 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/13 15:00:55 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <fcntl.h>

void	fill_bytefb(t_bytebf *bytebf, t_pos *pos)
{
	bytebf->hd_size = 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4;
	bytebf->header = (char *)ft_memalloc(bytebf->hd_size);  //malloc protection!
	ft_memcpy(bytebf->header, bytebf->magic, 4);
	ft_memcpy(bytebf->header + 4, bytebf->name, PROG_NAME_LENGTH);
	ft_memcpy(bytebf->header + 4 + PROG_NAME_LENGTH, bytebf->offset1, 4);
	ft_memcpy(bytebf->header + 8 + PROG_NAME_LENGTH, "size", 4); // change program size
	ft_memcpy(bytebf->header +  12 + PROG_NAME_LENGTH, bytebf->comment, COMMENT_LENGTH);
	ft_memcpy(bytebf->header + 12 + PROG_NAME_LENGTH + COMMENT_LENGTH, bytebf->offset2, 4);

	bytebf->bytebuf = (char *)ft_memalloc(bytebf->hd_size + pos->lc_tkn);
	ft_memcpy(bytebf->bytebuf, bytebf->header, bytebf->hd_size);
	ft_memcpy(bytebf->bytebuf + bytebf->hd_size, bytebf->inst, pos->lc_tkn);
}

static int	read_analyze_encode_loop(int fd, t_bytebf *bytebf, t_pos *pos)
{
	t_list	*lbls;
	t_tkn	*tkn;
	char	*read_line;
	int		error;

	error = 0;
	ft_init_main(&lbls, bytebf, &read_line, pos);
	while ((pos->size_line = read_bytes(&read_line, error, fd)) > 0)
	{
		init_before_analysis(pos, &read_line);
		if ((!syntactic_analysis(&lbls, pos, bytebf, &tkn)) && (error = 1))
			continue ;
		if (pos->multiple_line)
			continue ;
		free_after_analysis(pos, &read_line);
		if (pos->ocp)
			ocp_modify(pos, bytebf->inst);
	}
	free_after_analysis(pos, &read_line);
	if (!error && end_lbl(lbls))
		return (1);
	return (0);
}

int		main(int argc, char **argv)
{
	int			fd;
	int			end;
	t_bytebf	bytebf;
	t_pos		pos;

	if (argc != 2)
		return (0);
	// check if file is valide (file name, ext)
	end = 0;
	if ((fd = open(argv[1], O_RDONLY)) < 0)
	{
		ft_printf("error\n"); // handle more properly
		return (0);
	}
	if (read_analyze_encode_loop(fd, &bytebf, &pos))
		ft_write_output(&bytebf, &pos, argv[1]);
	return (0);
}
