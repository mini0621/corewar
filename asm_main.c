/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 17:35:24 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/05 14:41:12 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
 * checks on lexical analysis result
 * */

/*
void	COMPLETE_CHECK_TOKEN()
{
	if (TOKEN == DIR_LABEL | IND_LABEL)
	{
		if (LABEL ISNT IN LABEL_TABLE)
		{
			LABEL_TABLE[LAST].NAME = LABEL;
			LABEL_TABLE[LAST].VALUE = UNDEFINED;
			LABEL_TABLE[LAST].REFERENCES = TOKEN_START_ADDRESS (linked list)
		}
	}
	if (TOKEN == LABEL_DECLARATION)
	{
		if (LABEL IS IN LABEL_TABLE)
		{
			if (TYPE == UNDEFINED)
				calcultate value of every previous reference to this label (follow the linked list)
			else
				ERROR (label declared twice)
		}
	}
	if (TOKEN == OP_CODE)
		check_op_codes() // strequ on a table with OP_CODES names...
	if (TOKEN == REGISTER)
		check_register() // MAX_REG size (available in .h)
	if (TOKEN == COMMAND)
		check_commands(); // length of string, strequ on .command & .name
						// move pointers to the name  or comments value
	if (TOKEN == DIR_VALUE | IND_VALUE)
		check_values(); // int max
	TOKEN.ADDRESS = Location_Counter
}

*/





/*
 * translates into bytecode
 * */

void	BYTECODE_TRANSLATION // should move the location counter forward
{
	OP_CODE();
	OCP();
	REG_IND_DIR();
}

void	REG_IND_DIR()
{
	LABEL_MANAGEMENT(); // if forward label, saves room for the value (2 bytes if label is indirect, 2 or 4 if label is direct, depending on OP Code)
	// if label already declared, make computations using the table of symbols to replace the label by the good value;
	OCP
}







/*
 * LEXICAL ANALYSIS
 * */

void	ft_lexical_error(char *buff, t_position *position)
{

}

t_token	*tkn_create(char *buff, t_position *position, int i, int state_l)
{
	tkn_create_func	tab[10];
	t_token			*token;

	tab[0] = tkn_create_label;
	tab[1] = tkn_create_register;
	tab[2] = tkn_create_op;
	tab[3] = tkn_create_dir_value;
	tab[4] = tkn_create_dir_label;
	tab[5] = tkn_create_ind_value;
	tab[6] = tkn_create_ind_label;
	tab[7] = tkn_create_cmd;
	tab[8] = tkn_create_separator;
	tab[9] = tkn_create_carriage_ret;

	j = 0;
	while (j < 9)
	{
		if (j == lexical_sm[state_l][1])
			tab[j](buff, position, i, token);
		j++;
	}
	return (token);
}

int	lexical_analysis(char *buff, t_pos *pos, t_tkn *tkn, t_lbl *lbls)
{
	int	j;

	pos->state_l = 0;
	if (!(tkn = (t_tkn*)ft_memalloc(sizeof(t_tkn))))
		return (0);
	tkn->buff_start = pos->col; // 1
	while (pos->state_l != -1)  // except every finals and err
	{
		j = 0;
		while (j < NB_LSM_COLUMN(14) && !ft_strchr(lsm_col[j], buff[pos->col]))
			j++;
		pos->state_l = lex_sm[pos->state_l][j];
		if (pos->state_l == -1)
			break;
		if (lex_sm[pos->state_l][0] == -2 || lex_sm[pos->state_l][0] == -3)
		{
			if (lex_sm[pos->state_l][0] == -3)
				pos->col--;
			tkn->buff_end = pos->col;
			tkn_create(buff, pos, labels, token);  //**
			return (1);
		}
		pos->col++;
	}
	ft_lexical_error(buff, position);
	return (0);
}

/*
 * syntactic analysis
 * */

void	syntactic_analysis(t_lbl *lbls, t_pos *pos, char *byte_buff, char *line)
{
	t_tkn	*token;

	while (pos->state_s != -1) //err 아닌경우
	{
		if (!lexical_analysis(&read_buff, &token, &position, &lbls))
			return ;
		pos->state_s = syntactic_sm[pos->state_s][token->type];
		if (token)
		bytecode_translation(token, byte_buff, pos, lbls); // translate the token we just read in bytecode
	}
	pos->lc_instruction = pos.lc_token + token.mem_size;
}

void	ft_init_main(t_lbl **lbls, char **byte_buff, char **line, t_pos *pos)
{
	*lbls = (t_lbl*)malloc(sizeof(t_lbl));
	*lbls->next = NULL;
	*byte_buff = ft_strnew(BUFF_SIZE);
	*line = NULL;
	pos->line = 1;
	pos->lc_instruction = 0;
	pos->lc_token = 0;
	pos->state_s = 0;
}

void	main_loop(void)
{
	t_lbl	*lbls;
	t_pos	pos; // line number and column number
	char	*byte_buff;
	char	*line;

	ft_init_main(&lbls, &byte_buff, &line, &pos);
	while ((MODIFIED_GNL(0, &read_buffer) == 1) && ERROR == 0) // line per line but should return the \n as well
	{
		syntactic_analysis(lbls, &pos, byte_buff, line);
		pos->col = 1;
		pos->line++;
	}
	END_FUNCTION(SYMBOLS_TABLE); // checks if all label used have been created effectively. If Undefined values still il symbol table, return error
}

int	main(void)
{
	main_loop();
	return (0);
}
