/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst01_live.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:44:18 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/25 18:18:43 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	deb_4_log(t_game *game, int p_id, int c_id, int id)
{
	char	*tmp;
	int		l;

	tmp = NULL;
	l = ft_asprintf(&tmp, "process(%i)/champ(%i): live for champ(%i)!\n",
			p_id, c_id, id);
	update_logs(game, &tmp, l);
}

void	inst_live(t_game *game, t_process *caller, t_inst *inst)
{
	int	i;
	int	id;

	if (!game || !caller || !inst)
		return ;
	inst->args[0].type = e_dir;
	caller->is_alive = 1;
	id = (int)*get_arg(caller, game->memdump, &(inst->args[0]), 0);
	i = 0;
	while (game->champs[i])
	{
		if (game->champs[i]->id == id)
		{
			if (!game->print_off || game->print_off == 2)
				ft_printf("A process shows that player %i (%s) is alive\n",
					-id, game->champs[i]->name);
			(game->champs[i]->live_c)++;
			break;
		}
		i++;
	}
	game->live_count += 1;
	if (game->deb_state & 4)
		deb_4_log(game, caller->p_id, caller->c_id, id);
}
