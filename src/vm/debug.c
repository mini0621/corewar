/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 21:12:15 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/10 03:04:38 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	get_debug(t_game *game, t_inst *inst, t_process *caller, t_champ *champ)
{
	t_arg	*args;
	char	*tmp;
	int		l;

	tmp = NULL;
	if (!(game->deb_state))
		return ;
	if (inst)
		return (print_inst(game, inst, caller, (get_op(inst))->opcode));
	if (!champ)
		l = ft_asprintf(&tmp, "    cycle: %i\n", game->cycle);
	else
		l = ft_asprintf(&tmp, "    death: champ(%hhd)\n", champ->id);
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
