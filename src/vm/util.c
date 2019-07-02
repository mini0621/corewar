/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 17:21:10 by mnishimo          #+#    #+#             */
/*   Updated: 2019/07/02 16:51:58 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_op			*get_op(t_inst *inst)
{
	return ((t_op *)(inst->op));
}

void			memcpy_inv(void *dst, void *src, size_t size)
{
	if (!dst || !src)
		return ;
	ft_memcpy(dst, src, size);
	endian_conv(dst, size);
}

void			update_logs(t_game *game, char **new, size_t l)
{
	char		*tmp;

	if (!(tmp = ft_strjoinfree(&(game->logs), new, 3)))
		return ;
	game->logs = tmp;
	game->logs_len += l;
}

void			reset_prcs_c(t_game *game)
{
	int			i;

	i = 0;
	while (i < game->nbr_champs)
	{
		game->champs[i]->prcs_c = 0;
		i++;
	}
}

void			ft_hexdump(t_uc *dump)
{
	t_uc		*ptr;
	int			i;

	ptr = dump;
	i = 0;
	ft_printf("0x0000 :");
	while (i < MEM_SIZE)
	{
		if (i && !(i % 32))
			ft_printf("\n%#06x :", ptr - dump);
		ft_printf(" %.2hhx", *ptr);
		ptr++;
		i++;
	}
	ft_printf("\n");
}
