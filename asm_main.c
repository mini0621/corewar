/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 17:35:24 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/06 17:14:38 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
 * LEXICAL ANALYSIS
 * */

void	ft_lexical_error(char *buff, t_position *position)
{
	
}

t_tkn	*tkn_create(char *buff, t_pos *pos, t_lbl *lbls, t_tkn *tkn)
{
	tkn_create_func	tab[NB_tkn_TYPES];

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
	while (j < NB_tkn_TYPES)
	{
		if (j == lexical_sm[state_l][1])
			tab[j](buff, position, i, tkn);
		j++;
	}
	return (tkn);
}

void	tkn_initialize(t_tkn *tkn)
{
	tkn->buff_start = pos->col; // 1
	tkn->value = NULL;
	tkn->mem_size = 0;
}

int		lexical_analysis(char *line, t_pos *pos, t_tkn *tkn, t_list *lbls)
{
	int	i;

	pos->state_l = 0;
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

void	gaps_fill(char *bytebuf, t_tkn *tkn)
{
	t_list	*t1;
	t_list	*t2;
	t_lbl	*lbl;
	int		ref_int;
	short	ref_sht;

	lbl = (t_lbl*)tkn->value;
	t1 = (t_list*)lbl->frwd;
	t2 = (t_list*)lbl->frwd;
	while (t1 != NULL)
	{
		if (t1->content->mem_size == 2)
		{
			ref_sht = (short)lbl->lc_label - (short)t1->lc_instruction;
			ft_memcpy(bytebuf + tkn->lc_tkn, ref_sht + 1, 1);
			ft_memcpy(bytebuf + tkn->lc_tkn + 1, ref_sht, 1);
		}
		else if (t1->content->mem_size == 4)
		{
			ref_int = lbl->lc_label - t1->lc_instruction;
			ft_memcpy(bytebuf + tkn->lc_tkn, ref_int + 3, 1);
			ft_memcpy(bytebuf + tkn->lc_tkn + 1, ref_int + 2, 1);
			ft_memcpy(bytebuf + tkn->lc_tkn + 2, ref_int + 1, 1);
			ft_memcpy(bytebuf + tkn->lc_tkn + 3, ref_int, 1);
		}
		t2 = t2->next;
		free(t1->content);
		free(t1);
		t1 = t2;
	}
}

void	bytecode_gen(t_tkn *tkn, char *bytebuf, t_pos *pos, t_list *lbls)
{
	if (tkn->type == e_label)
	{
		gaps_fill(bytebuf, tkn)
		tkn->value->type = 'D';
	}
	else
	{
		if (tkn->mem_size == 1)
			ft_memcpy(bytebuf + tkn->lc_tkn, tkn->value, 1);
		else if (tkn->mem_size == 2)
		{
			ft_memcpy(bytebuf + tkn->lc_tkn, tkn->value + 1, 1);
			ft_memcpy(bytebuf + tkn->lc_tkn + 1, tkn->value, 1);
		}
		else if (tkn->mem_size == 4)
		{
			ft_memcpy(bytebuf + tkn->lc_tkn, tkn->value + 3, 1);
			ft_memcpy(bytebuf + tkn->lc_tkn + 1, tkn->value + 2, 1);
			ft_memcpy(bytebuf + tkn->lc_tkn + 2, tkn->value + 1, 1);
			ft_memcpy(bytebuf + tkn->lc_tkn + 3, tkn->value, 1);
		}
	}
}

void	syntactic_analysis(t_list *lbls, t_pos *pos, char *bytebuf, char *line)
{
	t_tkn	*tkn;

	while (pos->state_s != -1) //err 아닌경우
	{
		if (!(tkn = (t_tkn*)ft_memalloc(sizeof(t_tkn))))
			return (0);
		if (!lexical_analysis(line, tkn, pos, lbls))
			return ;
		pos->state_s = syntactic_sm[pos->state_s][tkn->type];
		if (pos->state_s == -1)
		{
			ERROR();
			break ;
		}
		if ((tkn->mem_size != 0 && tkn->value != NULL)
			|| ((tkn->type == e_lbl) && ((t_lbl*)(tkn->value))->type == 'U')
			bytecode_gen(tkn, bytebuf, pos, lbls); // translate the tkn we just read in bytecode
		if ((tkn->type == e_ind_label || tkn->type == e_dir_label)
			&& tkn->value == NULL)
			continue ;
		free(tkn);
	}
	pos->lc_instruction = pos.l
}

void	ft_init_main(t_list **lbls, char **bytebuf, char **line, t_pos *pos)
{
	*bytebuf = ft_strnew(BUFF_SIZE);
	*line = NULL;
	pos->line = 1;
	pos->lc_instruction = 0;
	pos->lc_tkn = 0;
	pos->state_s = 0;
	*lbls = NULL;
}

void	main_loop(void)
{
	t_list	*lbls;
	t_pos	pos; // line number and column number
	char	*bytebuf;
	char	*line;

	ft_init_main(&lbls, &bytebuf, &line, &pos);
	while ((MODIFIED_GNL(0, &read_buffer) == 1) && ERROR == 0) // line per line but should return the \n as well
	{
		syntactic_analysis(lbls, &pos, bytebuf, line);
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
