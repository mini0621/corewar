/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_create_func1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:08:01 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/08 17:20:33 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	tkn_label(char *buff, t_pos *pos, t_list *lbls, t_tkn *tkn)
{
	char	*name;
	t_list	*tmp_l;
	t_lbl	*new;

	tkn->type = e_label;
	tmp_l = lbls;
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
			((t_lbl*)(tmp_l->content))->lc_label = pos->lc_instruction;
			//((t_lbl*)(tmp_l->content))->type = 'D'; // Move this in bytecode_translation function.
			//verify that the LC points to where the label we just received is pointing to
		}
	}
	else
	{
		new = (t_lbl*)ft_memalloc(sizeof(t_lbl));
		tkn->value = new;
		new->name = name;
		new->type = 'D';
		new->lc_label = pos->lc_instruction; // Check if on good instruction (the one after the label, not before)
		new->frwd = NULL;
		ft_lstadd(&lbls, ft_lstnew(new, sizeof(t_lbl)));
	}
}

void	tkn_dir_label(char *buff, t_pos *pos, t_list *lbls, t_tkn *tkn)
{
	char	*name;
	t_list	*tmp_l;
	t_tkn	*tmp_t;
	t_lbl	*new;

	tkn->type = e_dir_label;
	tkn->mem_size = pos->dir_bytes;
	tmp_l = lbls;
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
				*((short*)tkn->value) = ((t_lbl*)(tmp_l->content))->lc_label - pos->lc_instruction;
			}
			else
			{
				tkn->value = (int*)malloc(sizeof(int));
				*((int*)tkn->value) = ((t_lbl*)(tmp_l->content))->lc_label - pos->lc_instruction;
			}
		}
		else
		{
			tkn->lc_instruction = pos->lc_instruction;
			tkn->lc_tkn = pos->lc_tkn;
			ft_lstadd(((t_lbl*)(tmp_l->content))->frwd, ft_lstnew(tkn, sizeof(t_tkn)));
		}
	}
	else
	{
		new = (t_lbl*)ft_memalloc(sizeof(t_lbl));
		new->name = name;
		new->type = 'U';
		ft_lstadd(&lbls, ft_lstnew(new, sizeof(t_lbl)));
		ft_lstadd(((t_lbl*)(tmp_l->content))->frwd, ft_lstnew(tkn, sizeof(t_tkn)));
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
		{
			if (pos->dir_bytes == 2)
			{
				tkn->value = (short*)malloc(sizeof(short));
				*((short*)tkn->value) = ((t_lbl*)(tmp_l->content))->lc_label - pos->lc_instruction;
			}
			else
			{
				tkn->value = (int*)malloc(sizeof(int));
				*((int*)tkn->value) = ((t_lbl*)(tmp_l->content))->lc_label - pos->lc_instruction;
			}
		}
		else
		{
			tkn->lc_instruction = pos->lc_instruction;
			tkn->lc_tkn = pos->lc_tkn;
			ft_lstadd(((t_lbl*)(tmp_l->content))->frwd, ft_lstnew(tkn, sizeof(t_tkn)));
		}
	}
	else
	{
		new = (t_lbl*)ft_memalloc(sizeof(t_lbl));
		new->name = name;
		new->type = 'U';
		ft_lstadd(&lbls, ft_lstnew(new, sizeof(t_lbl)));
		ft_lstadd(((t_lbl*)(tmp_l->content))->frwd, ft_lstnew(tkn, sizeof(t_tkn)));
	}
}

void	tkn_register(char *buff, t_pos *pos, t_list *lbls, t_tkn *tkn)
{
	int		i;
	char 	nbr_char;
	char	*nbr_str;

	i = tkn->buff_start + 1;
	while (buff[i] == '0')
		i++;
	if (i == tkn->buff_end)
		ft_printf("registers cannot have value 0\n"); // handle more properly // 0 ?
	nbr_str = ft_strndup(buff + i, tkn->buff_end - i + 1);
	if (ft_strlen(nbr_str) > 2)
		ft_printf("registers cannot have value greater than %d\n", REG_NUMBER);
	nbr_char = ft_atochar(nbr_str); //create "ft_atochar"
	if (nbr_char > 16)  // 0?
		ft_printf("registers cannot have value greater than %d\n", REG_NUMBER);
	else
	{
		tkn->type = e_register;
		*((char*)tkn->value) = nbr_char;
		tkn->mem_size = 1;
	}
}

