/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:47:54 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/06 21:27:31 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
#define VISU_H

#include <ncurses.h>

# define CLR_P1 1
# define CLR_P2 2
# define CLR_P3 3
# define CLR_P4 4


typedef struct	t_visu
{
	WINDOW	*dump_win;
	WINDOW	*menu_win;
}				t_visu;

#endif
