/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:47:54 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/25 18:40:21 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
#define VISU_H

#define VISU_SPEED 1
#include <ncurses.h>
#include "op.h"

typedef struct	t_visu
{
	WINDOW	*dump_win;
	WINDOW	*menu_win;
	WINDOW	*logs_win;
	int		sp;
	short	clr_map[MEM_SIZE];
}				t_visu;

#endif
