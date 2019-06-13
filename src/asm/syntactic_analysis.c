/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntactic_analysis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 22:32:35 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/13 17:21:18 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	check_state_s(t_pos *pos, t_tkn *tkn)
{
	if (syntactic_sm[pos->state_s][0] == -2)
		pos->state_s = syntactic_sm[pos->state_s][1];
	if (syntactic_sm[pos->state_s][0] == -3)
		pos->state_s = tkn->op->op_state_s;
}

static void	ft_encode(t_pos *pos, t_tkn *tkn, t_list **lbls, t_bytebf *bytebf)
{
	bytebuf_realloc(bytebf, pos, tkn);
	bytecode_gen(tkn, bytebf, pos, *lbls);
	if (tkn && pos->ocp && tkn->mem_size != 0)
		ocp_create(tkn, pos, bytebf->inst);
	pos->lc_tkn = pos->lc_tkn + tkn->mem_size;
}

int		syntactic_analysis(t_list **lbls, t_pos *pos, t_bytebf *bytebf, t_tkn **tkn)
{
	while (pos->state_s != -1 && pos->buf_pos < pos->size_buf)
	{
		if (!lexical_analysis(pos, tkn, lbls))
			return (0);
		if (pos->multiple_line)
			return (1);
		pos->state_s = syntactic_sm[pos->state_s][(*tkn)->type];
		if (pos->state_s == -1)
			return (0);
		if (syntactic_sm[pos->state_s][0] < -1)
			check_state_s(pos, *tkn);
		if ((*tkn)->type == e_lbl || (*tkn)->type == e_op)
			pos->lc_instruction = pos->lc_tkn;
		ft_encode(pos, *tkn, lbls, bytebf);
		if (((*tkn)->type == e_ind_label || (*tkn)->type == e_dir_label)
			&& (*tkn)->value == NULL)
			continue ;
		free(*tkn);
	}
	return (1);
}
