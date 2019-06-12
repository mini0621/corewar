/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 17:35:24 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/12 10:48:37 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <fcntl.h>

t_tkn	*tkn_create(char *buff, t_pos *pos, t_list **lbls, t_tkn *tkn)
{
	int j;

	tkn_fptr[0] = &tkn_label;
	tkn_fptr[1] = &tkn_register;
	tkn_fptr[2] = &tkn_op;
	tkn_fptr[3] = &tkn_dir_value;
	tkn_fptr[4] = &tkn_dir_label;
	tkn_fptr[5] = &tkn_ind_value;
	tkn_fptr[6] = &tkn_ind_label;
	tkn_fptr[7] = &tkn_cmd;
	tkn_fptr[8] = &tkn_separator;
	tkn_fptr[9] = &tkn_carr_ret;

	j = 0;
	while (j < NB_TKN_TYPES)
	{
		if (j == lex_sm[pos->state_l][1])
		{
			tkn_fptr[j](buff, pos, lbls, tkn);
			break ;
		}
		j++;
	}
	return (tkn);
}

int	lexical_analysis(char *line, t_pos *pos, t_tkn **tkn, t_list **lbls)
{
	int	i;

	pos->state_l = 0;
	if (!(*tkn = (t_tkn*)ft_memalloc(sizeof(t_tkn))))
		return (0); //error
	(*tkn)->buff_start = pos->col; // 1
	while (pos->state_l != -1)  // except every finals and err
	{
		i = 0;
		while (i < NB_LSM_COL && !ft_strchr(lsm_col[i], line[pos->col]))
			i++;
		pos->state_l = lex_sm[pos->state_l][i];
		if (pos->state_l == -1)
			break;
		if (pos->state_l == 0)
			(*tkn)->buff_start++;
		if (lex_sm[pos->state_l][0] == -2 || lex_sm[pos->state_l][0] == -3)
		{
			if (lex_sm[pos->state_l][0] == -3)
				pos->col--;
			(*tkn)->buff_end = pos->col;
			tkn_create(line, pos, lbls, *tkn);  //**
			pos->col++;
			return (1);
		}
		pos->col++;
	}
	error(pos, 1, *tkn); // hangle more properly
	return (0);
}

void ocp_create(t_tkn *tkn, t_pos *pos, char *bytebuf)
{
	char a;

	if (tkn->type == e_register)
		a = 0b00000001;
	if (tkn->type == e_dir_label || tkn->type == e_dir_value)
		a = 0b00000010;
	if (tkn->type == e_ind_label || tkn->type == e_ind_value)
		a = 0b00000011;
	if (tkn->type == e_register || tkn->type == e_ind_label || tkn->type == e_ind_value
		|| tkn->type == e_dir_label || tkn->type == e_dir_value) // pos->ocp_nbr >= 1
	{
		if (*(bytebuf + pos->lc_instruction + 1) == '\0')
			*(bytebuf + pos->lc_instruction + 1) = a;
		else if (*(bytebuf + pos->lc_instruction + 1) > 0 && *(bytebuf + pos->lc_instruction + 1) < 4)
		{
			*(bytebuf + pos->lc_instruction + 1) = *(bytebuf + pos->lc_instruction + 1) << 2;
			*(bytebuf + pos->lc_instruction + 1) = *(bytebuf + pos->lc_instruction + 1) | a;
		}
		else if (*(bytebuf + pos->lc_instruction + 1) > 3)
		{
			*(bytebuf + pos->lc_instruction + 1) = *(bytebuf + pos->lc_instruction + 1) << 2;
			*(bytebuf + pos->lc_instruction + 1) = *(bytebuf + pos->lc_instruction + 1) | a;
		}
	}
}

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
		ref_sht = lbl->lc_lbl_inst - ((t_tkn*)(t1->content))->lc_instruction;
		ft_memcpy(bytebuf + tkn->lc_tkn, &ref_sht, tkn->mem_size);
		ft_memrev(bytebuf + tkn->lc_tkn, tkn->mem_size);
		t2 = t2->next;
		free(t1->content);
		free(t1);
		t1 = t2;
	}
}

void	bytecode_gen(t_tkn *tkn, char *bytebuf, t_pos *pos, t_list *lbls)
{
	if (tkn->type == e_lbl)
	{
		gaps_fill(bytebuf, tkn);
		((t_lbl*)(tkn->value))->type = 'D';
	}
	else
	{
		if (tkn->mem_size == 1)
			ft_memcpy(bytebuf + pos->lc_tkn, tkn->value, 1);
		else
		{
			ft_memcpy(bytebuf + pos->lc_tkn, tkn->value, tkn->mem_size);
			ft_memrev(bytebuf + pos->lc_tkn, tkn->mem_size);
		}
	}
}

void	bytebuf_realloc(char **bytebuf, t_pos *pos, t_tkn *tkn)
{
	if (pos->bytebf_remain < tkn->mem_size
		|| (tkn->type == e_op && ((t_op_asm*)(tkn->value))->ocp == 1 && pos->bytebf_remain < 2))
		{
			pos->bytebf_size = pos->bytebf_size + BUFF_SIZE_COR;
			*bytebuf = realloc(*bytebuf, pos->bytebf_size);
			pos->bytebf_remain = pos->bytebf_remain + BUFF_SIZE_COR;
		}
}

