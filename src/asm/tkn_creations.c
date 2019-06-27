/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_creations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 21:35:32 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/27 17:21:08 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	tkn_create(char *buf, t_pos *pos, t_list **lbls, t_tkn **tkn)
{
	int			j;
	t_tkn_fptr	fptr[NB_TKN_TYPES];

	fptr[0] = &tkn_label;
	fptr[1] = &tkn_register;
	fptr[2] = &tkn_op;
	fptr[3] = &tkn_dir_value;
	fptr[4] = &tkn_dir_label;
	fptr[5] = &tkn_ind_value;
	fptr[6] = &tkn_ind_label;
	fptr[7] = &tkn_cmd;
	fptr[8] = &tkn_separator;
	fptr[9] = &tkn_carr_ret;
	j = 0;
	while (j < NB_TKN_TYPES)
	{
		if (j == g_lex_sm[pos->state_l][1])
		{
			if (!(fptr[j](buf, pos, lbls, tkn)))
				return (ft_error(NULL, e_no_print, tkn));
			break ;
		}
		j++;
	}
	return (1);
}

int	final_state(t_pos *pos, t_tkn **tkn, char *buf, t_list **lbls)
{
	if (g_lex_sm[pos->state_l][0] == -2 || g_lex_sm[pos->state_l][0] == -3)
	{
		pos->multiple_line = 0;
		if (g_lex_sm[pos->state_l][0] == -3)
		{
			pos->buf_pos--;
			pos->file_col--;
		}
		else
			pos->tab_counter++;
		if (pos->tab_counter == 8)
			pos->tab_counter = 0;
		(*tkn)->buff_end = pos->buf_pos;
		(*tkn)->col_end = pos->file_col;
		if (!(tkn_create(buf, pos, lbls, tkn)))
			return (ft_error(NULL, e_no_print, tkn));
		pos->file_col++;
		pos->buf_pos++;
		return (1);
	}
	return (2);
}
