/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_create_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:08:01 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/14 16:00:55 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	tkn_register(char *buff, t_pos *pos, t_list **lbls, t_tkn *tkn)
{
	int		i;
	char 	nbr_char;
	char	*nbr_str;

	(void)lbls;
	(void)pos;
	i = tkn->buff_start + 1;
	while (buff[i] == '0')
		i++;
	if (i == tkn->buff_end && (i - 1 != tkn->buff_start && buff[i] != '0'))
		ft_printf("registers cannot have value 0\n"); // handle more properly // 0 ?
	nbr_str = ft_strndup(buff + i, tkn->buff_end - i + 1);
	if (ft_strlen(nbr_str) > 2)
		ft_printf("registers cannot have value greater than %d\n", REG_NUMBER);
	nbr_char = ft_atochar(nbr_str); //create "ft_atochar"
	if (nbr_char > 16)  // 0?
		ft_printf("registers cannot have value greater than %d\n", REG_NUMBER);
	else
	{
		tkn->type = e_register;
		if (!(tkn->value = ft_strdup(&nbr_char)))
			return (ft_error(NULL, e_malloc_error, NULL, NULL));
		tkn->mem_size = 1;
	}
	return (1);
}

int	tkn_op(char *buff, t_pos *pos, t_list **lbls, t_tkn *tkn)
{
	int		i;
	char	*name;

	(void)lbls;
	tkn->type = e_op;
	if (!(name = ft_strndup(buff + tkn->buff_start, tkn->buff_end - tkn->buff_start + 1)))
		return (ft_error(NULL, e_malloc_error, NULL, NULL));
	i = 0;
	while (i < OP_TAB_ASM_SIZE && !ft_strequ(name, g_op_tab_asm[i].name))
		i++;
	if (i == OP_TAB_ASM_SIZE)
		return (ft_error(pos, e_op_code_error, tkn, NULL));
	if (!(tkn->value = (char*)ft_memalloc(sizeof(char))))
		return (ft_error(NULL, e_malloc_error, NULL, NULL));
	*(char*)(tkn->value) = g_op_tab_asm[i].op_code;
	tkn->op = g_op_tab_asm + i;
	tkn->mem_size = 1;
	pos->arg_nbr = g_op_tab_asm[i].n_args;
	pos->ocp = g_op_tab_asm[i].ocp;
	pos->dir_bytes = g_op_tab_asm[i].dir_bytes;
	return (1);
}

int	tkn_dir_value(char *buff, t_pos *pos, t_list **lbls, t_tkn *tkn)
{
	long int	long_nbr;
	int			nbr;
	short		sh_nbr;

	(void)lbls;
	tkn->mem_size = pos->dir_bytes;
	if (tkn->buff_start - tkn->buff_end + 1 > 10)
		return (ft_error(pos, e_dir_int_error, tkn, NULL));
	long_nbr = ft_atolong(buff + tkn->buff_start + 1);
	if (tkn->mem_size == 4)
	{
		if (long_nbr > 2147483647 || long_nbr < -2147483648)
			return (ft_error(pos, e_dir_int_error, tkn, NULL));
		else
		{
			nbr = ft_atoi(buff + tkn->buff_start + 1);
			tkn->value = (void*)(&nbr);
		}
	}
	else if (tkn->mem_size == 2)
	{
		if (long_nbr > 32767 || long_nbr < -32767)
			return (ft_error(pos, e_dir_short_error, tkn, NULL));
		else
		{
			sh_nbr = ft_atos(buff + tkn->buff_start + 1);
			tkn->value = (void*)(&sh_nbr);
		}
	}
	tkn->type = e_dir_value;
	return (1);
}

int	tkn_ind_value(char *buff, t_pos *pos, t_list **lbls, t_tkn *tkn)
{
	long int	long_nbr;
	short		sh_nbr;

	(void)lbls;
	if (tkn->buff_start - tkn->buff_end + 1 > 5)
		return (ft_error(pos, e_ind_error, tkn, NULL));
	long_nbr = ft_atolong(buff + tkn->buff_start);
	if (long_nbr > 32767 || long_nbr < -32767)
		return (ft_error(pos, e_ind_error, tkn, NULL));
	else
	{
		sh_nbr = ft_atos(buff + tkn->buff_start);
		tkn->value = (void*)&sh_nbr;
	}
	tkn->type = e_ind_value;
	tkn->mem_size = 2;
	return (1);
}
