/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_create_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 10:32:41 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/13 11:18:57 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	tkn_label(char *buff, t_pos *pos, t_list **lbls, t_tkn *tkn)
{
	char	*name;
	t_list	*tmp_l;
	t_lbl	*new;

	tkn->type = e_lbl;
	tmp_l = *lbls;
	name = ft_strndup(buff + tkn->buff_start, tkn->buff_end - tkn->buff_start);
	while (tmp_l != NULL && !ft_strequ(((t_lbl*)(tmp_l->content))->name, name))
		tmp_l = tmp_l->next;
	if (tmp_l != NULL)
	{
		if (((t_lbl*)(tmp_l->content))->type == 'D')
			ft_printf("double label declaration\n"); // handle more properly
		else
		{
			tkn->value = tmp_l->content;
			((t_lbl*)(tmp_l->content))->lc_lbl_inst = pos->lc_instruction;
		}
	}
	else
	{
		new = (t_lbl*)ft_memalloc(sizeof(t_lbl));
		tkn->value = new;
		new->name = name;
		new->type = 'D';
		new->lc_lbl_inst = pos->lc_instruction; // Check if on good instruction (the one after the label, not before)
		new->frwd = NULL;
		ft_lstadd(lbls, ft_lstnew(new, sizeof(t_lbl)));
	}
	return (1);
}

int	tkn_dir_label(char *buff, t_pos *pos, t_list **lbls, t_tkn *tkn)
{
	char	*name;
	t_list	*tmp_l;
	t_list	*tmp_t;
	t_lbl	*new;

	tkn->type = e_dir_label;
	tkn->mem_size = pos->dir_bytes;
	tmp_l = *lbls;
	name = ft_strndup(buff + tkn->buff_start + 2, tkn->buff_end - tkn->buff_start - 1);
	while (tmp_l != NULL && !ft_strequ(((t_lbl*)(tmp_l->content))->name, name))
		tmp_l = tmp_l->next;
	if (tmp_l != NULL)
	{
		if (((t_lbl*)(tmp_l->content))->type == 'D')
		{
			if (pos->dir_bytes == 2)
			{
				tkn->value = (short*)malloc(sizeof(short));
				*((short*)tkn->value) = ((t_lbl*)(tmp_l->content))->lc_lbl_inst - pos->lc_instruction;
			}
			else
			{
				tkn->value = (int*)malloc(sizeof(int));
				*((int*)tkn->value) = ((t_lbl*)(tmp_l->content))->lc_lbl_inst - pos->lc_instruction;
			}
		}
		else
		{
			tkn->lc_instruction = pos->lc_instruction;
			tkn->lc_tkn = pos->lc_tkn;
			ft_lstadd(&((t_lbl*)(tmp_l->content))->frwd, ft_lstnew(tkn, sizeof(t_tkn)));
		}
	}
	else
	{
		new = (t_lbl*)ft_memalloc(sizeof(t_lbl));
		new->name = name;
		new->type = 'U';
		tmp_l = ft_lstnew(new, sizeof(t_lbl));
		tmp_t = ft_lstnew(tkn, sizeof(t_tkn));
		ft_lstadd(lbls, tmp_l);
		ft_lstadd(&((t_lbl*)(tmp_l->content))->frwd, tmp_t);
	}
	return (1);
}

int	tkn_ind_label(char *buff, t_pos *pos, t_list **lbls, t_tkn *tkn)
{
	char	*name;
	t_list	*tmp_l;
	t_lbl	*new;

	tkn->type = e_ind_label;
	tkn->mem_size = 2;
	tmp_l = *lbls;
	name = ft_strndup(buff + tkn->buff_start + 1, tkn->buff_end - tkn->buff_start);
	while (tmp_l != NULL && !ft_strequ(((t_lbl*)(tmp_l->content))->name, name))
		tmp_l = tmp_l->next;
	if (tmp_l != NULL)
	{
		if (((t_lbl*)(tmp_l->content))->type == 'D')
		{
			if (pos->dir_bytes == 2)
			{
				tkn->value = (short*)malloc(sizeof(short));
				*((short*)tkn->value) = ((t_lbl*)(tmp_l->content))->lc_lbl_inst - pos->lc_instruction;
			}
			else
			{
				tkn->value = (int*)malloc(sizeof(int));
				*((int*)tkn->value) = ((t_lbl*)(tmp_l->content))->lc_lbl_inst - pos->lc_instruction;
			}
		}
		else
		{
			tkn->lc_instruction = pos->lc_instruction;
			tkn->lc_tkn = pos->lc_tkn;
			ft_lstadd(&((t_lbl*)(tmp_l->content))->frwd, ft_lstnew(tkn, sizeof(t_tkn)));
		}
	}
	else
	{
		new = (t_lbl*)ft_memalloc(sizeof(t_lbl));
		new->name = name;
		new->type = 'U';
		tmp_l = ft_lstnew(new, sizeof(t_lbl));
		ft_lstadd(lbls, tmp_l);
		ft_lstadd(&((t_lbl*)(tmp_l->content))->frwd, ft_lstnew(tkn, sizeof(t_tkn)));
	}
	return (1);
}
