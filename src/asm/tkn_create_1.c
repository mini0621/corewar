/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_create_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:08:01 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/20 22:45:39 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	tkn_register(char *buff, t_pos *pos, t_list **lbls, t_tkn **tkn)
{
	int		i;
	char	nbr_char;
	char	*nbr_str;

	(void)lbls;
	i = (*tkn)->buff_start + 1;
	while (buff[i] == '0' && buff[i] != '\n')
		i++;
//	if (i == (*tkn)->buff_end && (i - 1 != (*tkn)->buff_start && buff[i] == '0'))
//		return (ft_error(pos, e_reg_nb_error, tkn));
	if (buff[i] == '\n')
		return (ft_error(pos, e_reg_nb_error, tkn));
	nbr_str = ft_strndup(buff + i, (*tkn)->buff_end - i + 1);
	if (ft_strlen(nbr_str) > 2)
		return (ft_error(pos, e_reg_nb_error, tkn));
	nbr_char = ft_atochar(nbr_str);
	ft_strdel(&nbr_str);
	if (nbr_char > 16)  // 0?
		return (ft_error(pos, e_reg_nb_error, tkn));
	else
	{
		(*tkn)->type = e_register;
		if (!((*tkn)->value = ft_strdup(&nbr_char)))
			return (ft_error(NULL, e_malloc_error, tkn));
		(*tkn)->mem_size = 1;
	}
	return (1);
}

int	tkn_op(char *buff, t_pos *pos, t_list **lbls, t_tkn **tkn)
{
	int		i;
	char	*name;

	(void)lbls;
	name = NULL;
	(*tkn)->type = e_op;
	if (!(name = ft_strndup(buff + (*tkn)->buff_start, (*tkn)->buff_end - (*tkn)->buff_start + 1)))
		return (ft_error(NULL, e_malloc_error, tkn));
	i = 0;
	while (i < OP_TAB_ASM_SIZE && !ft_strequ(name, g_op_tab_asm[i].name))
		i++;
	free(name);
	if (i == OP_TAB_ASM_SIZE)
		return (ft_error(pos, e_op_code_error, tkn));
	if (!((*tkn)->value = (char*)ft_memalloc(sizeof(char))))
		return (ft_error(NULL, e_malloc_error, tkn));
	*(char*)((*tkn)->value) = g_op_tab_asm[i].op_code;
	(*tkn)->op = g_op_tab_asm + i;
	(*tkn)->mem_size = 1;
	pos->arg_nbr = g_op_tab_asm[i].n_args;
	pos->ocp = g_op_tab_asm[i].ocp;
	pos->dir_bytes = g_op_tab_asm[i].dir_bytes;
	return (1);
}

int	tkn_dir_value(char *buff, t_pos *pos, t_list **lbls, t_tkn **tkn)
{
	long int	long_nbr;
	int			nbr;
	short		sh_nbr;

	(void)lbls;
	(*tkn)->mem_size = pos->dir_bytes;
	if ((*tkn)->buff_end - (*tkn)->buff_start > 10)
		return (ft_error(pos, e_dir_int_error, tkn));
	long_nbr = ft_atolong(buff + (*tkn)->buff_start + 1);
	if ((*tkn)->mem_size == 4)
	{
		if (long_nbr > 2147483647 || long_nbr < -2147483648)
			return (ft_error(pos, e_dir_int_error, tkn));
		else
		{
			nbr = ft_atoi(buff + (*tkn)->buff_start + 1);
			(*tkn)->value = ft_memalloc((*tkn)->mem_size);
			ft_memcpy((*tkn)->value, &nbr, (*tkn)->mem_size);
		}
	}
	else if ((*tkn)->mem_size == 2)
	{
		if (long_nbr > 32767 || long_nbr < -32767)
			return (ft_error(pos, e_dir_short_error, tkn));
		else
		{
			sh_nbr = ft_atos(buff + (*tkn)->buff_start + 1);
			(*tkn)->value = ft_memalloc((*tkn)->mem_size);
			ft_memcpy((*tkn)->value, &sh_nbr, (*tkn)->mem_size);
		}
	}
	(*tkn)->type = e_dir_value;
	return (1);
}

int	tkn_ind_value(char *buff, t_pos *pos, t_list **lbls, t_tkn **tkn)
{
	long int	long_nbr;
	short		sh_nbr;

	(void)lbls;
	if ((*tkn)->buff_end - (*tkn)->buff_start + 1 > 5)
		return (ft_error(pos, e_ind_error, tkn));
	long_nbr = ft_atolong(buff + (*tkn)->buff_start);
	if (long_nbr > 32767 || long_nbr < -32767)
		return (ft_error(pos, e_ind_error, tkn));
	else
	{
		(*tkn)->mem_size = pos->dir_bytes;
		sh_nbr = ft_atos(buff + (*tkn)->buff_start);
		(*tkn)->value = ft_memalloc((*tkn)->mem_size);
		ft_memcpy((*tkn)->value, &sh_nbr, (*tkn)->mem_size);
	}
	(*tkn)->type = e_ind_value;
	(*tkn)->mem_size = 2;
	return (1);
}
