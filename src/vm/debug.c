/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 21:12:15 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/27 14:20:04 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	get_debug(t_game *game, t_champ *champ, int id)
{
	char	*tmp;
	int		l;

	tmp = NULL;
	if (!(game->deb_state))
		return ;
	if (!champ && !id  && game->deb_state & 1)
		l = ft_asprintf(&tmp, "    cycle: %i\n", game->cycle);
	else if (champ && !id && game->deb_state & 2)
		l = ft_asprintf(&tmp, "    death: champ(%hhd) \"%s\"\n", champ->id, champ->name);
	else if (!champ && id && game->deb_state & 2)
		l = ft_asprintf(&tmp, "    death: process(%d)\n", id);
	else
		return ;
	update_logs(game, &tmp, l);
}

void	reset_debug(t_game *game)
{
	if (game->deb_state && game->logs)
	{
		free(game->logs);
		game->logs = ft_strnew(0);
		game->logs_len = 0;
	}
}

void	print_debug(t_game *game)
{
	if (game->deb_state && !game->visu && game->logs)
		write(1, game->logs, game->logs_len);
}
