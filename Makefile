# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/30 13:41:26 by mnishimo          #+#    #+#              #
#    Updated: 2019/05/30 17:22:39 by mnishimo         ###   ########.fr        #
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
		 decode.c ocp.c free.c lst_util.c util.c) \
		 #$(addprefix src/vm/instructions/, inst_live.c inst_ld.c inst_.c inst_.c inst_.c inst_.c inst_.c inst_.c inst_.c inst_.c inst_.c inst_.c inst_.c)

VM_OBJ = $(VM_SRC:src/vm/%.c=obj/%.o)

.PHONY: all fclean clean re

all: $(VM_NAME)

$(LIBFT):
	make -C libftprintf/

obj/%.o: src/vm/%.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(VM_NAME): $(LIBFT) $(VM_OBJ)
	$(CC) $(CFLAGS)  -o $(VM_NAME) $(VM_OBJ) $(LDIR) $(INCLUDES)

clean:
	$(RM) $(VM_OBJ)
	make -C libftprintf/ clean

fclean: clean
	$(RM) $(VM_NAME)
	make -C libftprintf/ fclean

re: fclean all
