/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:51:52 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/28 19:26:41 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

#include "libftprintf.h"
#include "op.h"
#include <unistd.h>
#include <stdlib.h>

//macro for representation of arg type ?
/*
 * #define T_DIR 0x01
 * #define T_IND 0x02
 * #define T_REG 0x03
 *
 * */
typedef	unsigned long long t_ull;
typedef	unsigned long long t_uc;

typedef struct	s_champ;
{
	char	name[PROG_NAME_LENGTH + 1];
	char	comment[COMMENT_LENGTH + 1];
	int		id; // this should be created in init and copied in r0
	int		prcs_c;
	int		live_c;
}				t_champ;

typedef struct	s_process
{
	int		id;
	int		prcs_id;
	t_uc	*regs[REG_NUMBER];
	int		wait_c;
	int		is_alive;
	t_uc	*pc;
	int		carry;
}				t_process;

enum	e_argtype
{
	// if we want to represent this by 3 bit, change to defined T_DIR/T_IND/T_REG
	reg;
	dir;
	ind;
};

typedef struct	s_arg
{
	e_argtype	type;
	t_ull		value;
}				t_arg;

typedef struct	s_op
{
	char		opcode;
	int			n_args; //nbr of args
	int			*args;
	int			carry; //can modify the carry or not
	int			wait;
	int			rstrct; //if %mod should be aplied or not, memory restriction

	//probably need more like "what arg type is allowed"
	//maybe a nbr to represent (3 bit for types and check by &)
}				t_op;

typedef struct	s_inst;
{
	t_op	*op;
	t_arg	arg1;
	t_arg	arg2;
	t_arg	arg3;
}				t_inst;

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
