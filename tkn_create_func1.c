/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_create_func1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:08:01 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/05 14:28:15 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
