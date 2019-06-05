/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_create_func1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:08:01 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/05 22:20:50 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	tkn_label(char *buff, t_pos *pos, t_lbl *labels, t_tkn *token)
{
	t_lbl	*tmp_l;
	t_tkn	*tmp_t;
	char	*name;

	tmp_l = labels;
	name = ft_strndup(buff + tkn->buff_start, tkn->buff_end - tkn->buff_start);
	tkn->type = e_label;
	while (tmp_l != NULL && !ft_strequ(tmp_l->name, name))
		tmp_l = tmp_l->next;
	if (tmp_l != NULL)
	{
		if (tmp_l->type == 'D')
			ERROR
		else
		{
			tmp_t = tmp_l->params;
			tmp_l->type = 'D';
			tmp_l->lc_label = pos->lc_instruction;
			while (tmp_t != NULL)
			{
				ft_fill_gap_bytebuff(tmp_t, tmp_l); // to code + verify that the LC points to where the label we just received is pointing to
				tmp_t = tmp_t->next;
			}
		}
	}
	else
	{
		tmp_l = (t_lbl *)ft_memalloc(sizeof(t_lbl));
		tmp_l->name = name;
		tmp_l->type = 'D';
		tmp_l->lc_label = pos->lc_instruction; // not sure about the pos->lc_instruction
		tmp_l->params = NULL;
		ft_lstadd(&labels, ft_lstnew(tmp_l, sizeof(t_lbl)));
	}

//	IF LABEL EXISTS IN SYMBOL TABLE
//		IF LABEL HAS TYPE DEFINED
//			THEN : ERROR
//		ELSE
//			THEN : PARSE LINKED LIST AND CALCULATE VALUES + PUT THEM IN THE BYTECODE BUFFER
//	ELSE
//		THEN : CREATE ENTRY
}

void	tkn_register(char *buff, t_pos *pos, t_lbl *labels, t_tkn *tkn)
{
	int nbr;
	char	*nbr_str;

	nbr_str = ft_strndup(buff + tkn->buff_start, tkn->buff_end - tkn->buff_start + 1);
	if (ft_strlen(nbr_str) > 2)
		ERROR;
	nbr = ft_atoi(buff + tkn->buff_start + 1); //after 'r'
	if (nbr > 16 || nbr == 0)  // 0?
		ERROR;
	else
	{
		tkn->type = e_register;
		tkn->value = nbr;
		tkn->mem_size = 1;
	}
}

void	tkn_op(char *buff, t_pos *pos, t_lbl *labels, t_tkn *token)
{
	int		i;
	char	*name;

	name = ft_strndup(buff + tkn->buff_start, tkn->buff_end - tkn->buff_start);
	i = 0;
	while (i < OP_TAB_SIZE && !ft_strequ(name, op_tab[i][0]))
		i++;
	if (i == OP_TAB_SIZE)
		ERROR();
	tkn->type = e_op;
	(t_op)tkn->value = op_tab[i];
}

void	tkn_cmd(char *buff, t_pos *pos, t_lbl *labels, t_tkn *token)
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
	while (!isspace(buff + tkn->buff_start))
		tkn->buff_start++;
	while (isspace(buff + tkn->buff_start))
		tkn->buff_start++;
	tkn->buff_start++;
	(char*)tkn->value = ft_strndup(buff + tkn->buff_start, ft_strchr(buff + tkn->buff_start, '\"'));
	if (tkn->type == e_cmd_name
		&& ft_strlen((char*)tkn->value) > PROG_NAME_LENGTH)
		ERROR();
	else if (tkn->type == e_cmd_comment
		&& ft_strlen((char*)tkn->value) > COMMENT_LENGTH)
		ERROR();
}


void	tkn_separator(char *buff, t_pos *pos, t_lbl *labels, t_tkn *tkn)
{
	tkn->type = e_separator;
}

void	tkn_carr_ret(char *buff, t_pos *pos, t_lbl *labels, t_tkn *token)
{
	token->type = e_carriage_return;
}

void	tkn_dir_value(char *buff, t_pos *pos, t_lbl *labels, t_tkn *tkn)
{
	int			nbr;
	long int	long_nbr;
	short		sh_nbr;

	tkn->mem_size = pos->op->dir_bytes;
	//length of the numbers > max
	long_nbr = ft_atolong(buff + tkn->buff_start + 1);
	if (long_nbr > 2147483647 || long_nbr < -2147483648)
		ERROR();
	else
	{
		if (tkn->mem_size == 4)
			tkn->value = (void *)long_nbr;
		else if (tkn->mem_size == 2)
		{
			sh_nbr = ft_atos(buff + tkn->buff_start + 1);
			tkn->value = (void *)sh_nbr;
		}
	}
	tkn->type = e_dir_value;
}

void	tkn_ind_value(char *buff, t_pos *pos, t_lbl *labels, t_tkn *tkn)
{
	long int	long_nbr;

	long_nbr = ft_atolong(buff + tkn->buff_start);
	if (long_nbr > 2147483647 || long_nbr < -2147483648)
		ERROR();
	else
	{
		if (long_nbr > 32767 || long_nbr < -32767)
			tkn->value = (short)long_nbr >> 48;// 6 * 8
		else
			tkn->value = (short)long_nbr;
	}
	tkn->type = e_ind_value;
	tkn->mem_size = 2;
}

