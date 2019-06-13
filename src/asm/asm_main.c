/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 17:35:24 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/13 12:30:31 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <fcntl.h>

t_tkn	*tkn_create(char *buf, t_pos *pos, t_list **lbls, t_tkn *tkn)
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
			tkn_fptr[j](buf, pos, lbls, tkn);
			break ;
		}
		j++;
	}
	return (tkn);
}

int	lexical_analysis(char *buf, t_pos *pos, t_tkn **tkn, t_list **lbls)
{
	int	i;


	if (!(*tkn = (t_tkn*)ft_memalloc(sizeof(t_tkn))))
		return (0); //error
	if (pos->state_l != 24)
	{
		pos->state_l = 0;
		(*tkn)->buff_start = pos->buf_pos; // 1
	}
	while (pos->state_l != -1 && pos->buf_pos < pos->size_buf)  // except every finals and err
	{
		i = 0;
		while (i < NB_LSM_COL && !ft_strchr(lsm_col[i], buf[pos->buf_pos]))
			i++;
		pos->state_l = lex_sm[pos->state_l][i];
		if (pos->state_l == -1)
			break;
		if (pos->state_l == 0)
			(*tkn)->buff_start++;
		if (lex_sm[pos->state_l][0] == -2 || lex_sm[pos->state_l][0] == -3)
		{
			if (lex_sm[pos->state_l][0] == -3)
				pos->buf_pos--;
			(*tkn)->buff_end = pos->buf_pos;
			tkn_create(buf, pos, lbls, *tkn);  //**
			pos->buf_pos++;
			return (1);
		}
		pos->buf_pos++;
	}
	if (pos->state_l == 24)
		return (10);
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
		|| tkn->type == e_dir_label || tkn->type == e_dir_value) // pos->arg_nbr >= 1
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
		tkn = (t_tkn*)t1->content;
		if (tkn->mem_size == 2)
		{
			ref_sht = lbl->lc_lbl_inst - tkn->lc_instruction;
			ft_memcpy(bytebuf + tkn->lc_tkn, &ref_sht, tkn->mem_size);
			ft_memrev(bytebuf + tkn->lc_tkn, tkn->mem_size);
		}
		else
		{
			ref_int = lbl->lc_lbl_inst - tkn->lc_instruction;
			ft_memcpy(bytebuf + tkn->lc_tkn, &ref_int, tkn->mem_size);
			ft_memrev(bytebuf + tkn->lc_tkn, tkn->mem_size);
		}
		t2 = t2->next;
		free(t1->content);
		free(t1);
		t1 = t2;
	}
}

void	command_buf_fill(t_bytebf *bytebf, t_tkn *tkn, t_pos *pos)
{
	int	i;

	i = 0;
	if (tkn->type == e_cmd_comment)
		while (i < pos->comment_len)
		{
			if (*(char*)(tkn->value + i) != '\0')
				bytebf->comment[i] = *(char*)(tkn->value + i);
			i++;
		}
	else
	{
		while (i < pos->name_len)
		{
			if (*(char*)(tkn->value + i) != '\0')
				bytebf->name[i] = *(char*)(tkn->value + i);
			i++;
		}
	}
}

void	bytecode_gen(t_tkn *tkn, t_bytebf *bytebf, t_pos *pos, t_list *lbls)
{
	if (tkn->type == e_lbl)
	{
		gaps_fill(bytebf->inst, tkn);
		((t_lbl*)(tkn->value))->type = 'D';
	}
	else if (tkn->type == e_cmd_comment || tkn->type == e_cmd_name)
		command_buf_fill(bytebf, tkn, pos);
	else
	{
		if (tkn->mem_size == 1)
			ft_memcpy(bytebf->inst + pos->lc_tkn, tkn->value, 1);
		else
		{
			ft_memcpy(bytebf->inst + pos->lc_tkn, tkn->value, tkn->mem_size);
			ft_memrev(bytebf->inst + pos->lc_tkn, tkn->mem_size);
		}
	}
}

