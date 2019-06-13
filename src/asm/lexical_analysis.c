/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 13:48:45 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/13 15:24:15 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	check_state_l(t_pos *pos, t_tkn **tkn)
{
	if (pos->state_l != 24)
	{
		if (!(*tkn = (t_tkn*)ft_memalloc(sizeof(t_tkn))))
			return (0);
		pos->state_l = 0;
		(*tkn)->buff_start = pos->buf_pos;
	}
	return (1);
}

static int	final_state(t_pos *pos, t_tkn *tkn, char *buf, t_list **lbls)
{
	if (lex_sm[pos->state_l][0] == -2 || lex_sm[pos->state_l][0] == -3)
	{
		pos->multiple_line = 0;
		if (lex_sm[pos->state_l][0] == -3)
			pos->buf_pos--;
		tkn->buff_end = pos->buf_pos;
		tkn_create(buf, pos, lbls, tkn);
		pos->buf_pos++;
		return (1);
	}
	return (0);
}

int			lexical_analysis(t_pos *pos, t_tkn **tkn, t_list **lbls)
{
	int	i;

	if (check_state_l(pos, tkn) == 0)
		return (0);
	while (pos->state_l != -1 && pos->buf_pos < pos->size_buf)
	{
		i = 0;
		while (i < NB_LSM_COL && !ft_strchr(lsm_col[i], pos->tmp_buf[pos->buf_pos]))
			i++;
		pos->state_l = lex_sm[pos->state_l][i];
		if (pos->state_l == -1)
			break;
		if (pos->state_l == 0)
			(*tkn)->buff_start++;
		if (final_state(pos, *tkn, pos->tmp_buf, lbls))
			return (1);
		pos->buf_pos++;
	}
	if (pos->state_l == 24)
	{
		pos->multiple_line = 1;
		return (2);
	}
	error(pos, 1, *tkn); // handle more properly
	return (0);
}
