/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 15:58:29 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/24 17:46:20 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <errno.h>

void	system_error(t_errors error)
{
	char *err_str;

	(void)error;
	err_str = strerror(errno);
	if (error == e_malloc_error)
		ft_printf("\e[1m\e[031mmemory_allocation error: \e[037m%s\n\e[0m",
			err_str);
	else if (error == e_open_error)
		ft_printf("\e[1m\e[031mopen_file error: \e[037m%s\n\e[0m", err_str);
	else if (error == e_empty_file)
		ft_printf("\e[1m\e[031mempty_file error:\n\e[0m");
	else if (error == e_write_error)
		ft_printf("\e[1m\e[031mwrite_error: \e[037m%s\n\e[0m", err_str);
	else if (error == e_close_error)
		ft_printf("\e[1m\e[031mclose_error: \e[037m%s\n\e[0m", err_str);
	ft_strdel(&err_str);
}

void	header_error(t_pos *pos, t_tkn *tkn, t_errors error)
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
	ft_strdel(&msg);
}

void	command_error(t_pos *pos, t_tkn *tkn, t_errors error)
{
	(void)error;
	if (pos->state_l == 26)
		display(pos, tkn, "lexical", "command: missing ending double_quote");
	else
		display(pos, tkn, "lexical", "unknown command");
}

void	input_error(t_pos *pos, t_errors error)
{
	ft_printf("\e[1m\e[031mfile_error: ");
	if (error == e_input_error)
	{
		ft_printf("\e[037minput file is of expected format ");
		ft_printf("'file_name.s' instead of '%s'\n", pos->file_name);
	}
	else
		ft_printf("\e[037mno instructions in file\n");
}
