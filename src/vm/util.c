/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 17:21:10 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/11 02:56:57 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_op	*get_op(t_inst *inst)
{
	return ((t_op *)(inst->op));
}

void	memcpy_inv(void *dst, void *src, size_t size)
{
	if (!dst || !src)
		return ;
	ft_memcpy(dst, src, size);
	endian_conv(dst, size);
}

void	update_logs(t_game *game, char **new, size_t l)
{
	char	*tmp;

	if (!(tmp = ft_strjoinfree(&(game->logs), new, 3)))
		return ;
	game->logs = tmp;
	game->logs_len += l;
}