int	syntactic_analysis(t_list **lbls, t_pos *pos, char **bytebuf, char *line)
{
	t_tkn	*tkn;

	while (pos->state_s != -1 && pos->col < pos->size_line) //err 아닌경우
	{

		if (!lexical_analysis(line, pos, &tkn, lbls))
			return (0);
		pos->state_s = syntactic_sm[pos->state_s][tkn->type];
		if (pos->state_s == -1)
			return (0);
		if (syntactic_sm[pos->state_s][0] < -1)
			check_state_s(pos, tkn);
		bytebuf_realloc(bytebuf, pos, tkn);
		if (tkn->type == e_lbl)
			pos->lc_instruction = pos->lc_tkn;
		if ((tkn->mem_size != 0 && tkn->value != NULL)
			|| ((tkn->type == e_lbl) && ((t_lbl*)(tkn->value))->type == 'U'))
			bytecode_gen(tkn, *bytebuf, pos, *lbls);
		if (tkn->type == e_op && ((t_op_asm*)(tkn->value))->ocp == 1)
		{
			pos->lc_tkn = pos->lc_tkn + 1;
			pos->bytebf_remain = pos->bytebf_remain - 1;
		}
		if (tkn)
			ocp_create(tkn, pos, *bytebuf);
		pos->lc_tkn = pos->lc_tkn + tkn->mem_size;
		pos->bytebf_remain = pos->bytebf_remain - tkn->mem_size;
		if ((tkn->type == e_ind_label || tkn->type == e_dir_label)
			&& tkn->value == NULL)
			continue ;
		free(tkn);
	}
	return (1);
}

void	ft_init_main(t_list **lbls, char **bytebuf, char **line, t_pos *pos)
{
	*bytebuf = (char*)ft_memalloc(BUFF_SIZE_COR);
	*line = NULL;
	*lbls = NULL;
	pos->bytebf_remain = BUFF_SIZE_COR;
	pos->bytebf_size = pos->bytebf_remain;
	pos->line = 0;
	pos->lc_instruction = 0;
	pos->lc_tkn = 0;
	pos->state_s = 0;
}

void ocp_modify(t_pos *pos, char *bytebuf)
{
	if (pos->ocp_nbr == 1)
		*(bytebuf + pos->lc_instruction + 1) = *(bytebuf + pos->lc_instruction + 1) << 6;
	else if (pos->ocp_nbr == 2)
		*(bytebuf + pos->lc_instruction + 1) = *(bytebuf + pos->lc_instruction + 1) << 4;
	else if (pos->ocp_nbr == 3)
		*(bytebuf + pos->lc_instruction + 1) = *(bytebuf + pos->lc_instruction + 1) << 2;
	pos->ocp_nbr = 0;
	//variable nbr error? already before in syntactic
}

int		end_lbl(t_list *lbls)
{
	t_list 	*tmp_l;
	t_list	*tmp_t;
	int		flag;

	tmp_l = lbls;
	flag = 1;
	while (tmp_l)
	{
		if (((t_lbl*)(tmp_l->content))->type == 'U')
		{
			ft_printf("ERROR -\nLabel \" %s \" has never been declared\n", ((t_lbl*)(tmp_l->content))->name);
			tmp_t = ((t_lbl*)(tmp_l->content))->frwd;
			while (tmp_t)
			{
				ft_printf("Used as an argument in instruction address %d\n", ((t_tkn*)(tmp_t->content))->lc_instruction);
				tmp_t = tmp_t->next;
			}
			flag = 0;
		}
		tmp_l = tmp_l->next;
	}
	return (flag);
}

void	ft_write_output(char *argv, char *bytebuf, t_pos *pos)
{
	//open(O_CREAT)
}

int	main_loop(int fd, char **bytebuf, t_pos *pos)
{
	char	*line;
	t_list	*lbls;
	int		error;

	error = 0;
	ft_init_main(&lbls, bytebuf, &line, pos);
	while ((pos->size_line = read_bytes(&line, error, fd)) > 0) // line per line but should return the \n as well
	{
		pos->col = 0;
		pos->line++;
		if (!(syntactic_analysis(&lbls, pos, bytebuf, line)))
		{
			error = 1;
			continue ;
		}
		ocp_modify(pos, *bytebuf);
		if (line)
			free(line);
	}
	if (line)
		free(line);
	if (!error && end_lbl(lbls)) // checks if all label used have been created effectively. If Undefined values still il symbol table, return error
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	int		fd;
	int		end;
	char	*bytebuf;
	t_pos	pos;

	if (argc != 2)
		return (0);
	end = 0;
	if ((fd = open(argv[1], O_RDONLY)) < 0)
	{
		ft_printf("error\n"); // handle more properly
		return (0);
	}
	if (main_loop(fd, &bytebuf, &pos))
		ft_write_output(argv[1], bytebuf, &pos);
	return (0);
}
