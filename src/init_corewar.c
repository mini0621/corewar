/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:18:54 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/27 22:24:45 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

//get "-dump nbr_cycle" part.
//read and update arg ptr
//if it doesn't exist return av+1
//if error return NULL
static char	**get_options(char **av)
{
	char	**arg;
	arg = av + 1;
}

//creates process
t_process	init_prcs(int id, t_uc *pc)
{

}

//malloc all the champs and copy the instructions into memdump
//create the first prcs then store them in game->prcs
static int	read_champs(t_game *game, char **arg)
{
	t_champ	*tmp;
	int		nbr_champs;
}

//read all the options, store champs, init game and read infos
//if error, return 0
int			init_corewar(t_game *game, int ac, char **av)
{
	char	**arg;

	//bzero everything
	if (ac < 2 || !(arg = get_options(av)))
		return (0);
	if (!read_champs(game, arg))
		return (0);
}
