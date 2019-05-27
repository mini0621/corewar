/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:51:52 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/28 00:34:49 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

#include "libftprintf.h"
#include "op.h"
#include <unistd.h>
#include <stdlib.h>

typedef	unsigned long long t_ull;
typedef	unsigned long long t_uc;

typedef struct	s_champ;
{
	char	name[PROG_NAME_LENGTH + 1];
	char	comment[COMMENT_LENGTH + 1];
	int		id;
	int		prcs_c;
}				t_champ;

typedef struct	s_process
{
	int		id;
	int		prcs_id;
	t_uc	*regs[REG_NUMBER];
	int		wait_c;
	int		live_c;
	t_uc	*pc;
	int		carry;
}				t_process;

enum	e_argtype
{	
};

typedef struct	s_args
{
	e_argtype	type;	
	t_ull		value;
	
}				t_args;

typedef struct	s_game;
{
	int			end;
	t_champs	champs[MAX_PLAYERS];
	t_list		*prcs; //cache coherence and use t_list?
	t_ull		nbr_cycle;
	int			nbr_champs;
	t_ull		cycle;
	long long	cycle_d;
	t_ull		c_checked;
	t_ull		cycle_to_die;
	t_uc		memdump[MEM_SIZE];
}				t_game;

#endif
