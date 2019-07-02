/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis_decode_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 13:04:30 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/07/02 10:57:13 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int				dis_append_str_instr(t_dis_game *game, char *instr)
{
	t_inst_store		*new;
	t_inst_store		*cur;

	if (!(new = (t_inst_store *)malloc(sizeof(t_inst_store))))
		return (0);
	new->size = ft_strlen(instr);
	new->instr = instr;
	new->next = NULL;
	if (game->store == NULL)
		game->store = new;
	else
	{
		cur = game->store;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
	(game->length)++;
	return (1);
}

static void				dis_get_inst_util(t_instr_node *node
						, char **str, int index)
{
	char	*tmp;

	tmp = ft_itoa(node->instr->args[index].data_dump);
	if (T_REG == node->instr->args[index].type)
	{
		*str = ft_strcat(*str, "r");
		*str = ft_strcat(*str, tmp);
	}
	else if (T_DIR == node->instr->args[index].type)
	{
		*str = ft_strcat(*str, "%");
		*str = ft_strcat(*str, tmp);
	}
	else
		*str = ft_strcat(*str, tmp);
	if (index + 1 == node->instr->op->nb_args)
	{
		*str = ft_strcat(*str, "\t\t#");
		*str = ft_strcat(*str, node->instr->op->description);
		*str = ft_strcat(*str, "\n");
	}
	else
		*str = ft_strcat(*str, ", ");
	free(tmp);
}

int						dis_get_instr(t_dis_game *game, t_instr_node *node)
{
	int					index;
	char				*str;

	index = -1;
	if (!(str = ft_strnew(256)))
		return (0);
	str = ft_strcat(str, "\t\t");
	str = ft_strcat(str, node->instr->op->name);
	str = ft_strcat(str, "\t");
	while (++index < node->instr->op->nb_args)
		dis_get_inst_util(node, &str, index);
	if (!dis_append_str_instr(game, str))
		return (0);
	return (1);
}
