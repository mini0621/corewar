/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:03:48 by sunakim           #+#    #+#             */
/*   Updated: 2019/06/21 16:14:35 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "errno.h"

char	*get_tkn_type_name(t_tkn_type tkn_type)
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
	char *err_str;

	err_str = strerror(errno);
	if (error == e_malloc_error)
		ft_printf(RED BLD "memory_allocation_error: " RESET "%s;\n",
			err_str);
	else if (error == e_open_error)
		ft_printf(RED BLD "open_file_error: " RESET "%s;\n",
			err_str);
	else if (error == e_empty_file)
		ft_printf(RED BLD "empty_file_error" RESET "%s;\n");
	else
		ft_printf(RED BLD "write_error: " RESET "%s;\n",
			err_str);
	ft_strdel(&err_str);
}

static void	input_error(t_pos *pos)
{
	ft_printf(RED BLD "file_error: " RESET "input file is of expected format ");
	ft_printf(WHT BLD "`file_name.s`" RESET "instead of " WHT BLD "`%s`" RESET ";",
		pos->file_name);
	free(pos->file_name);
}

static void	ft_print_expected(t_pos *pos)
{
	int	i;
	int flag;

	i = -1;
	flag = 0;
	ft_printf(RESET "expected ");
	while (++i < NB_TKN_TYPES)
	{
		if (g_syntactic_sm[pos->previous_st_s][i] != -1)
		{
			if (flag == 1)
				ft_printf(" | ");
			ft_printf(WHT BLD "`%s`" RESET, get_tkn_type_name(i));
			flag = 1;
		}
	}
}

static void	nice_display(t_pos *pos, t_tkn *tkn, char *error, char *msg)
{
	int	i;

	i = -1;
	if (pos->state_s != -1)
	{
		ft_printf(WHT "%s:%d:%d: " RED BLD "%s_error",
			pos->file_name, pos->file_line, tkn->col_start + 1, error);
		if (msg)
			ft_printf(": " RESET "%s;", msg);
		else
			ft_printf(";");
		ft_printf(RESET "\n%s", pos->tmp_buf);
	}
	else
	{
		ft_printf(WHT "%s:%d:%d: " RED BLD "%s_error: ",
			pos->file_name, pos->file_line, tkn->col_start + 1, error);
		ft_print_expected(pos);
		ft_printf(RESET " instead of " WHT BLD "`%s`" RESET ";",
			get_tkn_type_name(tkn->type), get_tkn_type_name(tkn->type), pos->tmp_buf);
		ft_printf("\n%s",pos->tmp_buf);
	}
	if (tkn->col_end != 0)
	{
		while (++i <= tkn->col_end)
		{
			if (i < tkn->col_start)
				ft_printf(" ");
			else if (i == tkn->col_start)
				ft_printf(GRN BLD "^" RESET);
			else if (i <= tkn->col_end)
				ft_printf(GRN BLD "~" RESET);
		}
	}
	else
	{
		while (++i < pos->file_col)
			ft_printf(" ");
		ft_printf(RED BLD "^" RESET);
	}
	ft_printf("\n");
}

static void	lexical_error(t_pos *pos, t_tkn *tkn, t_errors error)
{

	if (error == e_reg_nb_error)
		nice_display(pos, tkn, "lexical", "wrong_register_nbr");
	else if (error == e_op_code_error)
		nice_display(pos, tkn, "lexical", "wrong_op_code");
	else if (error == e_dir_int_error)
		nice_display(pos, tkn, "lexical", "dir_value [ > INT_MAX | < INT_MIN ]");
	else if (error == e_dir_short_error)
		nice_display(pos, tkn, "lexical", "dir_value [ > SHORT_MAX | < SHORT_MIN ]");
	else if (error == e_ind_error)
		nice_display(pos, tkn, "lexical", "ind_value [ > SHORT_MAX | < SHORT_MIN ]");
	else
		nice_display(pos, tkn, "lexical", "unexpected_chararacter");
}

static void	syntactic_error(t_pos *pos, t_tkn *tkn, t_errors error)
{
	if (error == e_double_label)
		nice_display(pos, tkn, "syntactic", "double_label_declaration");
	else
		nice_display(pos, tkn, "syntactic", NULL);
}

int			ft_error(t_pos *pos, t_errors error, t_tkn **tkn)
{
	if (error != e_no_print)
	{
		if (error == e_lexical_error || error == e_reg_nb_error
			|| error == e_op_code_error || error == e_dir_int_error
			|| error == e_dir_short_error || error == e_ind_error
			|| error == e_reg_nb_error)
			lexical_error(pos, *tkn, error);
		else if (error == e_syntactic_error || error == e_double_label)
			syntactic_error(pos, *tkn, error);
		else if (error == e_input_error)
			input_error(pos);
		else if (error == e_malloc_error || error == e_open_error
			|| error == e_write_error)
			system_error(error);
	}
	free_tkn(tkn);
	return (0);
}
