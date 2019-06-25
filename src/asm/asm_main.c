/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 17:35:24 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/25 14:42:11 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	end_main_loop(t_pos *pos, t_tkn **tkn)
{
	if (!pos->content)
		return (ft_error(pos, e_empty_file, NULL));
	if (pos->state_l == 26)
		return (ft_error(pos, e_invalid_command_error, tkn));
	if (pos->state_s == 2 && !pos->error_print)
		return (ft_error(pos, e_no_instruction, NULL));
	else
		return (0);
}

static int	rd_anlz_enc_2(t_pos *pos, t_list **lbls)
{
	if (pos->content && pos->state_l != 26 && pos->state_s != 2
		&& !pos->end_read && end_lbl(*lbls, pos))
	{
		ft_lstdel(lbls, &del_lbls);
		return (1);
	}
	ft_lstdel(lbls, &del_lbls);
	return (0);
}

static int	read_analyze_encode_loop(int fd, t_bytebf *bytebf, t_pos *pos)
{
	t_list	*lbls;
	t_tkn	*tkn;
	char	*read_line;

	if (!(ft_init_main(&lbls, bytebf, &read_line, pos)))
		return (ft_error(NULL, e_no_print, NULL));
	while ((pos->size_line = read_bytes(&read_line, pos->end_read, fd)) > 0)
	{
		pos->content = 1;
		if (!(init_before_analysis(pos, &read_line)) && (pos->end_read = 1))
			continue ;
		if ((!syntactic_analysis(&lbls, pos, bytebf, &tkn))
			&& (pos->end_read = 1))
			continue ;
		if (pos->multiple_line)
			continue ;
		free_after_analysis(pos, &read_line);
		if (pos->ocp)
			ocp_modify(pos, bytebf->inst);
	}
	free_after_analysis(pos, &read_line);
	if (!rd_anlz_enc_2(pos, &lbls))
		return (end_main_loop(pos, &tkn));
	return (1);
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
		if (i != 0)
			return (ft_error(pos, e_input_error, NULL));
		i++;
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
	if (!(pos.file_name = ft_strdup(argv[1])))
		return (ft_error(&pos, e_malloc_error, NULL));
	if (!(file_check(argv[1], &pos)))
		return (0);
	else if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (ft_error(&pos, e_open_error, NULL));
	else if (!read_analyze_encode_loop(fd, &bytebf, &pos)
		|| !ft_write_output(&bytebf, &pos, argv[1]))
	{
		free_bytebf_pos(&bytebf, &pos);
		if (close(fd) == -1)
			return (ft_error(&pos, e_close_error, NULL));
	}
	else if (close(fd) == -1)
		return (ft_error(&pos, e_close_error, NULL));
	return (0);
}
