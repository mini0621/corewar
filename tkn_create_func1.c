/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_create_func1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:08:01 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/04 15:20:06 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	tkn_label(char *buff, t_pos *pos, t_lbl *labels, t_tkn *token)
{
	t_lbl	*tmp;
	char	*name;

	tmp = labels;
	name = ft_strndup(buff + tkn->buff_start, tkn->buff_end - tkn->buff_start);
	while (tmp != NULL && !ft_strequ(tmp->name != name)
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
