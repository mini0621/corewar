/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 11:03:59 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/20 22:43:39 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ocp_create(t_tkn *tkn, t_pos *pos, char *bytebuf)
{
	char a;

	if (tkn->type == e_register)
		a = 0b00000001;
	if (tkn->type == e_dir_label || tkn->type == e_dir_value)
		a = 0b00000010;
	if (tkn->type == e_ind_label || tkn->type == e_ind_value)
		a = 0b00000011;
	if (tkn->type == e_register || tkn->type == e_ind_label || tkn->type == e_ind_value
		|| tkn->type == e_dir_label || tkn->type == e_dir_value) // pos->arg_nbr >= 1
	{
		if (*(bytebuf + pos->lc_inst + 1) == '\0')
			*(bytebuf + pos->lc_inst + 1) = a;
		else if (*(bytebuf + pos->lc_inst + 1) > 0 && *(bytebuf + pos->lc_inst + 1) < 4)
		{
			*(bytebuf + pos->lc_inst + 1) = *(bytebuf + pos->lc_inst + 1) << 2;
			*(bytebuf + pos->lc_inst + 1) = *(bytebuf + pos->lc_inst + 1) | a;
		}
		else if (*(bytebuf + pos->lc_inst + 1) > 3)
		{
			*(bytebuf + pos->lc_inst + 1) = *(bytebuf + pos->lc_inst + 1) << 2;
			*(bytebuf + pos->lc_inst + 1) = *(bytebuf + pos->lc_inst + 1) | a;
		}
	}
}

void	ocp_modify(t_pos *pos, char *bytebuf)
{
	if (pos->arg_nbr == 1)
		*(bytebuf + pos->lc_inst + 1) = *(bytebuf + pos->lc_inst + 1) << 6;
	else if (pos->arg_nbr == 2)
		*(bytebuf + pos->lc_inst + 1) = *(bytebuf + pos->lc_inst + 1) << 4;
	else if (pos->arg_nbr == 3)
		*(bytebuf + pos->lc_inst + 1) = *(bytebuf + pos->lc_inst + 1) << 2;
	pos->arg_nbr = 0;
}
