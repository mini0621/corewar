/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:51:52 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/19 12:53:17 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

#include "libftprintf.h"
#include "op.h"
#include "visu.h"
#include <unistd.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
# define IO_ERROR 1
# define OPT_ERROR 2
# define ML_ERROR 3
# define US_ERROR 0
# define CLR_RED  "\x1b[31m"
# define CLR_GREEN  "\x1b[32m"
# define CLR_YEL  "\x1b[33m"
typedef	unsigned long long	t_ull;
typedef	unsigned char	t_uc;
typedef	uint8_t				t_reg_type;
typedef uint16_t			t_ind_type;
typedef uint32_t			t_dir_type;
typedef	uint8_t				t_ocp;

typedef struct		s_champ
{
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	int				fd;
	unsigned int	prog_size;
	short			id;
	int				prcs_c;
	int				live_c;
}				t_champ;

typedef struct	s_process
{
	int			c_id;
	int			p_id; // this might be useless
	t_dir_type	regs[REG_NUMBER];
	int			wait_c;
	int			is_alive;
	t_uc		*pc;
	int			carry;
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
	t_reg_type	u_reg_val;
	t_ind_type	u_ind_val;
	t_dir_type	u_dir_val;
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

typedef struct  s_option
{
        char    option[3];
        int     (*f)();
}               t_option;

typedef struct	s_game
{
	t_champ		*champs[MAX_PLAYERS + 1]; // the last ptr is NULL
	t_list		*prcs; //cache coherence and use t_list? young prcs is top
	t_ull		nbr_prcs;
	t_ull		nbr_cycle;
	int			nbr_champs;
	int			nbr_d_cycle; //-d option number of cycles to run before memory dump
	int			d_state;//-d option
	int			n_state;//-n flag for specifying the number of the following
						//player and also states the order of execution
	int			pl_state;
	t_ull		pl_number; //store the value which follows the -n flag 
	int			deb_state;
	char		*logs;
	size_t		logs_len;
	int			pv_number; //keeps track of the previous player number
	t_ull		live_count;
	t_ull		prcs_count;
	int			prev_champ;
	t_ull		cycle;
	t_ull		cycle_d;
	t_ull		check_c;
	t_ull		cycle_to_die;
	t_visu		*visu;
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
 * prcs_util.c
 * */
t_list	*prcs_new(t_game *game, int c_id);
void	prcs_cpy(t_process *dst, t_process *src, t_uc *addr);

/*
 * instructions.c
 * */
void	prcs_inst(t_game *game, t_process *caller);
int		decode_wait(t_uc *pc);
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
void	update_logs(t_game *game, char **new, size_t l);
void	memcpy_inv(void *dst, void *src, size_t size);
void	ft_hexdump(t_uc *dump);
void    reset_prcs_c(t_game *game);

/*
 * memory_utils.c
 * */
t_uc	*access_ptr(t_uc *dump, t_uc *pc, int offset);
void	read_dump(t_uc *dump, t_uc *src, void *dst, size_t size);
void	write_dump(t_uc *dump, void *src, t_uc *dst, size_t size);
t_dir_type	*get_arg(t_process *caller, t_uc *dump, t_arg *arg, int rstr);
void	endian_conv(void *value, size_t size);

/*
 * lst_util.c
 * */
void	del_lstprcs(void *cnt, size_t size);

/*
 *	Parser utility functions
 * */
void            		vm_init_flags(t_game *game);
t_ull               	vm_get_value(char *sval);
int                     vm_catch_error(int flag, char *av);
int                     vm_file_reader(char *file, t_game *game, int *flag, int *index);
void                	vm_debug(int flag, int ac, char **av, t_game *game);
unsigned int			vm_endian_conversion(unsigned int val);
int	                    vm_opt_reader(int *ac, char **av, t_game *game, int *flag);
int                     vm_opt_dump(int *index, char **av, t_game *game);
int                     vm_opt_debug(int *index, char **av, t_game *game);
int                     vm_opt_visu(int *index, char **av, t_game *game);
int                     vm_opt_n(int *index, char **av, t_game *game);
int                 	vm_primary_parser(int fd, t_game *game);

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
 * visu
*/
void	end_visu(t_visu *visu);
int		output(t_game *game);
void	update_all(t_game *game, t_visu *visu);
void    init_visu(t_game *game, t_visu *visu);
void	        draw_dump(t_game *game, t_visu *win);
void            draw_menu(t_game *game, t_visu *wind);
void	update_clr(t_game *game, int dst, size_t size, int id);
void	draw_debug(t_game *game, t_visu *visu);

/*
 *debug
 * */
void	get_debug(t_game *game, t_champ *champ);
void	reset_debug(t_game *game);
void	print_debug(t_game *game);
void	debug_hex(void *dst, size_t size);

/*
 *debug inst
 * */
void	deb_8_log(t_game *game, t_inst *inst, t_process *caller, int val);
void	deb_16_log(t_game *game, t_inst *inst, t_process *caller, int val);
void	deb_32_log(t_game *game, t_inst *inst, t_process *caller, int res);
void	deb_64_log(t_game *game, t_inst *inst, t_process *caller, int p_id);
#endif
