/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_creations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 21:35:32 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/22 21:37:55 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	tkn_create(char *buf, t_pos *pos, t_list **lbls, t_tkn **tkn)
{
	int j;

	tkn_fptr[0] = &tkn_label;
	tkn_fptr[1] = &tkn_register;
	tkn_fptr[2] = &tkn_op;
	tkn_fptr[3] = &tkn_dir_value;
	tkn_fptr[4] = &tkn_dir_label;
	tkn_fptr[5] = &tkn_ind_value;
	tkn_fptr[6] = &tkn_ind_label;
	tkn_fptr[7] = &tkn_cmd;
	tkn_fptr[8] = &tkn_separator;
	tkn_fptr[9] = &tkn_carr_ret;
	j = 0;
	while (j < NB_TKN_TYPES)
	{
		if (j == g_lex_sm[pos->state_l][1])
		{
			if (!(tkn_fptr[j](buf, pos, lbls, tkn)))
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
