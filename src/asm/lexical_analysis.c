/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 13:48:45 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/25 16:12:16 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	check_state_l(t_pos *pos, t_tkn **tkn)
{
	if (pos->state_l != 26)
	{
		if (!(*tkn = (t_tkn*)ft_memalloc(sizeof(t_tkn))))
			return (ft_error(pos, e_malloc_error, tkn));
		pos->state_l = 0;
		(*tkn)->buff_start = pos->buf_pos;
		(*tkn)->col_start = pos->file_col;
		(*tkn)->value = NULL;
	}
	else
	{
		pos->file_col = 0;
		pos->tab_counter = 0;
	}
	return (1);
}

static void	ft_move_positions(t_pos *pos, t_tkn *tkn)
{
	if (pos->state_l == 0)
	{
		tkn->buff_start++;
		if (pos->tmp_buf[pos->buf_pos] == '\t')
			tkn->col_start = tkn->col_start + 8 - pos->tab_counter;
		else
			tkn->col_start++;
	}
	if (pos->tmp_buf[pos->buf_pos] == '\t')
	{
		pos->file_col = pos->file_col + 8 - pos->tab_counter;
		pos->nb_tab++;
		pos->tab_counter = 0;
	}
	else
		pos->file_col++;
	if (pos->tmp_buf[pos->buf_pos] != '\t')
		pos->tab_counter++;
	if (pos->tab_counter == 8)
		pos->tab_counter = 0;
	pos->buf_pos++;
}

static int	find_char_type(t_pos *pos, int i)
{
	i = 0;
	if (pos->tmp_buf[pos->buf_pos] != 0)
	{
		while (i < NB_LSM_COL && !ft_strchr(g_lsm_col[i],
			pos->tmp_buf[pos->buf_pos]))
			i++;
	}
	else
		i = 13;
	return (i);
}

int			lexical_analysis(t_pos *pos, t_tkn **tkn, t_list **lbls)
{
	int	i;
	int	ret;

	if (check_state_l(pos, tkn) == 0)
		return (ft_error(NULL, e_no_print, tkn));
	while (pos->state_l != -1 && pos->buf_pos < pos->size_buf)
	{
		i = find_char_type(pos, i);
		pos->state_l = g_lex_sm[pos->state_l][i];
		if (pos->state_l == -1)
			break ;
		if ((ret = final_state(pos, tkn, pos->tmp_buf, lbls)) == 1)
			return (1);
		else if (!ret)
			return (ft_error(NULL, e_no_print, tkn));
		ft_move_positions(pos, *tkn);
	}
	if (pos->state_l == 26)
	{
		pos->multiple_line = 1;
		return (1);
	}
	return (ft_error(pos, e_lexical_error, tkn));
}
