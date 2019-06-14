/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:03:48 by sunakim           #+#    #+#             */
/*   Updated: 2019/06/14 10:48:37 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "errno.h"

static void	system_error(t_errors error)
{
	if (error == e_malloc_error)
		ft_printf("Memory Allocation Error\nSystem Error Message : %s",
			strerror(errno));
	else if (error == e_open_error)
		ft_printf("Open system function Failed\nSystem Error Message : %s",
			strerror(errno));
	else
		ft_printf("Write system function Failed\nSystem Error Message : %s",
			strerror(errno));
}

static void	input_error(char *input)
{
	ft_printf("Input file is of expected format \"file_name.s\"");
	ft_printf("Given file : \"%s\"", input);
}

static void	lexical_error(t_pos *pos, t_tkn *tkn, t_errors error)
{
	if (error == e_reg_nb_error)
		ft_printf("Lexical error at [%d : %d] - wrong register nbr\nLine : %s",
			pos->file_line, tkn->buff_start, pos->tmp_buf);
	else if (error == e_op_code_error)
		ft_printf("Lexical error at [%d : %d] - wrong op_code\nLine : %s",
			pos->file_line, tkn->buff_start, pos->tmp_buf);
	else if (error == e_dir_int_error)
		ft_printf("Lexical error at [%d : %d] - dir value > INT_MAX\nLine : %s",
			pos->file_line, tkn->buff_start, pos->tmp_buf);
	else if (error == e_dir_short_error)
		ft_printf("Lexical error at [%d : %d] - dir value > SHORT_MAX\nLine : %s",
			pos->file_line, tkn->buff_start, pos->tmp_buf);
	else if (error == e_ind_error)
		ft_printf("Lexical error at [%d : %d] - ind value > SHORT_MAX\nLine : %s",
			pos->file_line, tkn->buff_start, pos->tmp_buf);
	else if (error == e_double_label)
		ft_printf("Lexical error at [%d : %d] - double label declaration\nLine : %s",
			pos->file_line, tkn->buff_start, pos->tmp_buf);
	else
		ft_printf("Lexical error at [%d : %d]\nLine : %s",
			pos->file_line, tkn->buff_start, pos->tmp_buf);
}

static void	syntactic_error(t_pos *pos, t_tkn *tkn)
{
	ft_printf("Syntactic error at [%d : %d]\n", pos->file_line, tkn->buff_start);
	ft_printf("Line : \"%s\"", pos->buf_pos);
}

int			ft_error(t_pos *pos, t_errors error, t_tkn *tkn, char *input)
{
	if (error != e_no_print)
	{
		if (error == e_lexical_error || error == e_reg_nb_error
			|| error == e_op_code_error || error == e_dir_int_error
			|| error == e_dir_short_error || error == e_ind_error
			|| error == e_double_label)
			lexical_error(pos, tkn, error);
		else if (error == e_syntactic_error)
			syntactic_error(pos, tkn);
		else if (error == e_input_error)
			input_error(input);
		else if (error == e_malloc_error || error == e_open_error
			|| error == e_write_error)
			system_error(error);
	}
	return (0);
}
