/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:51:52 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/04 17:06:44 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# define BUFF_SIZE 2048

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
	int			args[MAX_ARGS_NUMBER];
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
void	update_caller(t_process *caller, t_op *op)
/*
 * decode.c
 * */
t_uc	*decode(t_uc *dump, t_uc *pc, t_inst *inst);


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

/*
 * instruction functions
 * */
void	inst_live(t_game *game, t_process *caller, t_inst *inst);
void	inst_ld(t_game *game, t_process *caller, t_inst *inst);
void	inst_st(t_game *game, t_process *caller, t_inst *inst);
void	inst_add(t_game *game, t_process *caller, t_inst *inst);
void	inst_sub(t_game *game, t_process *caller, t_inst *inst);
void	inst_and(t_game *game, t_process *caller, t_inst *inst);
void	inst_or(t_game *game, t_process *caller, t_inst *inst);
void	inst_xor(t_game *game, t_process *caller, t_inst *inst);
void	inst_zjmp(t_game *game, t_process *caller, t_inst *inst);
void	inst_ldi(t_game *game, t_process *caller, t_inst *inst);
void	inst_sti(t_game *game, t_process *caller, t_inst *inst);
void	inst_fork(t_game *game, t_process *caller, t_inst *inst);
void	inst_lld(t_game *game, t_process *caller, t_inst *inst);
void	inst_lldi(t_game *game, t_process *caller, t_inst *inst);
void	inst_lfork(t_game *game, t_process *caller, t_inst *inst);
void	inst_aff(t_game *game, t_process *caller, t_inst *inst);



/*
 * ASM PART
 * */

typedef enum	e_tkn_type
{
	e_cmd_name,
	e_cmd_comment,
	e_op,
	e_label,
	e_register,
	e_ind_label,
	e_ind_value,
	e_dir_label,
	e_dir_value,
	e_separator,
	e_carriage_return,
	e_eof,
}				t_tkn_type;

typedef	struct	s_tkn
{
	int			lc_instruction;
	int			lc_token;
	int			buff_start;
	int			buff_end;
	int			mem_size;
	void		*value; //case of indirect | direct
	t_tkn_type	type;
	s_token		*next; //list
}				t_tkn;

typedef	struct	s_lbl
{
	char		*name;
	char		type // D - Defined or U - Undefined
	int			lc_label;
	t_token		*param_list;
	s_labels	*next;
}				t_lbl;

typedef struct	s_pos
{
	int			line;
	int			col; // char?
	int			lc_instruction;
	int			lc_token;
	int			state_l;
	int			state_s;
}				t_pos;


typedef void (*tkn_create_func)(char *, t_position *, int);

void	tkn_label(char *buff, t_pos *pos, t_lbl *labels, t_tkn *token);
void	tkn_register(char *buff, t_pos *pos, t_lbl *labels, t_tkn *token);
void	tkn_op(char *buff, t_pos *position, t_lbl *labels, t_tkn *token);
void	tkn_dir_value(char *buff, t_pos *pos, t_lbl *labels, t_tkn *token);
void	tkn_dir_label(char *buff, t_pos *pos, t_lbl *labels, t_tkn *token);
void	tkn_ind_value(char *buff, t_pos *pos, t_lbl *labels, t_tkn *token);
void	tkn_ind_label(char *buff, t_pos *pos, t_lbl *labels, t_tkn *token);
void	tkn_cmd(char *buff, t_pos *pos, t_lbl *labels, t_tkn *token);
void	tkn_separator(char *buff, t_pos *pos, t_lbl *labels, t_tkn *token);
void	tkn_carr_ret(char *buff, t_pos *pos, t_lbl *labels, t_tkn *token);

#endif
