/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 11:16:16 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/13 14:50:51 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_tkn	*tkn_create(char *buf, t_pos *pos, t_list **lbls, t_tkn *tkn)
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
		if (j == lex_sm[pos->state_l][1])
		{
			tkn_fptr[j](buf, pos, lbls, tkn);
			break ;
		}
		j++;
	}
	return (tkn);
}

void	bytebuf_realloc(t_bytebf *bytebf, t_pos *pos, t_tkn *tkn)
{
	if (bytebf->inst_remain < tkn->mem_size
		|| (tkn->type == e_op && ((t_op_asm*)(tkn->value))->ocp == 1 && bytebf->inst_remain < 2))
	{
		bytebf->inst_size = bytebf->inst_size + BUFF_SIZE_COR;
		bytebf->inst = realloc(bytebf->inst, bytebf->inst_size);
		bytebf->inst_remain = bytebf->inst_remain + BUFF_SIZE_COR;
	}
}

void	ft_init_main(t_list **lbls, t_bytebf *bytebf, char **line, t_pos *pos)
{
	int	magic;

	bytebf->inst = (char*)ft_memalloc(BUFF_SIZE_COR);
	bytebf->inst_remain = BUFF_SIZE_COR;
	bytebf->inst_size = bytebf->inst_remain;
	bytebf->magic = (char*)ft_memalloc(4);
	magic = COREWAR_EXEC_MAGIC;
	ft_memcpy(bytebf->magic, &magic, 4);
	ft_memrev(bytebf->magic, 4);
	ft_bzero(bytebf->offset1, 4);
	ft_bzero(bytebf->offset2, 4);
	ft_bzero(bytebf->name, PROG_NAME_LENGTH);
	ft_bzero(bytebf->comment, COMMENT_LENGTH);
	bytebf->prog_size = (char*)ft_memalloc(4);
	*line = NULL;
	*lbls = NULL;
	pos->file_line = 0;
	pos->buf_pos = 0;
	pos->lc_instruction = 0;
	pos->lc_tkn = 0;
	pos->state_s = 0;
	pos->size_buf = 0;
}

void	init_before_analysis(t_pos *pos, char **read_line)
{
	char	*tmp;

	pos->file_col = 0;
	pos->file_line++;
	tmp = pos->tmp_buf;
	pos->tmp_buf = ft_memjoin(pos->tmp_buf, *read_line, pos->size_buf, pos->size_line);
	ft_strdel(read_line);
	ft_strdel(&tmp);
	pos->size_buf = pos->size_buf + pos->size_line;
}

void	free_after_analysis(t_pos *pos, char **line)
{
	ft_strdel(&pos->tmp_buf);
	ft_strdel(line);
	pos->buf_pos = 0;
	pos->size_buf = 0;
	pos->multiple_line = 0;
}