void	bytebuf_realloc(t_bytebf *bytebf, t_pos *pos, t_tkn *tkn)
{
	if (bytebf->inst_remain < tkn->mem_size
		|| (tkn->type == e_op && ((t_op_asm*)(tkn->value))->ocp == 1 && bytebf->inst_remain < 2))
		{
			bytebf->inst_size = bytebf->inst_size + BUFF_SIZE_COR;
			bytebf->inst = realloc(bytebf->inst, bytebf->inst_size);
			bytebf->inst_remain = bytebf->inst_remain + BUFF_SIZE_COR;
		}
}

int	syntactic_analysis(t_list **lbls, t_pos *pos, t_bytebf *bytebf, char *buf)
{
	t_tkn	*tkn;
	int		ret;

	while (pos->state_s != -1 && pos->buf_pos < pos->size_buf) //err 아닌경우
	{

		if (!(ret = lexical_analysis(buf, pos, &tkn, lbls)))
			return (0);
		else if (ret == 10)
			return (10);
		pos->state_s = syntactic_sm[pos->state_s][tkn->type];
		if (pos->state_s == -1)
			return (0);
		if (syntactic_sm[pos->state_s][0] < -1)
			check_state_s(pos, tkn);
		bytebuf_realloc(bytebf, pos, tkn);
		if (tkn->type == e_lbl || tkn->type == e_op)
			pos->lc_instruction = pos->lc_tkn;
		if ((tkn->mem_size != 0 && tkn->value != NULL)
			|| ((tkn->type == e_lbl) && ((t_lbl*)(tkn->value))->type == 'U')
			|| tkn->type == e_cmd_comment || tkn->type == e_cmd_name)
			bytecode_gen(tkn, bytebf, pos, *lbls);
		if (tkn->type == e_op && ((t_op_asm*)(tkn->value))->ocp == 1)
		{
			pos->lc_tkn = pos->lc_tkn + 1;
			bytebf->inst_remain = bytebf->inst_remain - 1;
		}
		if (tkn && pos->ocp)
			ocp_create(tkn, pos, bytebf->inst);
		pos->lc_tkn = pos->lc_tkn + tkn->mem_size;
		bytebf->inst_remain = bytebf->inst_remain - tkn->mem_size;
		if ((tkn->type == e_ind_label || tkn->type == e_dir_label)
			&& tkn->value == NULL)
			continue ;
		free(tkn);
	}
	return (1);
}

void	ft_init_main(t_list **lbls, t_bytebf *bytebf, char **line, t_pos *pos)
{
	int	magic;

	bytebf->inst = (char*)ft_memalloc(BUFF_SIZE_COR);
	bytebf->inst_remain = BUFF_SIZE_COR;
	bytebf->inst_size = bytebf->inst_remain;
	bytebf->magic = (char*)ft_memalloc(4);
	magic = COREWAR_EXEC_MAGIC;
	ft_memcpy(bytebf->magic, &magic, 4);
	ft_memrev(bytebf->magic, 4);
	ft_bzero(bytebf->offset1, 4);
	ft_bzero(bytebf->offset2, 4);
	ft_bzero(bytebf->name, PROG_NAME_LENGTH);
	ft_bzero(bytebf->comment, COMMENT_LENGTH);
	bytebf->prog_size = (char*)ft_memalloc(4);
	*line = NULL;
	*lbls = NULL;
	pos->file_line = 0;
	pos->buf_pos = 0;
	pos->lc_instruction = 0;
	pos->lc_tkn = 0;
	pos->state_s = 0;
	pos->size_buf = 0;
}

