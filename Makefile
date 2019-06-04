# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/30 13:41:26 by mnishimo          #+#    #+#              #
#    Updated: 2019/05/30 18:58:07 by mnishimo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VM_NAME = corewar
LIBFT = libftprintf.a

CC = gcc -g
#CFLAGS = -Wall -Werror -Wextra
#CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
CFLAGS = -g -fsanitize=address

RM = rm -f
LDIR = -L libftprintf/ -lftprintf
INCLUDES = -I includes/  -I libftprintf/includes

HEADER =  $(addprefix includes/, corewar.h op.h)

VM_SRC = $(addprefix src/vm/, main.c init_corewar.c process.c instructions.c \
		 decode.c ocp.c free.c lst_util.c util.c) 
VM_INST_SRC = $(addprefix src/vm/instructions/, inst01_live.c inst02_ld.c \
		inst03_st.c inst04_add.c inst05_sub.c inst06_and.c inst07_or.c \
		inst08_xor.c inst09_zjmp.c inst0a_ldi.c inst0b_sti.c inst0c_fork.c \
		inst0d_lld.c inst0e_lldi.c inst0f_lfork.c inst10_aff.c)

VM_OBJ = $(VM_SRC:src/vm/%.c=obj/%.o)
VM_INST_OBJ = $(VM_INST_SRC:src/vm/instruction/%.c=obj/%.o)

.PHONY: all fclean clean re

all: $(VM_NAME)

$(LIBFT):
	make -C libftprintf/

obj/%.o: src/vm/%.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(VM_NAME): $(LIBFT) $(VM_OBJ) $(VM_INST_OBJ)
	$(CC) $(CFLAGS)  -o $(VM_NAME) $(VM_OBJ) $(VM_INST_OBJ) $(LDIR) $(INCLUDES)

clean:
	$(RM) $(VM_OBJ)
	make -C libftprintf/ clean

fclean: clean
	$(RM) $(VM_NAME)
	make -C libftprintf/ fclean

re: fclean all
