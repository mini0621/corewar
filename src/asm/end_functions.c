/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 11:17:39 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/24 14:32:54 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	print_error_lbl(t_list *tmp_l, t_pos *pos, int *flag, int *first)
{
	t_list	*tmp_t;
	t_tkn	*tkn;

	tmp_t = ((t_lbl*)(tmp_l->content))->frwd;
	while (tmp_t)
	{
		tkn = (t_tkn*)(tmp_t->content);
		if (*first == 0)
			ft_printf("\n");
		ft_printf("\e[1m\e[037m%s:%d:%d: \e[031merror: \e[037mlabel '%s' used",
			pos->file_name, tkn->line,
			tkn->buff_start + 1, ((t_lbl*)(tmp_l->content))->name);
		ft_printf(" as '%s' at address '%#x' has never been declared\n\e[0m",
			get_tkn_type_name(((t_tkn*)(tmp_t->content))->type),
			((t_tkn*)(tmp_t->content))->lc_inst);
		tmp_t = tmp_t->next;
		*first = 0;
	}
	*flag = 0;
}

int			end_lbl(t_list *lbls, t_pos *pos)
{
	t_list	*tmp_l;
	int		flag;
	int		first;

	tmp_l = lbls;
	flag = 1;
	first = 1;
	while (tmp_l)
	{
		if (((t_lbl*)(tmp_l->content))->type == 'U')
			print_error_lbl(tmp_l, pos, &flag, &first);
		tmp_l = tmp_l->next;
	}
	return (flag);
}

static int	fill_bytebf(t_bytebf *bytebf, t_pos *pos)
{
	bytebf->hd_size = 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4;
	if (!(bytebf->header = (char *)ft_memalloc(bytebf->hd_size)))
		return (ft_error(pos, e_malloc_error, NULL));
	ft_memcpy(bytebf->header, bytebf->magic, 4);
	ft_memcpy(bytebf->header + 4, bytebf->name, PROG_NAME_LENGTH);
	ft_memcpy(bytebf->header + 4 + PROG_NAME_LENGTH, bytebf->offset1, 4);
	ft_memcpy(bytebf->prog_size, &pos->lc_tkn, 4);
	ft_memrev(bytebf->prog_size, 4);
	ft_memcpy(bytebf->header + 8 + PROG_NAME_LENGTH, bytebf->prog_size, 4);
	ft_memcpy(bytebf->header + 12 + PROG_NAME_LENGTH,
		bytebf->comment, COMMENT_LENGTH);
	ft_memcpy(bytebf->header + 12 + PROG_NAME_LENGTH + COMMENT_LENGTH,
		bytebf->offset2, 4);
	if (!(bytebf->bytebuf = (char *)ft_memalloc(bytebf->hd_size + pos->lc_tkn)))
		return (ft_error(pos, e_malloc_error, NULL));
	ft_memcpy(bytebf->bytebuf, bytebf->header, bytebf->hd_size);
	ft_memcpy(bytebf->bytebuf + bytebf->hd_size, bytebf->inst, pos->lc_tkn);
	return (1);
}

static int	ft_fill_write(t_bytebf *bytebf, t_pos *pos, int fd, char *f_name)
{
	int	i;

	if (!(fill_bytebf(bytebf, pos)))
	{
		ft_strdel(&f_name);
		return (ft_error(NULL, e_no_print, NULL));
	}
	if ((i = write(fd, bytebf->bytebuf, pos->lc_tkn + bytebf->hd_size)) == -1)
	{
		ft_strdel(&f_name);
		return (ft_error(pos, e_write_error, NULL));
	}
	else
		ft_printf("\e[1m\e[037mWrite output to %s\n\e[0m", f_name);
	return (1);
}

int			ft_write_output(t_bytebf *bytebf, t_pos *pos, char *name)
{
	int		fd;
	char	*tmp;
	char	*f_name;

	if (!(tmp = ft_strndup(name, ft_strlen(name) - 2)))
		return (ft_error(pos, e_malloc_error, NULL));
	if (!(f_name = ft_strjoin(tmp, ".cor")))
	{
		ft_strdel(&tmp);
		return (ft_error(pos, e_malloc_error, NULL));
	}
	ft_strdel(&tmp);
	if ((fd = open(f_name, O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
	{
		ft_strdel(&f_name);
		return (ft_error(pos, e_open_error, NULL));
	}
	else if (!ft_fill_write(bytebf, pos, fd, f_name))
		return (ft_error(NULL, e_no_print, NULL));
	free_bytebf_pos(bytebf, pos);
	ft_strdel(&f_name);
	return (1);
}
