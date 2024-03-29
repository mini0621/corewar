/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <allefebv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:51:52 by mnishimo          #+#    #+#             */
/*   Updated: 2019/07/02 16:24:06 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# define BUFF_SIZE_COR 2048
# define OP_TAB_ASM_SIZE 16
# define NB_TKN_TYPES 11
# define SPACE_CHAR " \t\v\f\r"
# define NB_LSM_COL 13
# define IO_ERROR 1
# define OPT_ERROR 2
# define ML_ERROR 3
# define US_ERROR 0
# define CLR_RED  "\x1b[31m"
# define CLR_GREEN  "\x1b[32m"
# define CLR_YEL  "\x1b[33m"
# define KWTH	"\x1B[0m"

# include "libftprintf.h"
# include "op.h"
# include "visu.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>

typedef	unsigned long long	t_ull;
typedef	unsigned char		t_uc;
typedef	uint32_t			t_ucc;
typedef uint8_t				t_din;
typedef	uint8_t				t_reg_type;
typedef uint16_t			t_ind_type;
typedef uint32_t			t_dir_type;
typedef	uint8_t				t_ocp;

typedef struct				s_champ
{
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	int				fd;
	short			n_id;
	unsigned int	prog_size;
	short			id;
	int				prcs_c;
	int				live_c;
}							t_champ;

typedef enum				e_argtype
{
	e_reg = T_REG,
	e_dir = T_DIR,
	e_ind = T_IND,
}							t_argtype;

typedef union				u_argval
{
	t_reg_type	u_reg_val;
	t_ind_type	u_ind_val;
	t_dir_type	u_dir_val;
}							t_argval;

typedef enum				e_opcode
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
}							t_opcode;

typedef struct				s_arg
{
	t_argtype	type;
	t_argval	value;
}							t_arg;

typedef struct				s_option
{
	char	option[6];
	int		(*f)();
}							t_option;

typedef struct				s_process
{
	int			c_id;
	int			p_id;
	t_uc		op;
	t_dir_type	regs[REG_NUMBER];
	int			wait_c;
	int			is_alive;
	t_uc		*pc;
	int			carry;
}							t_process;

typedef struct				s_instr_dec
{
	t_arg_type				type;
	int32_t					data_dump;
	size_t					size;
}							t_instr_dec;

typedef struct				s_opdis
{
	char					*name;
	int						nb_args;
	t_arg_type				arg_types[MAX_ARGS_NUMBER];
	int						num_value;
	int						nb_cycles;
	char					*description;
	int						param_byte;
	int						index_status;
}							t_opdis;

typedef struct				s_single_instr
{
	t_opdis					*op;
	t_ocp					*new_pc;
	t_instr_dec				args[4];
}							t_single_instr;

typedef struct				s_instr_node
{
	t_uc					pos;
	t_single_instr			*instr;
}							t_instr_node;

typedef struct				s_file
{
	char					name[PROG_NAME_LENGTH + 1];
	char					comment[COMMENT_LENGTH + 1];
	int						dis_state;
	int						col;
	t_list					*instr_nodes;
	unsigned char			*raw_dump;
	int						fd;
	unsigned int			prog_size;
	char					*file_name;
	char					*output_file;
}							t_file;

typedef struct				s_inst_store
{
	int						size;
	char					*instr;
}							t_inst_store;

typedef	struct				s_dis_game
{
	t_file					*file[MAX_PLAYERS + 1];
	t_list					*store;
	t_visu					*visu;
	t_ucc					dismemdump[CHAMP_MAX_SIZE];
	int						nbr_champs;
	int						pv_number;
	int						length;
	int						deb_state;
	int						visu_state;
}							t_dis_game;

typedef struct				s_game
{
	t_champ					*champs[MAX_PLAYERS + 1];
	t_arr					*prcs;
	t_ull					nbr_prcs;
	t_ull					nbr_cycle;
	int						nbr_champs;
	int						d_state;
	int						n_state;
	t_ull					pl_number;
	int						deb_state;
	int						print_off;
	char					*logs;
	size_t					logs_len;
	int						pv_number;
	t_ull					live_count;
	t_ull					prcs_count;
	t_ull					cycle;
	t_ull					cycle_d;
	t_ull					check_c;
	t_ull					cycle_to_die;
	int						winner;
	t_visu					*visu;
	t_uc					memdump[MEM_SIZE];
}							t_game;

typedef struct				s_inst
{
	void	*op;
	t_arg	args[MAX_ARGS_NUMBER];
}							t_inst;

typedef	void				(*t_inst_func)(t_game *, t_process *, t_inst *);

typedef struct				s_op
{
	t_opcode	opcode;
	int			n_args;
	int			args[MAX_ARGS_NUMBER];
	int			wait;
	int			ocp;
	int			rstrct;
	int			carry;
	int			dir_bytes;
	t_inst_func	function;
}							t_op;

int							init_corewar(t_game *game, int ac, char **av);

int							process(t_game *game);

int							prcs_new(t_game *game, int c_id, t_uc *pc,
							t_arr *arr);
void						prcs_cpy(t_process *dst, t_process *src);

void						prcs_inst(t_game *game, size_t p_index);
int							decode_wait(t_uc *pc);

t_uc						*decode(t_uc *dump, t_uc *pc, t_inst *inst);
t_op						*decode_op(t_uc pc);

int							decode_ocp(t_uc *addr, t_inst *inst);
void						deb_32_util(t_game *game, char **tmp
							, t_process *caller, int *l);
void						free_game(t_game *game);
int							deb_ld_util(t_process *caller
							, t_inst *inst, char **tmp, int val);
t_op						*get_op(t_inst *inst);
void						update_logs(t_game *game, char **new, size_t l);
void						memcpy_inv(void *dst, void *src, size_t size);
void						ft_hexdump(t_uc *dump);
void						reset_prcs_c(t_game *game);

t_uc						*access_ptr(t_uc *dump, t_uc *pc, int offset);
void						read_dump(t_uc *dump, t_uc *src, void *dst,
							size_t size);
void						write_dump(t_uc *dump, void *src, t_uc *dst,
							size_t size);
t_dir_type					*get_arg(t_process *caller, t_uc *dump,
							t_arg *arg, int rstr);
void						endian_conv(void *value, size_t size);

void						del_lstprcs(void *cnt, size_t size);

void						vm_init_flags(t_game *game);
t_ull						vm_get_value(char *sval);
int							vm_catch_error(int flag, char *av);
int							vm_file_reader(char *file, t_game *game,
							int *flag, int *index);
void						vm_sort_champ_id(t_game *game);
int							vm_is_player(char *str);
void						vm_debug(int flag, int ac, char **av, t_game *game);
unsigned int				vm_endian_conversion(unsigned int val);
int							vm_opt_reader(int *ac, char **av, t_game *game,
							int *flag);
int							vm_opt_dump(int *index, char **av, t_game *game);
int							vm_opt_print(int *index, char **av, t_game *game);
int							vm_opt_debug(int *index, char **av, t_game *game);
int							vm_opt_visu(int *index, char **av, t_game *game);
int							vm_opt_n(int *index, char **av, t_game *game);
int							vm_primary_parser(int fd, t_game *game);

void						inst_live(t_game *game, t_process *caller,
							t_inst *inst);
void						inst_ld(t_game *game, t_process *caller,
							t_inst *inst);
void						inst_st(t_game *game, t_process *caller,
							t_inst *inst);
void						inst_add(t_game *game, t_process *caller,
							t_inst *inst);
void						inst_sub(t_game *game, t_process *caller,
							t_inst *inst);
void						inst_and(t_game *game, t_process *caller,
							t_inst *inst);
void						inst_or(t_game *game, t_process *caller,
							t_inst *inst);
void						inst_xor(t_game *game, t_process *caller,
							t_inst *inst);
void						inst_zjmp(t_game *game, t_process *caller,
							t_inst *inst);
void						inst_ldi(t_game *game, t_process *caller,
							t_inst *inst);
void						inst_sti(t_game *game, t_process *caller,
							t_inst *inst);
void						inst_fork(t_game *game, t_process *caller,
							t_inst *inst);
void						inst_lld(t_game *game, t_process *caller,
							t_inst *inst);
void						inst_lldi(t_game *game, t_process *caller,
							t_inst *inst);
void						inst_lfork(t_game *game, t_process *caller,
							t_inst *inst);
void						inst_aff(t_game *game, t_process *caller,
							t_inst *inst);

void						end_visu(t_visu *visu);
int							output(t_game *game);
void						update_all(t_game *game, t_visu *visu);
void						init_visu(t_game *game, t_visu *visu);
void						draw_dump(t_game *game, t_visu *win);
void						draw_menu(t_game *game, t_visu *wind);
void						update_clr(t_game *game, int dst, size_t size,
							int id);
void						draw_debug(t_game *game, t_visu *visu);

void						get_debug(t_game *game, t_champ *champ, int id);
void						reset_debug(t_game *game);
void						print_debug(t_game *game);
void						debug_hex(void *dst, size_t size);

void						debug_carry(t_game *game, int p_id,
							int c_id, int carry);
char						*add_head(char **log, int p_id, int c_id, int *l);

void						deb_8_log(t_game *game, t_inst *inst,
							t_process *caller, int val);
void						deb_16_log(t_game *game, t_inst *inst,
							t_process *caller, int val);
void						deb_32_log(t_game *game, t_inst *inst,
							t_process *caller, int res);
void						deb_64_log(t_game *game, t_inst *inst,
							t_process *caller, int p_id);

int							dis_source_parser(int fd, char *file
							, t_dis_game *game);
int							dis_catch_error(int flag, char *av);
int							dis_multi_util(t_dis_game *game, int p_num);
int16_t						dis_endian_convert_16(int16_t val);
int32_t						dis_endian_convert_32(int32_t val);
int							dis_check_endianness(int value);
void						dis_print_node(t_visu *win, t_dis_game *game);
t_single_instr				*dis_decode_handler(t_ocp *pc);
void						dis_sub_handler(t_dis_game *game, int p_num);
int							dis_write_output(t_dis_game *game, int p_num);
int							dis_load_player(t_dis_game *game);
void						dis_debug(t_dis_game *game, int p_num);
int							dis_file_reader(char *file, t_dis_game *game
							, int *flag, int *index);
int							dis_get_instr(t_dis_game *game, t_instr_node *node);
unsigned int				dis_endian_conversion(unsigned int val);
void						dis_end_visu(t_visu *visu);
int							dis_output(t_dis_game *game, int p_num, int *flag);
void						dis_visu_launcher(t_dis_game *game
							, t_visu *visu, int p_num);
void						dis_init_visu(t_dis_game *game
							, t_visu *visu, int pl_num);
int							free_all(t_dis_game *game);
void						del_store(void *content, size_t size);
int							opcode_is_valid(t_uc x);
int							reg_is_valid(int x);

typedef enum				e_errors
{
	e_no_error,
	e_no_print,
	e_lexical_error,
	e_syntactic_error,
	e_input_error,
	e_malloc_error,
	e_open_error,
	e_close_error,
	e_invalid_command_error,
	e_comment_too_long_error,
	e_name_too_long_error,
	e_write_error,
	e_reg_nb_error,
	e_op_code_error,
	e_dir_int_error,
	e_dir_short_error,
	e_ind_error,
	e_double_label,
	e_empty_file,
	e_no_instruction,
	e_usage,
}							t_errors;

typedef enum				e_tkn_type
{
	e_cmd_name,
	e_cmd_comment,
	e_op,
	e_lbl,
	e_register,
	e_ind_label,
	e_ind_value,
	e_dir_label,
	e_dir_value,
	e_separator,
	e_carriage_return,
	e_eof,
}							t_tkn_type;

typedef struct				s_op_asm
{
	int			n_args;
	int			ocp;
	int			dir_bytes;
	char		*name;
	int			op_state_s;
	char		op_code;
}							t_op_asm;

typedef	struct				s_tkn
{
	t_tkn_type	type;
	int			lc_inst;
	int			lc_tkn;
	int			buff_start;
	int			buff_end;
	int			col_start;
	int			col_end;
	int			mem_size;
	void		*value;
	t_op_asm	*op;
	int			line;
}							t_tkn;

typedef	struct				s_lbl
{
	char		*name;
	char		type;
	int			lc_lbl_inst;
	t_list		*frwd;
}							t_lbl;

typedef struct				s_pos
{
	int			file_line;
	int			file_col;
	int			buf_pos;
	int			size_buf;
	int			tab_counter;
	int			lc_inst;
	int			lc_tkn;
	int			dir_bytes;
	int			ocp;
	int			arg_nbr;
	int			multiple_line;
	int			state_l;
	int			state_s;
	int			previous_st_s;
	int			name_len;
	int			comment_len;
	int			size_line;
	char		*tmp_buf;
	char		*file_name;
	int			content;
	int			end_read;
	int			error_print;
}							t_pos;

typedef struct				s_bytebf
{
	char		*bytebuf;
	char		*header;
	int			hd_size;
	char		*magic;
	char		name[PROG_NAME_LENGTH];
	char		offset1[4];
	char		*prog_size;
	char		comment[COMMENT_LENGTH];
	char		offset2[4];
	char		*inst;
	int			inst_remain;
	int			inst_size;
}							t_bytebf;

extern char					g_lsm_col[13][26];
extern int					g_lex_sm[30][14];
extern int					g_syntactic_sm[59][14];
extern t_op_asm				g_op_tab_asm[16];

typedef int					(*t_tkn_fptr)(char *buf, t_pos *pos, t_list **lbl,
							t_tkn **tkn);

int							tkn_label(char *buff, t_pos *pos, t_list **lbls,
							t_tkn **tkn);
int							tkn_register(char *buff, t_pos *pos, t_list **lbls,
							t_tkn **tkn);
int							tkn_op(char *buff, t_pos *pos, t_list **lbls,
							t_tkn **tkn);
int							tkn_dir_value(char *buf, t_pos *pos, t_list **lbls,
							t_tkn **tkn);
int							tkn_dir_label(char *buf, t_pos *pos, t_list **lbls,
							t_tkn **tkn);
int							tkn_ind_value(char *buf, t_pos *pos, t_list **lbls,
							t_tkn **tkn);
int							tkn_ind_label(char *buf, t_pos *pos, t_list **lbls,
							t_tkn **tkn);
int							tkn_cmd(char *buf, t_pos *pos, t_list **lbls,
							t_tkn **tkn);
int							tkn_separator(char *buf, t_pos *pos, t_list **lbls,
							t_tkn **tkn);
int							tkn_carr_ret(char *buf, t_pos *pos, t_list **lbls,
							t_tkn **tkn);

void						ocp_modify(t_pos *pos, char *bytebuf);
int							end_lbl(t_list *lbls, t_pos *pos);
int							ft_write_output(t_bytebf *bytebf, t_pos *pos,
							char *name);
int							final_state(t_pos *pos, t_tkn **tkn, char *buf,
							t_list **lbls);
int							tkn_create(char *buf, t_pos *pos, t_list **lbls,
							t_tkn **tkn);
int							bytebuf_realloc(t_bytebf *bytebf, t_pos *pos,
							t_tkn **tkn);
int							ft_init_main(t_list **lbls, t_bytebf *bytebf,
							char **line, t_pos *pos);
int							init_before_analysis(t_pos *pos, char **read_line);
void						free_after_analysis(t_pos *pos, char **read_line);
int							lexical_analysis(t_pos *pos, t_tkn **tkn,
							t_list **lbls);
int							syntactic_analysis(t_list **lbls, t_pos *pos,
							t_bytebf *bytebf, t_tkn **tkn);
char						*get_tkn_type_name(t_tkn_type tkn_type);

void						ocp_create(t_tkn *tkn, t_pos *pos, char *bybf);
void						gaps_fill(char *bytebuf, t_tkn *tkn);
void						command_buf_fill(t_bytebf *bytebf, t_tkn *tkn,
							t_pos *pos);
void						bytecode_gen(t_tkn *tkn, t_bytebf *bytebf,
							t_pos *pos);

int							ft_error(t_pos *pos, t_errors error, t_tkn **tkn);
void						display(t_pos *pos, t_tkn *tkn, char *error,
							char *msg);
void						system_error(t_pos *pos, t_errors error);
void						header_error(t_pos *pos, t_tkn *tkn,
							t_errors error);
void						command_error(t_pos *pos, t_tkn *tkn,
							t_errors error);
void						input_error(t_pos *pos, t_errors error);

void						del_lbls(void *content, size_t size);
void						free_tkn(t_tkn **tkn);
void						del_tkn(void *content, size_t size);
void						free_bytebf_pos(t_bytebf *bytebf, t_pos *pos);
int							read_bytes(char **line, int error, const int fd);

#endif
