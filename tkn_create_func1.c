/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_create_func1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:08:01 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/04 18:14:18 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	tkn_label(char *buff, t_pos *pos, t_lbl *labels, t_tkn *token)
{
	t_lbl	*tmp_l;
	t_tkn	*tmp_t;
	char	*name;

	tmp_l = labels;
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

	}


	IF LABEL EXISTS IN SYMBOL TABLE
		IF LABEL HAS TYPE DEFINED
			THEN : ERROR
		ELSE
			THEN : PARSE LINKED LIST AND CALCULATE VALUES + PUT THEM IN THE BYTECODE BUFFER
	ELSE
		THEN : CREATE ENTRY
}

void	tkn_register(char *buff, t_pos *pos, t_lbl *labels, t_tkn *token)
{
	IF LENGTH OF NUM CHARS > 2
		THEN : ERROR
	ELSE
		THEN : CREATE TOKEN WITH TYPE REGISTER / VALUE = NUMERIC / LC_INST / LC_TOKEN / SIZE
}

void	tkn_op(char *buff, t_pos *pos, t_lbl *labels, t_tkn *token)
{
	IF LOOKUP TABLE FOR OP_CODES = TRUE
		THEN : CREATE TOKEN WITH OPTYPE / VALUE OP CODE / LC_INST / LC_TOKEN / SIZE
}