void	tkn_op(char *buff, t_pos *pos, t_list *lbls, t_tkn *tkn)
{
	int		i;
	char	*name;

	tkn->type = e_op;
	name = ft_strndup(buff + tkn->buff_start, tkn->buff_end - tkn->buff_start + 1);
	i = 0;
	while (i < OP_TAB_ASM_SIZE && !ft_strequ(name, g_op_tab_asm[i].name))
		i++;
	if (i == OP_TAB_ASM_SIZE)
		ft_printf("invalide op_code\n"); // handle more properly
	tkn->value = g_op_tab_asm + i;
	pos->ocp_nbr = g_op_tab_asm[i].n_args;
	pos->dir_bytes = g_op_tab_asm[i].dir_bytes; // changed the name of op_tab_asm
}

void	tkn_cmd(char *buff, t_pos *pos, t_list *lbls, t_tkn *tkn)
{
	if (ft_strnequ(buff + tkn->buff_start, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		tkn->type = e_cmd_name;
	else if (ft_strnequ(buff + tkn->buff_start, COMMENT_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		tkn->type = e_cmd_comment;
	else
	{
		error(pos, 1, tkn);  //fix
		return ;
	}
	while (!ft_isspace(tkn->buff_start))
		tkn->buff_start++;
	while (ft_isspace(*(buff + tkn->buff_start)))
		tkn->buff_start++;
	tkn->buff_start++;
	tkn->value = ft_strndup(buff + tkn->buff_start,
		ft_strchr(buff + tkn->buff_start, '\"') - (buff + tkn->buff_start) + 1); //WONT COPY THE \0 CHARS ...
	if (tkn->type == e_cmd_name
		&& ft_strlen((char*)tkn->value) > PROG_NAME_LENGTH) //WONT GO TO THE END OF COMMENT IF \0
		error(pos, 1, tkn);  //fix
	else if (tkn->type == e_cmd_comment
		&& ft_strlen((char*)tkn->value) > COMMENT_LENGTH) //WONT GO TO THE END OF COMMENT IF \0
		error(pos, 1, tkn);  //fix
}

void	tkn_separator(char *buff, t_pos *pos, t_list *labels, t_tkn *tkn)
{
	tkn->type = e_separator;
}

void	tkn_carr_ret(char *buff, t_pos *pos, t_list *labels, t_tkn *token)
{
	token->type = e_carriage_return;
}

void	tkn_dir_value(char *buff, t_pos *pos, t_list *labels, t_tkn *tkn)
{
	long int	long_nbr;
	int			nbr;
	short		sh_nbr;

	tkn->mem_size = pos->dir_bytes;
	if (tkn->buff_start - tkn->buff_end + 1 > 10)
		error(pos, 1, tkn);  //fix
	long_nbr = ft_atolong(buff + tkn->buff_start + 1);
	if (tkn->mem_size == 4)
	{
		if (long_nbr > 2147483647 || long_nbr < -2147483648)
			error(pos, 1, tkn);  //fix
		else
		{
			nbr = ft_atoi(buff + tkn->buff_start + 1);
			tkn->value = (void*)(&nbr);
		}
	}
	else if (tkn->mem_size == 2)
	{
		if (long_nbr > 32767 || long_nbr < -32767)
			error(pos, 1, tkn);  //fix
		else
		{
			sh_nbr = ft_atos(buff + tkn->buff_start + 1);
			tkn->value = (void*)(&sh_nbr);
		}
	}
	tkn->type = e_dir_value;
}

void	tkn_ind_value(char *buff, t_pos *pos, t_list *labels, t_tkn *tkn)
{
	long int	long_nbr;
	short		sh_nbr;

	if (tkn->buff_start - tkn->buff_end + 1 > 10)
		error(pos, 1, tkn);  //fix
	long_nbr = ft_atolong(buff + tkn->buff_start);
	if (long_nbr > 32767 || long_nbr < -32767)
		error(pos, 1, tkn);  //fix
	else
	{
		sh_nbr = ft_atos(buff + tkn->buff_start + 1);
		tkn->value = (void*)&sh_nbr;
	}
	tkn->type = e_ind_value;
	tkn->mem_size = 2;
}
