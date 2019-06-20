/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_primary_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mndhlovu <mndhlovu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 13:33:55 by mndhlovu          #+#    #+#             */
/*   Updated: 2019/06/20 15:40:39 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int          vm_verify_magic(int fd, unsigned int *magic)
{
	if ((read(fd, magic, sizeof(unsigned int))) < 0)
		return (0);
	*magic = vm_endian_conversion(*magic);
	if (*magic == (unsigned int)COREWAR_EXEC_MAGIC)
		return (fd);
	return (0);
}

static int          vm_pri_processor(int pv_number, t_champ *champ
		, t_game *game)
{
	if (game->n_state
			&& (game->pl_number + 1 < MAX_PLAYERS))
	{
		champ->id = (short)(-1 * pv_number -1);
		champ->n_id = (short)(-1 * game->pl_number);
		champ->prcs_c = 0;
		champ->live_c = 0;
		game->champs[pv_number] = champ;
		(game->nbr_champs)++;
		(game->pv_number)++;
		game->pl_number = 0;
		game->n_state = 0;
		return (1);
	}
	if (!game->n_state)
	{
		champ->id = (short)(-1 * pv_number -1);
		champ->n_id = 0;
		champ->prcs_c = 0;
		champ->live_c = 0;
		game->champs[pv_number] = champ;
		(game->nbr_champs)++;
		(game->pv_number)++;
		return (1);
	}
	return (0);
}

int                 vm_primary_parser(int fd, t_game *game)
{
	unsigned int    magic;
	unsigned int	prog_size;
	int             play_num;
	t_champ         *new;

	play_num = game->pv_number;
	if (play_num + 1 >= MAX_PLAYERS)
		return (-4);
	if (!(fd = vm_verify_magic(fd, &magic)))
		return (-1);
	if (!(new = (t_champ *)malloc(sizeof(t_champ))))
		return (-2);
	ft_bzero(new, sizeof(t_champ));
	if ((read(fd, new->name, sizeof(t_uc) * PROG_NAME_LENGTH)) < 0
		|| lseek(fd, 136, SEEK_SET) < 0
		|| read(fd, &prog_size, sizeof(unsigned int)) < 0)
		return (-2);
	prog_size = vm_endian_conversion(prog_size);
	if ((read(fd, new->comment, sizeof(t_uc) * COMMENT_LENGTH)) < 0)
		return (-2);
	new->prog_size = prog_size;
	new->fd = fd;
	if (!vm_pri_processor(play_num, new, game))
		return (-3);
	return (1);
}
