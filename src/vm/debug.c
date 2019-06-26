/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 21:12:15 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/16 23:02:26 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	get_debug(t_game *game, t_champ *champ)
{
	char	*tmp;
	int		l;

	tmp = NULL;
	if (!(game->deb_state))
		return ;
	if (!champ && game->deb_state & 1)
		l = ft_asprintf(&tmp, "    cycle: %i\n", game->cycle);
	else if (champ && game->deb_state & 2)
		l = ft_asprintf(&tmp, "    death: champ(%hhd)\n", champ->id);
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
