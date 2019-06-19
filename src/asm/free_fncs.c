/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fncs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:48:19 by sunakim           #+#    #+#             */
/*   Updated: 2019/06/19 21:21:49 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	free_bytebf_pos(t_bytebf *bytebf, t_pos *pos)
{
	free(bytebf->bytebuf);
	free(bytebf->header);
	free(bytebf->magic);
	free(bytebf->prog_size);
	free(bytebf->inst);
	free(pos->file_name);
}
 //tkn
void	del_tkn(void *content, size_t size)
{
	t_tkn *tmp;

	(void)size;
	tmp = (t_tkn*)content;
	free(tmp->value);
	free(tmp);
}
//lbl
void	del_lbls(void *content, size_t size)
{
	t_lbl *tmp;

	(void)size;
	tmp = (t_lbl *)content;
	ft_strdel(&(tmp->name));
	ft_lstdel(&(tmp->frwd), &del_tkn);
	free(tmp);
}

void	free_tkn(t_tkn **tkn)
{
	if (tkn && *tkn != NULL)
	{
		if ((*tkn)->value)
		{
			free((*tkn)->value);
			(*tkn)->value = NULL;
		}
		ft_memdel((void**)tkn);
		*tkn = NULL;
	}
}
