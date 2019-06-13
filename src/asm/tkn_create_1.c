/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_create_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:08:01 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/13 11:03:18 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	tkn_register(char *buff, t_pos *pos, t_list **lbls, t_tkn *tkn)
{
	int		i;
	char 	nbr_char;
	char	*nbr_str;

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
		tkn->value = ft_strdup(&nbr_char);
		tkn->mem_size = 1;
	}
	return (1);
}

int	tkn_op(char *buff, t_pos *pos, t_list **lbls, t_tkn *tkn)
{
	int		i;
	char	*name;

	tkn->type = e_op;
	name = ft_strndup(buff + tkn->buff_start, tkn->buff_end - tkn->buff_start + 1);
	i = 0;
	while (i < OP_TAB_ASM_SIZE && !ft_strequ(name, g_op_tab_asm[i].name))
		i++;
	if (i == OP_TAB_ASM_SIZE)
		ft_printf("invalide op_code\n"); // handle more properly
	tkn->value = g_op_tab_asm + i;
	tkn->mem_size = 1;
	pos->arg_nbr = g_op_tab_asm[i].n_args;
	pos->ocp = g_op_tab_asm[i].ocp;
	pos->dir_bytes = g_op_tab_asm[i].dir_bytes; // changed the name of op_tab_asm
	return (1);
}

int	tkn_dir_value(char *buff, t_pos *pos, t_list **lbls, t_tkn *tkn)
{
	long int	long_nbr;
	int			nbr;
	short		sh_nbr;

	tkn->mem_size = pos->dir_bytes;
	if (tkn->buff_start - tkn->buff_end + 1 > 10)
		error(pos, 1, tkn);  //fix
	long_nbr = ft_atolong(buff + tkn->buff_start + 1);
	if (tkn->mem_size == 4)
	{
		if (long_nbr > 2147483647 || long_nbr < -2147483648)
			error(pos, 1, tkn);  //fix
		else
		{
			nbr = ft_atoi(buff + tkn->buff_start + 1);
			tkn->value = (void*)(&nbr);
		}
	}
	else if (tkn->mem_size == 2)
	{
		if (long_nbr > 32767 || long_nbr < -32767)
			error(pos, 1, tkn);  //fix
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

	if (tkn->buff_start - tkn->buff_end + 1 > 10)
		error(pos, 1, tkn);  //fix
	long_nbr = ft_atolong(buff + tkn->buff_start);
	if (long_nbr > 32767 || long_nbr < -32767)
		error(pos, 1, tkn);  //fix
	else
	{
		sh_nbr = ft_atos(buff + tkn->buff_start);
		tkn->value = (void*)&sh_nbr;
	}
	tkn->type = e_ind_value;
	tkn->mem_size = 2;
	return (1);
}
