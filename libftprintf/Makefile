NAME = libftprintf.a

CC = gcc 

CFLAGS = -Wall -Werror -Wextra -g
#CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g

INCLUDES = includes
HEADER = $(addprefix includes/, libftprintf.h ft_avl.h)

FTSRC = ft_lstiter.c    ft_putchar.c    ft_strdel.c     ft_strnew.c  ft_lstlast.c  \
		ft_putchar_fd.c ft_strdup.c     ft_strnstr.c ft_atoi.c  ft_lstlen.c        \
		ft_putendl.c    ft_strequ.c     ft_strrchr.c ft_bzero.c      ft_lstmap.c   \
		ft_putendl_fd.c ft_striter.c    ft_strsplit.c ft_isalnum.c    ft_lstnew.c  \
		ft_putnbr.c     ft_striteri.c   ft_strstr.c ft_isalpha.c    ft_memalloc.c  \
		ft_putnbr_fd.c  ft_strjoin.c    ft_strsub.c ft_isascii.c    ft_memccpy.c   \
		ft_putstr.c     ft_strlcat.c    ft_strtrim.c ft_isdigit.c    ft_memchr.c   \
		ft_putstr_fd.c  ft_strlen.c     ft_tolower.c ft_isprint.c    ft_memcmp.c   \
		ft_sqrt.c       ft_strmap.c     ft_toupper.c ft_itoa.c       ft_memcpy.c   \
		ft_strcat.c     ft_strmapi.c   ft_lstadd.c     ft_memdel.c     ft_strchr.c \
		ft_strncat.c ft_lstat.c      ft_memmove.c    ft_strclr.c     ft_strncmp.c  \
		ft_lstdel.c     ft_memset.c     ft_strcmp.c     ft_strncpy.c ft_lstdelone.c\
		ft_power.c      ft_strcpy.c     ft_strnequ.c ft_lstpushback.c ft_lstfind.c \
		ft_lstdelof.c ft_strjoinfree.c ft_strupper.c ft_strndup.c ft_strsubfree.c \
		ft_atozu.c		ft_max.c ft_deltab.c get_next_line.c ft_min.c ft_lstsort.c \
		ft_isnumeric.c 	ft_atoill.c \
		ft_atollu.c ft_qappend.c ft_qnew.c ft_qpop.c ft_qdel.c  \
		ft_qpush.c ft_lstsub.c ft_lstinsert.c ft_qclear.c ft_lstnomallocnew.c

FTIOSRC=$(addprefix ft_printf/, ft_printf.c convertion.c setting.c process_csp.c \
		fraction.c process_ld.c \
		ft_dbtoa.c process_precision.c ft_ldtoa.c arithfrac.c ft_ldtolltoa.c     \
		process_doux.c ft_lltoa.c process_e.c process_f.c process_flag.c 		 \
		 ft_sprintf.c ft_dprintf.c ft_asprintf.c ft_snprintf.c)

FTAVLSRC=$(addprefix avlsrc/,	ft_avladd.c	ft_avlfind.c	ft_avlnomallocnew.c	\
		ft_avlheight.c	ft_avlnew.c		ft_treedel.c	lrotate.c      rrotate.c)

FTIOOBJ=$(FTIOSRC:.c=.o)
FTAVLOBJ=$(FTAVLSRC:.c=.o)
OBJ = $(FTSRC:.c=.o) 


%.o:%.c $(HEADER)
	$(CC) $(CFLAGS) -I $(INCLUDES) -o $@ -c $<

.PHONY: all fclean clean

RM = rm -f 

$(NAME): $(OBJ) $(FTIOOBJ) $(FTAVLOBJ)
	ar rcs $(NAME) $(OBJ) $(FTIOOBJ) $(FTAVLOBJ)

all: $(NAME)

clean:
	$(RM) $(OBJ)
	$(RM) $(FTIOOBJ)
	$(RM) $(FTAVLOBJ)


fclean: clean
	$(RM) $(NAME)

re: fclean all
