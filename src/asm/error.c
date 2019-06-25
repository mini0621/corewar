/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:03:48 by sunakim           #+#    #+#             */
/*   Updated: 2019/06/24 18:53:33 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	lexical_error(t_pos *pos, t_tkn *tkn, t_errors error)
{
	if (error == e_reg_nb_error)
		display(pos, tkn, "lexical", "wrong register_nbr");
	else if (error == e_op_code_error)
		display(pos, tkn, "lexical", "wrong op_code");
	else if (error == e_dir_int_error)
		display(pos, tkn, "lexical", "dir_value [ > INT_MAX | < INT_MIN ]");
	else if (error == e_dir_short_error)
		display(pos, tkn, "lexical", "dir_value [ > SHORT_MAX | < SHORT_MIN ]");
	else if (error == e_ind_error)
		display(pos, tkn, "lexical", "ind_value [ > SHORT_MAX | < SHORT_MIN ]");
	else
		display(pos, tkn, "lexical", "unexpected_character");
}

static void	syntactic_error(t_pos *pos, t_tkn *tkn, t_errors error)
{
	if (error == e_double_label)
		display(pos, tkn, "syntactic", "double label_declaration");
	else
		display(pos, tkn, "syntactic", NULL);
}

int			ft_error(t_pos *pos, t_errors error, t_tkn **tkn)
{
	if (pos)
		pos->error_print = 1;
	if (error != e_no_print)
	{
		if (error == e_lexical_error || error == e_reg_nb_error
			|| error == e_op_code_error || error == e_dir_int_error
			|| error == e_dir_short_error || error == e_ind_error
			|| error == e_reg_nb_error)
			lexical_error(pos, *tkn, error);
		else if (error == e_syntactic_error || error == e_double_label)
			syntactic_error(pos, *tkn, error);
		else if (error == e_input_error || error == e_no_instruction)
			input_error(pos, error);
		else if (error == e_malloc_error || error == e_open_error
			|| error == e_write_error || error == e_close_error)
			system_error(error);
		else if (error == e_name_too_long_error
			|| error == e_comment_too_long_error)
			header_error(pos, *tkn, error);
		else if (error == e_invalid_command_error)
			command_error(pos, *tkn, error);
	}
	free_tkn(tkn);
	return (0);
}
