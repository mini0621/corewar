/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:03:48 by sunakim           #+#    #+#             */
/*   Updated: 2019/06/21 16:53:50 by allefebv         ###   ########.fr       */
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
		ft_printf(BLD RED "memory_allocation_error: %s\n",
			err_str);
	else if (error == e_open_error)
		ft_printf(BLD RED "open_file_error: %s\n",
			err_str);
	else
		ft_printf(BLD RED "write_error: %s\n",
			err_str);
	ft_strdel(&err_str);
}

static void	input_error(t_pos *pos)
{
	ft_printf(BLD RED "file_error: " WHT "input file is of expected format ");
	ft_printf("'file_name.s' instead of '%s'\n", pos->file_name);
}

static void	print_expected_tkn(t_pos *pos, t_tkn *tkn)
{
	int	i;
	int flag;

	i = -1;
	flag = 0;
	ft_printf(WHT "expected ");
	while (++i < NB_TKN_TYPES)
	{
		if (syntactic_sm[pos->previous_st_s][i] != -1)
		{
			if (flag == 1)
				ft_printf(" | ");
			ft_printf("'%s'", get_tkn_type_name(i));
			flag = 1;
		}
	}
	ft_printf(WHT " instead of '%s'",
		get_tkn_type_name(tkn->type), get_tkn_type_name(tkn->type), pos->tmp_buf);
}

static void	print_file_name(t_pos *pos, t_tkn *tkn, char *error)
{
	ft_printf(WHT BLD "%s:%d:%d: " RED "%s_error:",
			pos->file_name, pos->file_line, tkn->buff_start + 1, error);
}

static void print_additionnal_msg(char *msg, t_pos *pos, t_tkn *tkn)
{
	if (msg)
		ft_printf(WHT " %s", msg);
	else if (pos->state_s == -1)
		print_expected_tkn(pos, tkn);
}

static void	print_line(t_pos *pos)
{
	int i;

	i = 0;
	while (pos->tmp_buf[i] != '\0' && i < pos->size_buf)
		i++;
	ft_printf(RESET "\n%s", pos->tmp_buf);
	if (i == pos->size_buf)
	{
		if (pos->tmp_buf[i - 1] != '\n')
			ft_putchar('\n');
	}
	else
		while (i < pos->size_buf)
		{
			ft_putchar(pos->tmp_buf[i]);
			i++;
		}
}

static void	print_arrow(t_pos *pos, t_tkn *tkn)
{
	int	i;

	i = -1;
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
}

static void	display(t_pos *pos, t_tkn *tkn, char *error, char *msg)
{
	print_file_name(pos, tkn, error);
	print_additionnal_msg(msg, pos, tkn);
	print_line(pos);
	print_arrow(pos, tkn);
	ft_printf("\n");
}

static void	lexical_error(t_pos *pos, t_tkn *tkn, t_errors error)
{

	if (error == e_reg_nb_error)
		display(pos, tkn, "lexical", "wrong_register_nbr");
	else if (error == e_op_code_error)
		display(pos, tkn, "lexical", "wrong_op_code");
	else if (error == e_dir_int_error)
		display(pos, tkn, "lexical", "dir_value [ > INT_MAX | < INT_MIN ]");
	else if (error == e_dir_short_error)
		display(pos, tkn, "lexical", "dir_value [ > SHORT_MAX | < SHORT_MIN ]");
	else if (error == e_ind_error)
		display(pos, tkn, "lexical", "ind_value [ > SHORT_MAX | < SHORT_MIN ]");
	else
		display(pos, tkn, "lexical", "unexpected_chararacter");
}

static void	syntactic_error(t_pos *pos, t_tkn *tkn, t_errors error)
{
	if (error == e_double_label)
		display(pos, tkn, "syntactic", "double_label_declaration");
	else
		display(pos, tkn, "syntactic", NULL);
}

static void	header_error(t_pos *pos, t_tkn *tkn, t_errors error)
{
	char *msg;

	msg = NULL;
	if (error == e_name_too_long_error)
		ft_asprintf(&msg, "champion_name_too_long : size '%d' for max '%d'",
			pos->name_len, PROG_NAME_LENGTH);
	else if (error == e_comment_too_long_error)
		ft_asprintf(&msg, "champion_comment_too_long : size '%d' for max '%d'",
			pos->comment_len, COMMENT_LENGTH);
	display(pos, tkn, "syntactic", msg);
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
		else if (error == e_name_too_long_error
			|| error == e_comment_too_long_error)
			header_error(pos, *tkn, error);
	}
	free_tkn(tkn);
	return (0);
}