void ocp_modify(t_pos *pos, char *bytebuf)
{
	if (pos->arg_nbr == 1)
		*(bytebuf + pos->lc_instruction + 1) = *(bytebuf + pos->lc_instruction + 1) << 6;
	else if (pos->arg_nbr == 2)
		*(bytebuf + pos->lc_instruction + 1) = *(bytebuf + pos->lc_instruction + 1) << 4;
	else if (pos->arg_nbr == 3)
		*(bytebuf + pos->lc_instruction + 1) = *(bytebuf + pos->lc_instruction + 1) << 2;
	pos->arg_nbr = 0;
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

void	init_after_read(t_pos *pos, char **buf, char **read_line)
{
	char	*tmp;

	pos->file_col = 0;
	pos->file_line++;
	tmp = *buf;
	*buf = ft_memjoin(*buf, *read_line, pos->size_buf, pos->size_line);
	ft_strdel(read_line);
	ft_strdel(&tmp);
	pos->size_buf = pos->size_buf + pos->size_line;
}

void	fill_bytefb(t_bytebf *bytebf, t_pos *pos)
{
	bytebf->hd_size = 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4;
	bytebf->header = (char *)ft_memalloc(bytebf->hd_size);  //malloc protection!
	ft_memcpy(bytebf->header, bytebf->magic, 4);
	ft_memcpy(bytebf->header + 4, bytebf->name, PROG_NAME_LENGTH);
	ft_memcpy(bytebf->header + 4 + PROG_NAME_LENGTH, bytebf->offset1, 4);
	ft_memcpy(bytebf->header + 8 + PROG_NAME_LENGTH, "size", 4); // change program size
	ft_memcpy(bytebf->header +  12 + PROG_NAME_LENGTH, bytebf->comment, COMMENT_LENGTH);
	ft_memcpy(bytebf->header + 12 + PROG_NAME_LENGTH + COMMENT_LENGTH, bytebf->offset2, 4);

	bytebf->bytebuf = (char *)ft_memalloc(bytebf->hd_size + pos->lc_tkn);
	ft_memcpy(bytebf->bytebuf, bytebf->header, bytebf->hd_size);
	ft_memcpy(bytebf->bytebuf + bytebf->hd_size, bytebf->inst, pos->lc_tkn);
}

void	ft_write_output(t_bytebf *bytebf, t_pos *pos, char *name)
{
	int fd;
	char *tmp;
	char *f_name;
	int	errno;
	int	i;

	errno = 0;
	tmp = ft_strndup(name, ft_strlen(name) - 2);
	f_name = ft_strjoin(tmp, ".cor");
	ft_strdel(&tmp);
	if ((fd = open(f_name, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1) //0644 = chmod
		ft_printf("\n ASM failed with error [%s]\n", strerror(errno));
	else
	{
		fill_bytefb(bytebf, pos);
		if ((i = write(fd, bytebf->bytebuf, pos->lc_tkn + bytebf->hd_size)) == -1)
			ft_printf("\n ASM failed with error [%s]\n", strerror(errno));
		else
			ft_printf("Write output to %s\n", f_name);
	}
}

int	main_loop(int fd, t_bytebf *bytebf, t_pos *pos)
{
	char	*read_line;
	char	*buf;
	int		error;
	t_list	*lbls;
	int		ret;

	error = 0;
	ft_init_main(&lbls, bytebf, &read_line, pos);
	while ((pos->size_line = read_bytes(&read_line, error, fd)) > 0) // line per line but should return the \n as well
	{
		init_after_read(pos, &buf, &read_line);
		if (!(ret = syntactic_analysis(&lbls, pos, bytebf, buf)))
		{
			error = 1;
			continue ;
		}
		else if (ret == 10)
			continue ;
		ft_strdel(&buf);
		pos->size_buf = 0;
		pos->buf_pos = 0;
		if (pos->ocp)
			ocp_modify(pos, bytebf->inst);
	}
	if (buf)
		free(buf);
	if (!error && end_lbl(lbls)) // checks if all label used have been created effectively. If Undefined values still il symbol table, return error
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	int			fd;
	int			end;
	t_bytebf	bytebf;
	t_pos		pos;

	if (argc != 2)
		return (0);
	// check if file is valide (file name, ext)
	end = 0;
	if ((fd = open(argv[1], O_RDONLY)) < 0)
	{
		ft_printf("error\n"); // handle more properly
		return (0);
	}
	if (main_loop(fd, &bytebf, &pos))
		ft_write_output(&bytebf, &pos, argv[1]);
	return (0);
}
