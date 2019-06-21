/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 17:35:24 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/21 14:53:26 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	read_analyze_encode_loop(int fd, t_bytebf *bytebf, t_pos *pos)
{
	t_list	*lbls;
	t_tkn	*tkn;
	char	*read_line;
	int		error;
	int		flag;

	flag = 0;
	error = 0;
	if (!(ft_init_main(&lbls, bytebf, &read_line, pos)))
		return (ft_error(pos, e_no_print, NULL));
	while ((pos->size_line = read_bytes(&read_line, error, fd)) > 0)
	{
		flag = 1;
		if (!(init_before_analysis(pos, &read_line)) && (error = 1))
			continue ;
		if ((!syntactic_analysis(&lbls, pos, bytebf, &tkn)) && (error = 1))
			continue ;
		if (pos->multiple_line)
			continue ;
		free_after_analysis(pos, &read_line);
		if (pos->ocp)
			ocp_modify(pos, bytebf->inst);
	}
	free_after_analysis(pos, &read_line);
	if (flag && !error && end_lbl(lbls, pos))
	{
		ft_lstdel(&lbls, &del_lbls);
		return (1);
	}
	ft_lstdel(&lbls, &del_lbls);
	if (!flag)
		return(ft_error(pos, e_empty_file, NULL));
	return (ft_error(pos, e_no_print, NULL));
}

static int	file_check(char *str, t_pos *pos)
{
	int i;

	i = 0;
	if ((ft_strlen(str)) < 3)
		return (ft_error(pos, e_input_error, NULL));
	while (str[i] != '\0' && str[i] != '.')
		i++;
	if (str[i] == '.' && str[i + 1] != 's')
	{
		while (str[i] != '\0' && str[i] != '.')
		i++;
	}
	if (str[i] == '.' && str[i + 1] == 's' && str[i + 2] == '\0')
		return (1);
	else
		return (ft_error(pos, e_input_error, NULL));
}

int			main(int argc, char **argv)
{
	int			fd;
	t_bytebf	bytebf;
	t_pos		pos;

	if (argc != 2)
		return (0);
	ft_bzero(&pos, sizeof(t_pos));
	pos.file_name = ft_strdup(argv[1]);
	if (!(file_check(argv[1], &pos)))
		return (0);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (ft_error(&pos, e_open_error, NULL));
	if (read_analyze_encode_loop(fd, &bytebf, &pos))
		ft_write_output(&bytebf, &pos, argv[1]);
	free_bytebf_pos(&bytebf, &pos);
	return (0);
}
