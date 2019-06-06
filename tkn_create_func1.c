/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_create_func1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:08:01 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/06 15:26:42 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	tkn_label(char *buff, t_pos *pos, t_list *lbls, t_tkn *tkn)
{
	char	*name;
	t_list	*tmp_l;
	t_lbl	**new;

	tkn->type = e_label;
	tmp_l = lbls;
	name = ft_strndup(buff + tkn->buff_start, tkn->buff_end - tkn->buff_start);
	while (tmp_l != NULL && !ft_strequ(((t_lbl*)(tmp_l->content))->name, name))
		tmp_l = tmp_l->next;
	if (tmp_l != NULL)
	{
		if (((t_lbl*)(tmp_l->content))->type == 'D')
			ERROR
		else
		{
			(t_lbl*)tkn->value = (t_lbl*)tmp_l->content;
			((t_lbl*)(tmp_l->content))->lc_label = pos->lc_instruction;
			//((t_lbl*)(tmp_l->content))->type = 'D'; // Move this in bytecode_translation function.
			//verify that the LC points to where the label we just received is pointing to
		}
	}
	else
	{
		new = (t_lbl*)ft_memalloc(sizeof(t_lbl));
		(t_lbl*)tkn->value = new;
		new->name = name;
		new->type = 'D';
		new->lc_label = pos->lc_instruction; // Check if on good instruction (the one after the label, not before)
		new->frwd = NULL;
		ft_lst_add(&lbls, ft_lstnew(new, sizeof(t_lbl)));
	}
}

void	tkn_dir_label(char *buff, t_pos *pos, t_list *lbls, t_tkn *tkn)
{
	char	*name;
	t_list	*tmp_l;
	t_tkn	*tmp_t;
	t_lbl	*new;

	tkn->type = e_dir_label;
	tkn->mem_size = pos->op->dir_bytes;
	tmp_l = lbls;
	name = ft_strndup(buff + tkn->buff_start + 2, tkn->buff_end - tkn->buff_start - 1);
	while (tmp_l != NULL && !ft_strequ(((t_lbl*)(tmp_l->content))->name, name))
		tmp_l = tmp_l->next;
	if (tmp_l != NULL)
	{
		if (((t_lbl*)(tmp_l->content))->type == 'D')
			tkn->value = ((t_lbl*)(tmp_l->content))->lc_label - pos->lc_instruction;
		else
		{
			tkn->lc_instruction = pos->lc_instruction;
			tkn->lc_tkn = pos->lc_tkn;
			ft_lst_add(((t_lbl*)(tmp_l->content))->frwd, ft_lstnew(tkn, sizeof(t_tkn)))
		}
	}
	else
	{
		new = (t_lbl*)ft_memalloc(sizeof(t_lbl));
		new->name = name;
		new->type = 'U';
		ft_lst_add(&lbls, ft_lstnew(new, sizeof(t_lbl)));
		ft_lst_add(((t_lbl*)(tmp_l->content))->frwd, ft_lstnew(tkn, sizeof(t_tkn)))
	}
}

void	tkn_ind_label(char *buff, t_pos *pos, t_list *lbls, t_tkn *tkn)
{
	char	*name;
	t_list	*tmp_l;
	t_tkn	*tmp_t;
	t_lbl	*new;

	tkn->type = e_ind_label;
	tkn->mem_size = 2;
	tmp_l = lbls;
	name = ft_strndup(buff + tkn->buff_start + 1, tkn->buff_end - tkn->buff_start);
	while (tmp_l != NULL && !ft_strequ(((t_lbl*)(tmp_l->content))->name, name))
		tmp_l = tmp_l->next;
	if (tmp_l != NULL)
	{
		if (((t_lbl*)(tmp_l->content))->type == 'D')
			tkn->value = tmp_l->lc_label - pos->lc_instruction;
		else
		{
			tkn->lc_instruction = pos->lc_instruction;
			tkn->lc_tkn = pos->lc_tkn;
			ft_lst_add(tmp_l->tkns, ft_lstnew(tkn, sizeof(t_tkn)))
		}
	}
	else
	{
		new = (t_lbl*)ft_memalloc(sizeof(t_lbl));
		new->name = name;
		new->type = 'U';
		ft_lst_add(&lbls, ft_lstnew(new, sizeof(t_lbl)));
		ft_lst_add(((t_lbl*)(tmp_l->content))->frwd, ft_lstnew(tkn, sizeof(t_tkn)))
	}
}

void	tkn_register(char *buff, t_pos *pos, t_list *lbls, t_tkn *tkn)
{
	IF LENGTH OF NUM CHARS > 2
		THEN : ERROR
	ELSE
		THEN : CREATE tkn WITH TYPE REGISTER / VALUE = NUMERIC / LC_INST / LC_tkn / SIZE
}

void	tkn_op(char *buff, t_pos *pos, t_list *lbls, t_tkn *tkn)
{
	int		i;
	char	*name;

	tkn->type = e_op;
	name = ft_strndup(buff + tkn->buff_start, tkn->buff_end - tkn->buff_start + 1);
	i = 0;
	while (i < OP_TAB_SIZE && !ft_strequ(name, op_tab[i]->name))
		i++;
	if (i == OP_TAB_SIZE)
		ERROR();
	(t_op)tkn->value = op_tab[i];
	pos->dir_bytes = op_tab[i]->dir_bytes;
}

void	tkn_cmd(char *buff, t_pos *pos, t_list *lbls, t_tkn *tkn)
{
	if (ft_strnequ(buff + tkn->buff_start, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		tkn->type = e_cmd_name;
	else if (ft_strnequ(buff + tkn->buff_start, COMMENT_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		tkn->type = e_cmd_comment;
	else
	{
		ERROR();
		return ;
	}
	while (!ft_isspace(buff + tkn->buff_start))
		tkn->buff_start++;
	while (ft_isspace(buff + tkn->buff_start))
		tkn->buff_start++;
	tkn->buff_start++;
	(char*)tkn->value = ft_strndup(buff + tkn->buff_start,
		ft_strchr(buff + tkn->buff_start, '\"') - (buff + tkn->buff_start) + 1);
	if (tkn->type == e_cmd_name
		&& ft_strlen((char*)tkn->value) > PROG_NAME_LENGTH)
		ERROR();
	else if (tkn->type == e_cmd_comment
		&& ft_strlen((char*)tkn->value) > COMMENT_LENGTH)
		ERROR();
}


