/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fncs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:48:19 by sunakim           #+#    #+#             */
/*   Updated: 2019/06/17 18:28:05 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	free_bytebf(t_bytebf *bytebf)
{
	free(bytebf->bytebuf);
	free(bytebf->header);
	free(bytebf->magic);
	free(bytebf->prog_size);
	free(bytebf->inst);
}
 //tkn
void	free_tkn(t_tkn *cnt)
{
	if (cnt->value)
		free(cnt->value); //void
	//op->name
}

void	del_tkn(void *cnt, size_t size)
{
	if (cnt && size)
		free_tkn((t_tkn *)cnt);
}
//lbl
void	free_lbls(t_lbl *lbl)
{
	ft_strdel(&(lbl->name));
	//if (lbl->frwd)
	//	ft_lstdel(&(lbl->frwd), &del_tkn);
}

void	del_lbls(void *content, size_t size)
{
	if (content && size)
		free_lbls((t_lbl *)content);
}
