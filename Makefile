# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/30 13:41:26 by mnishimo          #+#    #+#              #
#    Updated: 2019/07/02 13:27:32 by allefebv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VM_NAME		=	corewar
ASM_NAME	=	asm
DIS_NAME	=	disassembler
LIBFT		=	libftprintf.a
OBJ_DIR		=	obj

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

RM			=	rm -rf
LDIR		=	-L libftprintf/ -lftprintf
INCLUDES	=	-I includes/  -I libftprintf/includes

HEADER		=	$(addprefix includes/, corewar.h op.h)

VM_SRC		=	$(addprefix src/vm/, main.c init_corewar.c process.c instructions.c	\
		 	decode.c ocp.c free.c lst_util.c util.c memory_util.c prcs_util.c		\
		 	vm_error_utils.c vm_file_reader.c vm_mem_utils.c vm_option_utils.c		\
		 	vm_parser_model.c vm_primary_parser.c debug_util.c						\
		 	debug.c debug_inst.c) $(addprefix src/vm/visu/, output.c visu_util.c	\
		 	visu_dump.c visu_menu.c init_visu.c visu_debug.c)

DIS_SRC		=	$(addprefix src/dis/, main.c decode.c dis_decode_utils.c			\
		 	dis_gen_utils.c dis_error_utils.c dis_multi_utils.c vm_visu_utils.c		\
		 	dis_parser_util_sub.c dis_parser_utils.c dis_source_parser.c			\
		 	dis_visu_extr.c vm_visu_output.c dis_free.c)

VM_INST_SRC	=	$(addprefix src/vm/instructions/, inst01_live.c inst02_ld.c			\
			inst03_st.c inst04_add.c inst05_sub.c inst06_and.c inst07_or.c			\
			inst08_xor.c inst09_zjmp.c inst0a_ldi.c inst0b_sti.c inst0c_fork.c		\
			inst0d_lld.c inst0e_lldi.c inst0f_lfork.c inst10_aff.c)

ASM_SRC		=	$(addprefix src/asm/, asm_main.c finished_state_machines.c			\
			read_asm.c ocp_management.c	utils.c bytecode_management.c				\
			tkn_create_1.c tkn_create_2.c tkn_create_3.c tkn_create_4.c				\
			end_functions.c	initializations.c free_fncs.c tkn_creations.c			\
			lexical_analysis.c syntactic_analysis.c error.c error_types.c			\
			error_display.c)

ASM_OBJ		=	$(ASM_SRC:src/asm/%.c=obj/asm/%.o)

VM_OBJ		=	$(VM_SRC:src/%.c=obj/%.o)
DIS_OBJ		=	$(DIS_SRC:src/%.c=obj/%.o)
VM_INST_OBJ	=	$(VM_INST_SRC:src/vm/instruction/%.c=obj/%.o)

.PHONY: all fclean clean re

all: libft $(VM_NAME) $(ASM_NAME) $(DIS_NAME)

libft:
	make -C libftprintf/

$(OBJ_DIR):
	mkdir $(OBJ_DIR)
	mkdir $(OBJ_DIR)/vm/
	mkdir $(OBJ_DIR)/vm/visu
	mkdir $(OBJ_DIR)/asm/
	mkdir $(OBJ_DIR)/dis/

obj/vm/%.o: src/vm/%.c $(HEADER) $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

obj/dis/%.o: src/dis/%.c $(HEADER) $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

obj/asm/%.o: src/asm/%.c $(HEADER) $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(ASM_NAME): $(ASM_OBJ)
	make -C libftprintf/
	$(CC) $(CFLAGS)  -o $(ASM_NAME) $(ASM_OBJ) $(LDIR) $(INCLUDES)

$(VM_NAME): $(VM_OBJ) $(VM_INST_OBJ)
	make -C libftprintf/
	$(CC) $(CFLAGS)  -o $(VM_NAME) $(VM_OBJ) $(VM_INST_OBJ) $(LDIR) $(INCLUDES) -lncurses

$(DIS_NAME): $(DIS_OBJ)
	make -C libftprintf/
	$(CC) $(CFLAGS)  -o $(DIS_NAME) $(DIS_OBJ) $(LDIR) $(INCLUDES) -lncurses

clean:
	$(RM) $(OBJ_DIR)
	make -C libftprintf/ clean

fclean: clean
	$(RM) $(VM_NAME) $(ASM_NAME) $(DIS_NAME)
	make -C libftprintf/ fclean

re: fclean all
