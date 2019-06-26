/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 11:16:16 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/25 14:42:10 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			bytebuf_realloc(t_bytebf *bytebf, t_pos *pos, t_tkn **tkn)
{
	char *tmp;

	if (bytebf->inst_remain < (*tkn)->mem_size || ((*tkn)->type == e_op
		&& (*tkn)->op->ocp == 1 && bytebf->inst_remain < 2))
	{
		tmp = bytebf->inst;
		if (!(bytebf->inst = realloc(bytebf->inst,
			bytebf->inst_size + BUFF_SIZE_COR)))
		{
			ft_strdel(&tmp);
			return (ft_error(pos, e_malloc_error, tkn));
		}
		ft_bzero(bytebf->inst + bytebf->inst_size, BUFF_SIZE_COR);
		bytebf->inst_size = bytebf->inst_size + BUFF_SIZE_COR;
		bytebf->inst_remain = bytebf->inst_remain + BUFF_SIZE_COR;
	}
	return (1);
}

int			ft_init_main(t_list **lbls, t_bytebf *bytebf, char **line,
				t_pos *pos)
{
	int	magic;

	*line = NULL;
	*lbls = NULL;
	ft_bzero(bytebf, sizeof(t_bytebf));
	bytebf->header = NULL;
	bytebf->prog_size = NULL;
	bytebf->magic = NULL;
	if (!(bytebf->inst = (char*)ft_memalloc(BUFF_SIZE_COR)))
		return (ft_error(pos, e_malloc_error, NULL));
	ft_bzero(bytebf->inst, BUFF_SIZE_COR);
	bytebf->inst_remain = BUFF_SIZE_COR;
	bytebf->inst_size = bytebf->inst_remain;
	if (!(bytebf->magic = (char*)ft_memalloc(4)))
		return (ft_error(pos, e_malloc_error, NULL));
	magic = COREWAR_EXEC_MAGIC;
	ft_memcpy(bytebf->magic, &magic, 4);
	ft_memrev(bytebf->magic, 4);
	ft_bzero(bytebf->offset1, 4);
	ft_bzero(bytebf->offset2, 4);
	ft_bzero(bytebf->name, PROG_NAME_LENGTH);
	ft_bzero(bytebf->comment, COMMENT_LENGTH);
	if (!(bytebf->prog_size = (char*)ft_memalloc(4)))
		return (ft_error(pos, e_malloc_error, NULL));
	return (1);
}

static int	check_buff_end(t_pos *pos)
{
	char	*tmp;

	tmp = pos->tmp_buf;
	if (pos->tmp_buf[pos->size_buf - 1] != '\n')
	{
		if (!(pos->tmp_buf = ft_memjoin(pos->tmp_buf, "\n\0",
								pos->size_buf, 2)))
		{
			ft_memdel((void**)&tmp);
			return (ft_error(pos, e_malloc_error, NULL));
		}
		pos->size_buf++;
	}
	else if (!(pos->tmp_buf = ft_memjoin(pos->tmp_buf, "\0", pos->size_buf, 1)))
	{
		ft_memdel((void**)&tmp);
		return (ft_error(pos, e_malloc_error, NULL));
	}
	return (1);
}

int			init_before_analysis(t_pos *pos, char **read_line)
{
	char	*tmp;
	char	c;

	tmp = NULL;
	c = '\0';
	pos->file_line++;
	tmp = pos->tmp_buf;
	if (!(pos->tmp_buf = ft_memjoin(pos->tmp_buf, *read_line,
		pos->size_buf, pos->size_line)))
	{
		free(tmp);
		return (ft_error(pos, e_malloc_error, NULL));
	}
	free(tmp);
	tmp = pos->tmp_buf;
	pos->size_buf = pos->size_buf + pos->size_line;
	if (!(check_buff_end(pos)))
		return (ft_error(NULL, e_no_print, NULL));
	free(tmp);
	ft_strdel(read_line);
	return (1);
}

void		free_after_analysis(t_pos *pos, char **line)
{
	ft_strdel(&pos->tmp_buf);
	ft_strdel(line);
	pos->buf_pos = 0;
	pos->file_col = 0;
	pos->tab_counter = 0;
	pos->size_buf = 0;
}
