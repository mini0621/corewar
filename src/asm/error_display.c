/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 14:42:46 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/23 19:13:16 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	print_file_name(t_pos *pos, t_tkn *tkn, char *error, char *msg)
{
	if (msg && strstr(msg, "unex"))
		ft_printf("\e[037m\e[1m%s:%d:%d: \e[031m%s_error: ",
			pos->file_name, pos->file_line, pos->buf_pos + 1, error);
	else
		ft_printf("\e[037m\e[1m%s:%d:%d: \e[031m%s_error: ",
			pos->file_name, pos->file_line, tkn->buff_start + 1, error);
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
		if (g_syntactic_sm[pos->previous_st_s][i] != -1)
		{
			if (flag == 1)
				ft_printf(" | ");
			ft_printf("'%s'", get_tkn_type_name(i));
			flag = 1;
		}
	}
	ft_printf(WHT " instead of '%s'",
		get_tkn_type_name(tkn->type),
		get_tkn_type_name(tkn->type), pos->tmp_buf);
}

static void	print_line_or_msg(t_pos *pos, t_tkn *tkn, char *msg, char type)
{
	int i;

	if (type == 'L')
	{
		i = -1;
		ft_printf("\e[0m\n");
		while (++i < pos->size_buf)
			ft_putchar(pos->tmp_buf[i]);
	}
	else if (type == 'M')
	{
		if (msg)
			ft_printf("\e[037m%s", msg);
		else if (pos->state_s == -1)
			print_expected_tkn(pos, tkn);
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
				ft_printf("\e[032m\e[1m^\e[0m");
			else if (i <= tkn->col_end)
				ft_printf("\e[032m\e[1m~\e[0m");
		}
	}
	else
	{
		while (++i < pos->file_col)
			ft_printf(" ");
		ft_printf("\e[031m\e[1m^\e[0m");
	}
}

void		display(t_pos *pos, t_tkn *tkn, char *error, char *msg)
{
	print_file_name(pos, tkn, error, msg);
	print_line_or_msg(pos, tkn, msg, 'M');
	print_line_or_msg(pos, tkn, msg, 'L');
	if ((msg && !strstr(msg, "missing")) || pos->state_s == -1)
	{
		print_arrow(pos, tkn);
		ft_printf("\n");
	}
}
