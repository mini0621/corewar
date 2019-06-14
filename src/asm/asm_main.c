/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 17:35:24 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/14 09:44:20 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <fcntl.h>

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
	return (ft_error(pos, e_no_print, tkn, NULL));
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
		return (ft_error(&pos, e_open_error, NULL, NULL));
	if (read_analyze_encode_loop(fd, &bytebf, &pos))
		ft_write_output(&bytebf, &pos, argv[1]);
	return (0);
}
