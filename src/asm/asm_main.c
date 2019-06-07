/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 17:35:24 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/07 15:45:39 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
 * checks on lexical analysis result
 * */

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

t_token	*tkn_create(char *buff, t_pos *pos, t_lbl *lbls, t_tkn *tkn)
{
	tkn_create_func	tab[NB_TOKEN_TYPES];

	tab[0] = tkn_label;
	tab[1] = tkn_register;
	tab[2] = tkn_op;
	tab[3] = tkn_dir_value;
	tab[4] = tkn_dir_label;
	tab[5] = tkn_ind_value;
	tab[6] = tkn_ind_label;
	tab[7] = tkn_cmd;
	tab[8] = tkn_separator;
	tab[9] = tkn_carriage_ret;

	j = 0;
	while (j < NB_TOKEN_TYPES)
	{
		if (j == lexical_sm[state_l][1])
			tab[j](buff, position, i, token);
		j++;
	}
	return (token);
}

int	lexical_analysis(char *buff, t_pos *pos, t_tkn **tkn, t_lbl *lbls)
{
	int	i;

	pos->state_l = 0;
	if (!(*tkn = (t_tkn*)ft_memalloc(sizeof(t_tkn))))
		return (0);
	*(tkn->buff_start) = pos->col; // 1
	while (pos->state_l != -1)  // except every finals and err
	{
		i = 0;
		while (i < NB_LSM_COLUMN(14) && !ft_strchr(lsm_col[i], buff[pos->col]))
			i++;
		pos->state_l = lex_sm[pos->state_l][i];
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
	LEXICAL_ERROR(buff, pos);
	return (0);
}

/*
 * syntactic analysis
 * */

void ocp_create(t_tkn *tkn, t_pos *pos)
{
	char a;

	a = (tkn->type == e_register) ? 0b00000001 : 0;
	if (tkn->type == e_dir_label || tkn->type == e_dir_value)
		a = 0b00000010;
	if (tkn->type == e_ind_label || tkn->type == e_ind_value)
		a = 0b00000011;
	if (tkn->type == e_register || tkn->type == e_ind_label || tkn->type == e_ind_value
		|| tkn->type == e_dir_label || tkn->type == e_dir_value) // pos->ocp_nbr >= 1
	{
		if (*(pos->lc_instruction + 1) == '\0')
			*(pos->lc_instruction + 1) = a;
		else if (*(pos->lc_instruction + 1) > 0 && *(pos->lc_instruction + 1) < 4)
		{
			*(pos->lc_instruction + 1) = *(pos->lc_instruction + 1) << 2;
			*(pos->lc_instruction + 1) = *(pos->lc_instruction + 1) | a;
		}
		else if (*(pos->lc_instruction + 1) > 3)
		{
			*(pos->lc_instruction + 1) = *(pos->lc_instruction + 1) << 2;
			*(pos->lc_instruction + 1) = *(pos->lc_instruction + 1) | a;
		}
	}
}

void	syntactic_analysis(t_lbl *lbls, t_pos *pos, char *byte_buff, char *line)
{
	t_tkn	*token;

	while (pos->state_s != -1) //err 아닌경우
	{
		if (!lexical_analysis(&read_buff, &token, &position, &lbls))
			return ;
		pos->state_s = syntactic_sm[pos->state_s][token->type];
		if (token)
			ocp_create(token, pos);
		if (token)
		bytecode_translation(token, byte_buff, pos, lbls); // translate the token we just read in bytecode
	}
	pos->lc_instruction = pos.lc_token + token.mem_size;
}

void	ft_init_main(t_lbl **lbls, char **byte_buff, char **line, t_pos *pos)
{
	bytebuf = (char*)ft_memalloc(BUFF_SIZE);
	*line = NULL;
	*lbls = NULL;
	pos->line = 0;
	pos->lc_instruction = 0;
	pos->lc_token = 0;
	pos->state_s = 0;
}

void ocp_modify(t_op *pos)
{
	if (pos->ocp_nbr == 1)
		*(pos->lc_instruction + 1) = *(pos->lc_instruction + 1) << 6;
	else if (pos->ocp_nbr == 2)
		*(pos->lc_instruction + 1) = *(pos->lc_instruction + 1) << 4;
	else if (pos->ocp_nbr == 3)
		*(pos->lc_instruction + 1) = *(pos->lc_instruction + 1) << 2;
	//variable nbr error? already before in syntactic
}

void	main_loop(int fd)
{
	char	*bytebuf;
	char	*line;
	t_list	*lbls;
	t_pos	pos; // line number and column number

	ft_init_main(&lbls, &bytebuf, &line, &pos);
	while ((pos->size_line = read_asm(&line, error, fd) > 0) && ERROR == 0) // line per line but should return the \n as well
	{
		pos->col = 1;
		pos->line++;
		syntactic_analysis(lbls, &pos, bytebuf, line);
		ocp_modify(&pos);
		if (line)
			free(line);
	}
	END_FUNCTION(SYMBOLS_TABLE); // checks if all label used have been created effectively. If Undefined values still il symbol table, return error
}

int	main(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		return (0);
	end = 0;
	if (fd = open(argv[1], O_RDONLY) < 0)
	{
		ERROR();
		return (0);
	}
	main_loop(fd);
	return (0);
}
