/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:03:48 by sunakim           #+#    #+#             */
/*   Updated: 2019/06/17 19:32:00 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "errno.h"

static char	*get_tkn_type_name(t_tkn_type tkn_type)
{
	if (tkn_type == e_cmd_name)
		return ("cmd_name");
	else if (tkn_type == e_cmd_comment)
		return ("cmd_comment");
	else if (tkn_type == e_op)
		return ("op_code");
	else if (tkn_type == e_lbl)
		return ("label_declaration");
	else if (tkn_type == e_ind_label)
		return ("ind_label");
	else if (tkn_type == e_ind_value)
		return ("ind_value");
	else if (tkn_type == e_dir_label)
		return ("dir_label");
	else if (tkn_type == e_dir_value)
		return ("dir_value");
	else if (tkn_type == e_separator)
		return ("separator");
	else if (tkn_type == e_carriage_return)
		return ("carriage_return");
	else if (tkn_type == e_eof)
		return ("end_of_file");
	else if (tkn_type == e_register)
		return ("register");
	return ("SHOULD NOT HAPPEN");
}

static void	system_error(t_errors error)
{
	if (error == e_malloc_error)
		ft_printf("\e[0m\e[031m\e[1mmemory_allocation_error: \e[0m%s",
			strerror(errno));
	else if (error == e_open_error)
		ft_printf("\e[0m\e[031m\e[1mopen_file_error: \e[0m%s",
			strerror(errno));
	else
		ft_printf("\e[0m\e[031m\e[1mwrite_error: %s",
			strerror(errno));
}

static void	input_error(t_pos *pos)
{
	ft_printf("\e[0m\e[031m\e[1mfile_error: \e[0minput file is of expected format \e[037m\e[1m`file_name.s`\e[0m instead of \e[037m\e[1m`%s`\e[0m;", pos->file_name);
}

static void	ft_print_expected(t_pos *pos)
{
	int	i;
	int flag;

	i = -1;
	flag = 0;
	ft_printf("\e[0mexpected ");
	while (++i < NB_TKN_TYPES)
	{
		if (syntactic_sm[pos->previous_st_s][i] != -1)
		{
			if (flag == 1)
				ft_printf(" | ");
			ft_printf("\e[037m\e[1m`%s`\e[0m", get_tkn_type_name(i));
			flag = 1;
		}
	}
}

static void	nice_display(t_pos *pos, t_tkn *tkn, char *error, char *msg)
{
	int	i;
	int	j;

	j = -1;
	i = -1;
	if (pos->state_s != -1)
		ft_printf("\e[037m%s:%d:%d: \e[0m\e[031m\e[1m%s_error: \e[0m%s;\n%s",
		pos->file_name, pos->file_line, tkn->buff_start + 1, error, msg, pos->tmp_buf);
	else
	{
		ft_printf("\e[037m%s:%d:%d: \e[0m\e[031m\e[1m%s_error: ",pos->file_name, pos->file_line, tkn->buff_start + 1, error);
		ft_print_expected(pos);
		ft_printf("\e[0m instead of \e[037m\e[1m`%s`\e[0m;", get_tkn_type_name(tkn->type), get_tkn_type_name(tkn->type), pos->tmp_buf);
		ft_printf("\n%s",pos->tmp_buf);
	}
	if (tkn->col_end != 0)
	{
		while (++i <= tkn->col_end)
		{
			if (i < tkn->col_start)
				ft_printf(" ");
			else if (i == tkn->col_start)
				ft_printf("\e[032m\e[1m^\e[0m");
			else if (i <= tkn->col_end)
				ft_printf("\e[032m\e[1m~\e[0m");
		}
	}
	else
	{
		while (++i <= pos->buf_pos)
		{
			if (i < tkn->col_start)
				ft_printf(" ");
			else if (i < pos->buf_pos)
				ft_printf("\e[032m\e[1m~\e[0m");
			else
				ft_printf("\e[032m\e[1m^\e[0m");
		}
	}
	ft_printf("\n");
}

static void	lexical_error(t_pos *pos, t_tkn *tkn, t_errors error)
{

	if (error == e_reg_nb_error)
		nice_display(pos, tkn, "lexical", "wrong register nbr");
	else if (error == e_op_code_error)
		nice_display(pos, tkn, "lexical", "wrong op_code");
	else if (error == e_dir_int_error)
		nice_display(pos, tkn, "lexical", "dir value > INT_MAX");
	else if (error == e_dir_short_error)
		nice_display(pos, tkn, "lexical", "dir value > SHORT_MAX");
	else if (error == e_ind_error)
		nice_display(pos, tkn, "lexical", "ind value > SHORT_MAX");
	else
		nice_display(pos, tkn, "lexical", "unexpected chararacter");
}

static void	syntactic_error(t_pos *pos, t_tkn *tkn, t_errors error)
{
	nice_display(pos, tkn, "syntactic", NULL);
	if (error == e_double_label)
		ft_printf("double label declaration");
}

int			ft_error(t_pos *pos, t_errors error, t_tkn *tkn)
{
	if (error != e_no_print)
	{
		if (error == e_lexical_error || error == e_reg_nb_error
			|| error == e_op_code_error || error == e_dir_int_error
			|| error == e_dir_short_error || error == e_ind_error
			|| error == e_reg_nb_error)
			lexical_error(pos, tkn, error);
		else if (error == e_syntactic_error || error == e_double_label)
			syntactic_error(pos, tkn, error);
		else if (error == e_input_error)
			input_error(pos);
		else if (error == e_malloc_error || error == e_open_error
			|| error == e_write_error)
			system_error(error);
	}
	return (0);
}
