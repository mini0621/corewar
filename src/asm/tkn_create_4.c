/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_create_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 14:07:57 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/24 14:25:21 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	lbl_exists(t_list *tmp_l, t_pos *pos, t_tkn **tkn, char **name)
{
	ft_strdel(name);
	if (((t_lbl*)(tmp_l->content))->type == 'D')
		return (ft_error(pos, e_double_label, tkn));
	else
	{
		(*tkn)->value = tmp_l->content;
		((t_lbl*)(tmp_l->content))->lc_lbl_inst = pos->lc_tkn;
	}
	return (1);
}

static int	lbl_dont_exist(t_list **lbls, t_pos *pos, t_tkn **tkn, char **name)
{
	t_lbl	*new;

	if (!(new = (t_lbl*)ft_memalloc(sizeof(t_lbl))))
	{
		ft_strdel(name);
		return (ft_error(pos, e_malloc_error, tkn));
	}
	(*tkn)->value = NULL;
	new->name = *name;
	new->type = 'D';
	new->lc_lbl_inst = pos->lc_tkn;
	new->frwd = NULL;
	if (!(ft_lstpushback(lbls, ft_lstnew(new, sizeof(t_lbl)))))
	{
		free(new);
		ft_strdel(name);
		return (ft_error(pos, e_malloc_error, tkn));
	}
	free(new);
	return (1);
}

int			tkn_label(char *buff, t_pos *pos, t_list **lbls, t_tkn **tkn)
{
	char	*name;
	t_list	*tmp_l;

	(void)buff;
	name = NULL;
	(*tkn)->type = e_lbl;
	tmp_l = *lbls;
	if (!(name = ft_strndup(buff + (*tkn)->buff_start,
		(*tkn)->buff_end - (*tkn)->buff_start)))
		return (ft_error(pos, e_malloc_error, tkn));
	while (tmp_l != NULL && !ft_strequ(((t_lbl*)(tmp_l->content))->name, name))
		tmp_l = tmp_l->next;
	if (tmp_l != NULL)
	{
		if (!(lbl_exists(tmp_l, pos, tkn, &name)))
			return (ft_error(NULL, e_no_print, NULL));
	}
	else if (!lbl_dont_exist(lbls, pos, tkn, &name))
		return (ft_error(NULL, e_no_print, NULL));
	return (1);
}
