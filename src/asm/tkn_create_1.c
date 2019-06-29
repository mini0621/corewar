/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_create_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:08:01 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/29 11:59:06 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <limits.h>

int			tkn_register(char *buff, t_pos *pos, t_list **lbls, t_tkn **tkn)
{
	int		i;
	char	nbr_char;
	char	*nbr_str;

	(void)lbls;
	i = (*tkn)->buff_start + 1;
	while (buff[i] == '0' && buff[i] != '\n')
		i++;
	if (!(nbr_str = ft_strndup(buff + i, (*tkn)->buff_end - i + 1)))
		return (ft_error(pos, e_malloc_error, tkn));
	if (ft_strlen(nbr_str) > 3 || ft_atoi(nbr_str) > 255)
		return (ft_error(pos, e_reg_nb_error, tkn));
	nbr_char = ft_atochar(nbr_str);
	ft_strdel(&nbr_str);
	(*tkn)->type = e_register;
	if (!((*tkn)->value = ft_strdup(&nbr_char)))
		return (ft_error(pos, e_malloc_error, tkn));
	(*tkn)->mem_size = 1;
	return (1);
}

int			tkn_op(char *buff, t_pos *pos, t_list **lbls, t_tkn **tkn)
{
	int		i;
	char	*name;

	(void)lbls;
	name = NULL;
	(*tkn)->type = e_op;
	if (!(name = ft_strndup(buff + (*tkn)->buff_start,
					(*tkn)->buff_end - (*tkn)->buff_start + 1)))
		return (ft_error(pos, e_malloc_error, tkn));
	i = 0;
	while (i < OP_TAB_ASM_SIZE && !ft_strequ(name, g_op_tab_asm[i].name))
		i++;
	free(name);
	if (i == OP_TAB_ASM_SIZE)
		return (ft_error(pos, e_op_code_error, tkn));
	if (!((*tkn)->value = (char*)ft_memalloc(sizeof(char))))
		return (ft_error(pos, e_malloc_error, tkn));
	*(char*)((*tkn)->value) = g_op_tab_asm[i].op_code;
	(*tkn)->op = g_op_tab_asm + i;
	(*tkn)->mem_size = 1;
	pos->arg_nbr = g_op_tab_asm[i].n_args;
	pos->ocp = g_op_tab_asm[i].ocp;
	pos->dir_bytes = g_op_tab_asm[i].dir_bytes;
	return (1);
}

static void	value_tkn_fill(char *buff, t_tkn **tkn,
			long int long_nbr, int start)
{
	int				neg_nb;
	unsigned int	pos_nb;
	short			neg_sh_nb;
	unsigned short	pos_sh_nb;

	if ((*tkn)->mem_size == 4 && long_nbr >= 0)
	{
		pos_nb = ft_atoui(buff + start);
		ft_memcpy((*tkn)->value, &pos_nb, (*tkn)->mem_size);
	}
	else if ((*tkn)->mem_size == 4 && long_nbr < 0)
	{
		neg_nb = ft_atoi(buff + start);
		ft_memcpy((*tkn)->value, &neg_nb, (*tkn)->mem_size);
	}
	else if ((*tkn)->mem_size == 2 && long_nbr >= 0)
	{
		pos_sh_nb = ft_atous(buff + start);
		ft_memcpy((*tkn)->value, &pos_sh_nb, (*tkn)->mem_size);
	}
	else if ((*tkn)->mem_size == 2 && long_nbr < 0)
	{
		neg_sh_nb = ft_atos(buff + start);
		ft_memcpy((*tkn)->value, &neg_sh_nb, (*tkn)->mem_size);
	}
}

int			tkn_dir_value(char *buff, t_pos *pos, t_list **lbls, t_tkn **tkn)
{
	int			i;
	long int	long_nbr;

	(void)lbls;
	i = (*tkn)->buff_start + 1;
	(*tkn)->type = e_dir_value;
	(*tkn)->mem_size = pos->dir_bytes;
	(pos->tmp_buf[i] == '-') ? (i = i + 1) : (0);
	while (buff[i] == '0')
		i++;
	if ((*tkn)->buff_end - (i - 1) > 10)
		return (ft_error(pos, e_dir_int_error, tkn));
	long_nbr = ft_atolong(buff + (*tkn)->buff_start + 1);
	if ((*tkn)->mem_size == 4 && (long_nbr > UINT32_MAX || long_nbr < INT_MIN))
		return (ft_error(pos, e_dir_int_error, tkn));
	else if ((*tkn)->mem_size == 2
		&& (long_nbr > USHRT_MAX || long_nbr < SHRT_MIN))
		return (ft_error(pos, e_dir_short_error, tkn));
	if (!((*tkn)->value = ft_memalloc((*tkn)->mem_size)))
		return (ft_error(pos, e_malloc_error, tkn));
	value_tkn_fill(buff, tkn, long_nbr, (*tkn)->buff_start + 1);
	return (1);
}

int			tkn_ind_value(char *buff, t_pos *pos, t_list **lbls, t_tkn **tkn)
{
	int				i;
	long int		long_nbr;

	(void)lbls;
	i = (*tkn)->buff_start;
	(*tkn)->mem_size = 2;
	(*tkn)->type = e_ind_value;
	(pos->tmp_buf[(*tkn)->buff_start] == '-') ? (i = i + 1) : (0);
	while (buff[i] == '0' && buff[i + 1] != '\n')
		i++;
	if ((*tkn)->buff_end - (i - 1) > 5)
		return (ft_error(pos, e_ind_error, tkn));
	long_nbr = ft_atolong(buff + (*tkn)->buff_start);
	if (long_nbr > USHRT_MAX || long_nbr < SHRT_MIN)
		return (ft_error(pos, e_ind_error, tkn));
	if (!((*tkn)->value = ft_memalloc((*tkn)->mem_size)))
		return (ft_error(pos, e_malloc_error, tkn));
	value_tkn_fill(buff, tkn, long_nbr, (*tkn)->buff_start);
	return (1);
}
