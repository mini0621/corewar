/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:51:52 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/30 18:12:13 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

#include "libftprintf.h"
#include "op.h"
#include <unistd.h>
#include <stdlib.h>

typedef	unsigned long long	t_ull;
typedef	unsigned long long	t_uc;
typedef	uint8_t				t_reg_type;
typedef uint16_t			t_ind_type;
typedef uint32_t			t_dir_type;
typedef	uint8_t				t_ocp;

typedef struct	s_champ
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

typedef enum	e_argtype
{
	// if we want to represent this by 3 bit, change to defined T_DIR/T_IND/T_REG
	e_reg = T_REG,
	e_dir = T_DIR,
	e_ind = T_IND,
}				t_argtype;

typedef union	u_argval
{
	t_reg_type	reg_val;
	t_ind_type	ind_val;
	t_dir_type	dir_val;
}				t_argval;

typedef enum	e_opcode
{
	e_err,
	e_live,
	e_ld,
	e_st,
	e_add,
	e_sub,
	e_and,
	e_or,
	e_xor,
	e_zjmp,
	e_ldi,
	e_sti,
	e_fork,
	e_lld,
	e_lldi,
	e_lfork,
	e_aff,
}				t_opcode;

typedef struct	s_arg
{
	t_argtype	type;
	t_argval	value;
}				t_arg;

typedef struct	s_game
{
	t_champ		*champs[MAX_PLAYERS + 1]; // the last ptr is NULL
	t_list		*prcs; //cache coherence and use t_list? young prcs is top
	t_ull		nbr_cycle;
	int			nbr_champs;
	t_ull		cycle;
	t_ull		cycle_d;
	t_ull		c_checked;
	t_ull		cycle_to_die;
	t_uc		memdump[MEM_SIZE];
}				t_game;

typedef struct	s_inst
{
	void	*op;
	t_arg	args[MAX_ARGS_NUMBER];
}				t_inst;

typedef	void (*t_inst_func)(t_game *, t_process *, t_inst *);

typedef struct	s_op
{
	t_opcode	opcode;
	int			n_args; //nbr of args
	int			*args; 
	int			wait;
	int			ocp;
	int			rstrct; //if %mod should be aplied or not, memory restriction
	int			carry; //can modify the carry or not
	int			dir_bytes;
	t_inst_func	function;
}				t_op;

/*
 * init_corewar.c
 * */
int		init_corewar(t_game *game, int ac, char **av);

/*
 * process.c
 * */
int		process(t_game *game);

/*
 * instructions.c
 * */
void	prcs_inst(t_game *game, t_process *caller);
void	update_caller(t_process *caller, t_op *op);

/*
 * decode.c
 * */
int		decode(t_uc *dump, t_uc *pc, t_inst *inst);


/*
 * ocp.c
 * */
int		decode_ocp(t_uc *addr, t_inst *inst);

/*
 * free.c
 * */
void	free_game(t_game *game);

/*
 * util.c
 * */
t_op	*get_op(t_inst *inst);

/*
 * lst_util.c
 * */
void	del_lstprcs(void *cnt, size_t size);
#endif
