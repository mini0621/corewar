/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_create_func1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:08:01 by allefebv          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/06/05 14:33:23 by sunakim          ###   ########.fr       */
=======
/*   Updated: 2019/06/04 18:14:18 by allefebv         ###   ########.fr       */
>>>>>>> origin/asm_alban
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	tkn_label(char *buff, t_pos *pos, t_lbl *labels, t_tkn *token)
{
	t_lbl	*tmp_l;
	t_tkn	*tmp_t;
	char	*name;

<<<<<<< HEAD
=======
	tmp_l = labels;
>>>>>>> origin/asm_alban
	name = ft_strndup(buff + tkn->buff_start, tkn->buff_end - tkn->buff_start);
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
<<<<<<< HEAD
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
=======

	}


	IF LABEL EXISTS IN SYMBOL TABLE
		IF LABEL HAS TYPE DEFINED
			THEN : ERROR
		ELSE
			THEN : PARSE LINKED LIST AND CALCULATE VALUES + PUT THEM IN THE BYTECODE BUFFER
	ELSE
		THEN : CREATE ENTRY
>>>>>>> origin/asm_alban
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

	IF LENGTH OF NUM CHARS > 2
		THEN : ERROR
	ELSE
		THEN : CREATE TOKEN WITH TYPE REGISTER / VALUE = NUMERIC / SIZE
}

void	tkn_op(char *buff, t_pos *pos, t_lbl *labels, t_tkn *token)
{
	IF LOOKUP TABLE FOR OP_CODES = TRUE
		THEN : CREATE TOKEN WITH OPTYPE / VALUE OP CODE / LC_INST / LC_TOKEN / SIZE
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
	char	*dir;
	int		nbr;

	dir = ft_strndup(buff + tkn->buff_start + 1, tkn->buff_end - tkn->buff_start + 1);
	nbr = ft_atoi(dir);  // bigger than int?
	tkn->type = e_dir_value;
	tkn->mem_size = 4;
	tkn->value = nbr;
}

void	tkn_ind_value(char *buff, t_pos *pos, t_lbl *labels, t_tkn *tkn)
{
	char	*ind;
	int		nbr;

	ind = ft_strndup(buff + tkn->buff_start, tkn->buff_end - tkn->buff_start + 1);
	nbr = ft_atoi(ind);  // bigger than int?
	tkn->type = e_ind_value;
	tkn->mem_size = 2;
	tkn->value = nbr;
}

void	tkn_dir_label(char *buff, t_pos *pos, t_lbl *labels, t_tkn *tkn)
{
	char	*dir;
	int		nbr;

	dir = ft_strndup(buff + tkn->buff_start + 1, tkn->buff_end - tkn->buff_start + 1);

}
