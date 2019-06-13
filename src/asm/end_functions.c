/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 11:17:39 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/13 15:14:15 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <fcntl.h>

int		end_lbl(t_list *lbls)
{
	t_list 	*tmp_l;
	t_list	*tmp_t;
	int		flag;

	tmp_l = lbls;
	flag = 1;
	while (tmp_l)
	{
		if (((t_lbl*)(tmp_l->content))->type == 'U')
		{
			ft_printf("ERROR -\nLabel \" %s \" has never been declared\n", ((t_lbl*)(tmp_l->content))->name);
			tmp_t = ((t_lbl*)(tmp_l->content))->frwd;
			while (tmp_t)
			{
				ft_printf("Used as an argument in instruction address %d\n", ((t_tkn*)(tmp_t->content))->lc_instruction);
				tmp_t = tmp_t->next;
			}
			flag = 0;
		}
		tmp_l = tmp_l->next;
	}
	return (flag);
}

void	fill_bytebf(t_bytebf *bytebf, t_pos *pos)
{
	bytebf->hd_size = 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4;
	bytebf->header = (char *)ft_memalloc(bytebf->hd_size);  //malloc protection!
	ft_memcpy(bytebf->header, bytebf->magic, 4);
	ft_memcpy(bytebf->header + 4, bytebf->name, PROG_NAME_LENGTH);
	ft_memcpy(bytebf->header + 4 + PROG_NAME_LENGTH, bytebf->offset1, 4);
    ft_memcpy(bytebf->prog_size, &pos->lc_tkn, 4);
	ft_memrev(bytebf->prog_size, 4);
	ft_memcpy(bytebf->header + 8 + PROG_NAME_LENGTH, bytebf->prog_size, 4); // change program size
	ft_memcpy(bytebf->header +  12 + PROG_NAME_LENGTH, bytebf->comment, COMMENT_LENGTH);
	ft_memcpy(bytebf->header + 12 + PROG_NAME_LENGTH + COMMENT_LENGTH, bytebf->offset2, 4);

	bytebf->bytebuf = (char *)ft_memalloc(bytebf->hd_size + pos->lc_tkn);
	ft_memcpy(bytebf->bytebuf, bytebf->header, bytebf->hd_size);
	ft_memcpy(bytebf->bytebuf + bytebf->hd_size, bytebf->inst, pos->lc_tkn);
}

void    ft_write_output(t_bytebf *bytebf, t_pos *pos, char *name)
{
    int		fd;
    char	*tmp;
    char	*f_name;
    int		errno;
    int		i;

    errno = 0;
    tmp = ft_strndup(name, ft_strlen(name) - 2);
    f_name = ft_strjoin(tmp, ".cor");
    ft_strdel(&tmp);
    if ((fd = open(f_name, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1) //0644 = chmod
        ft_printf("\n ASM failed with error [%s]\n", strerror(errno));
    else
    {
        fill_bytebf(bytebf, pos);
        if ((i = write(fd, bytebf->bytebuf, pos->lc_tkn + bytebf->hd_size)) == -1)
            ft_printf("\n ASM failed with error [%s]\n", strerror(errno));
        else
            ft_printf("Write output to %s\n", f_name);
    }
}
