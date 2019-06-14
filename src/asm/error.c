/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:03:48 by sunakim           #+#    #+#             */
/*   Updated: 2019/06/14 16:44:38 by allefebv         ###   ########.fr       */
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
	ft_printf("\nInput file is of expected format \"file_name.s\"");
	ft_printf("\nGiven file : \"%s\"", input);
}

static void	nice_display(t_pos *pos, t_tkn *tkn, char *error)
{
	int	i;
	int	j;

	j = -1;
	i = -1;
	ft_printf("\n\e[033m[%d : %d]\e[0m - \e[031m\e[1m%s Error\e[0m\n\e[3m%s\e[0m",
		pos->file_line, tkn->buff_start + 1, error, pos->tmp_buf);
	while (++i + 2 < pos->file_col - (pos->buf_pos - tkn->buff_start))
		ft_printf(" ");
	while (--i > 0 && ++j < 2)
		ft_printf("\e[032m\e[1m~");
	ft_printf("\e[032m\e[1m^~~\e[0m\n");
}

static void	lexical_error(t_pos *pos, t_tkn *tkn, t_errors error)
{
	nice_display(pos, tkn, "Lexical");
	if (error == e_reg_nb_error)
		ft_printf("wrong register nbr");
	else if (error == e_op_code_error)
		ft_printf("wrong op_code");
	else if (error == e_dir_int_error)
		ft_printf("dir value > INT_MAX");
	else if (error == e_dir_short_error)
		ft_printf("dir value > SHORT_MAX");
	else if (error == e_ind_error)
		ft_printf("ind value > SHORT_MAX");
	else if (error == e_double_label)
		ft_printf("double label declaration");
}

static void	syntactic_error(t_pos *pos, t_tkn *tkn)
{
	nice_display(pos, tkn, "Syntactic");
	write(1, "\n", 1);
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
