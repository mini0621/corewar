/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_create_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 10:32:41 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/23 14:22:36 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	tkn_fields_update(t_pos *pos, t_tkn *tkn)
{
	tkn->lc_inst = pos->lc_inst;
	tkn->lc_tkn = pos->lc_tkn;
	tkn->line = pos->file_line;
}

static int	label_exists(t_list *tmp_l, t_pos *pos, t_tkn **tkn)
{
	if (((t_lbl*)(tmp_l->content))->type == 'D')
	{
		if (pos->dir_bytes == 2)
		{
			if (!((*tkn)->value = (short*)malloc(sizeof(short))))
				return (ft_error(NULL, e_malloc_error, NULL));
			*((short*)(*tkn)->value) = ((t_lbl*)(tmp_l->content))->lc_lbl_inst
				- pos->lc_inst;
		}
		else
		{
			if (!((*tkn)->value = (int*)malloc(sizeof(int))))
				return (ft_error(NULL, e_malloc_error, NULL));
			*((int*)(*tkn)->value) = ((t_lbl*)(tmp_l->content))->lc_lbl_inst
				- pos->lc_inst;
		}
	}
	else
	{
		tkn_fields_update(pos, *tkn);
		if (!(ft_lstadd(&((t_lbl*)(tmp_l->content))->frwd,
			ft_lstnew(*tkn, sizeof(t_tkn)))))
			return (ft_error(NULL, e_malloc_error, NULL));
	}
	return (1);
}

static int	label_dont_exist(t_list **lbls, t_pos *pos, t_tkn **tkn, char *name)
{
	t_lbl	*new;

	tkn_fields_update(pos, *tkn);
	if (!(new = (t_lbl*)ft_memalloc(sizeof(t_lbl))))
		return (ft_error(NULL, e_malloc_error, NULL));
	new->name = name;
	new->type = 'U';
	if (!(ft_lstadd(lbls, ft_lstnew(new, sizeof(t_lbl)))))
		return (ft_error(NULL, e_malloc_error, NULL));
	free(new);
	if (!(ft_lstadd(&((t_lbl*)((*lbls)->content))->frwd,
		ft_lstnew(*tkn, sizeof(t_tkn)))))
		return (ft_error(NULL, e_malloc_error, NULL));
	return (1);
}

int			tkn_dir_label(char *buff, t_pos *pos, t_list **lbls, t_tkn **tkn)
{
	char	*name;
	t_list	*tmp_l;

	name = NULL;
	(*tkn)->type = e_dir_label;
	(*tkn)->mem_size = pos->dir_bytes;
	tmp_l = *lbls;
	if (!(name = ft_strndup(buff + (*tkn)->buff_start + 2,
		(*tkn)->buff_end - (*tkn)->buff_start - 1)))
		return (ft_error(NULL, e_malloc_error, NULL));
	while (tmp_l != NULL && !ft_strequ(((t_lbl*)(tmp_l->content))->name, name))
		tmp_l = tmp_l->next;
	if (tmp_l != NULL)
	{
		ft_strdel(&name);
		if (!label_exists(tmp_l, pos, tkn))
			return (ft_error(NULL, e_no_print, NULL));
	}
	else if (!label_dont_exist(lbls, pos, tkn, name))
		return (ft_error(NULL, e_no_print, NULL));
	return (1);
}

int			tkn_ind_label(char *buff, t_pos *pos, t_list **lbls, t_tkn **tkn)
{
	char	*name;
	t_list	*tmp_l;

	name = NULL;
	(*tkn)->type = e_ind_label;
	(*tkn)->mem_size = 2;
	tmp_l = *lbls;
	if (!(name = ft_strndup(buff + (*tkn)->buff_start + 1,
		(*tkn)->buff_end - (*tkn)->buff_start)))
		return (ft_error(NULL, e_malloc_error, NULL));
	while (tmp_l != NULL && !ft_strequ(((t_lbl*)(tmp_l->content))->name, name))
		tmp_l = tmp_l->next;
	if (tmp_l != NULL)
	{
		ft_strdel(&name);
		if (!label_exists(tmp_l, pos, tkn))
			return (ft_error(NULL, e_no_print, NULL));
	}
	else if (!label_dont_exist(lbls, pos, tkn, name))
		return (ft_error(NULL, e_no_print, NULL));
	return (1);
}
