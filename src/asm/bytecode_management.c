/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytecode_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 11:12:36 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/19 17:14:49 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	command_buf_fill(t_bytebf *bytebf, t_tkn *tkn, t_pos *pos)
{
	int	i;

	i = 0;
	if (tkn->type == e_cmd_comment)
	{
		while (i < pos->comment_len)
		{
			if (*(char*)(tkn->value + i) != '\0')
				bytebf->comment[i] = *(char*)(tkn->value + i);
			i++;
		}
		free(tkn->value);
	}
	else
	{
		while (i < pos->name_len)
		{
			bytebf->name[i] = *(char*)(tkn->value + i);
			i++;
		}
		free(tkn->value);
	}
}

void	gaps_fill(char *bytebuf, t_tkn *tkn)
{
	t_list	*t1;
	t_lbl	*lbl;
	int		ref_int;
	short	ref_sht;

	lbl = (t_lbl*)tkn->value;
	t1 = (t_list*)lbl->frwd;
	while (t1 != NULL)
	{
		tkn = (t_tkn*)t1->content;
		if (tkn->mem_size == 2)
		{
			ref_sht = lbl->lc_lbl_inst - tkn->lc_instruction;
			ft_memcpy(bytebuf + tkn->lc_tkn, &ref_sht, tkn->mem_size);
			ft_memrev(bytebuf + tkn->lc_tkn, tkn->mem_size);
		}
		else
		{
			ref_int = lbl->lc_lbl_inst - tkn->lc_instruction;
			ft_memcpy(bytebuf + tkn->lc_tkn, &ref_int, tkn->mem_size);
			ft_memrev(bytebuf + tkn->lc_tkn, tkn->mem_size);
		}
		t1 = t1->next;
	}
}

void	bytecode_gen(t_tkn *tkn, t_bytebf *bytebf, t_pos *pos)
{
	if (tkn->type == e_lbl && tkn->value && ((t_lbl*)(tkn->value))->type == 'U')
	{
		gaps_fill(bytebf->inst, tkn);
		((t_lbl*)(tkn->value))->type = 'D';
	}
	else if (tkn->type == e_cmd_comment || tkn->type == e_cmd_name)
		command_buf_fill(bytebf, tkn, pos);
	else if (tkn->mem_size != 0 && tkn->value != NULL)
	{
		if (tkn->mem_size == 1)
		{
			ft_memcpy(bytebf->inst + pos->lc_tkn, tkn->value, 1);
			free(tkn->value);
			if (tkn->type == e_op && tkn->op->ocp == 1)
			{
				pos->lc_tkn = pos->lc_tkn + 1;
				bytebf->inst_remain = bytebf->inst_remain - 1;
			}
		}
		else if (tkn->mem_size == 2 || tkn->mem_size == 4)
		{
			ft_memcpy(bytebf->inst + pos->lc_tkn, tkn->value, tkn->mem_size);
			ft_memrev(bytebf->inst + pos->lc_tkn, tkn->mem_size);
			free(tkn->value);
		}
	}
	bytebf->inst_remain = bytebf->inst_remain - tkn->mem_size;
}
