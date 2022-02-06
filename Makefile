NAME	=	minishell

SRCS	=	src/minishell.c				src/utils.c					src/error.c\
			src/exe/exe.c				src/exe/utils.c				src/builtins/echo_env.c\
			src/lst_func.c				src/lst_func2.c				src/signals/signal.c\
			src/builtins/pwd.c			src/builtins/cd.c			src/builtins/exit.c\
			src/prepars/prepars.c		src/utils2.c				src/parsing/parsing.c\
			src/parsing/pars_utils.c	src/parsing/dollar_rep.c

LIB 	=	./lib/libft.a

HEADER	=	includes/minishell.h ./lib/libft.h includes/exe.h

RM		=	rm -f

OBJS	=	$(SRCS:.c=.o)

GCC		= clang

CFLAGS	=	

FLAG	=	-lreadline -ltermcap -g -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include

$(NAME)	:	$(OBJS) $(HEADER)
			@$(GCC) $(CFLAGS) $(OBJS) $(LIB) $(FLAG) -o ${NAME}
			@$(RM) $(OBJS)
			@echo "\033[0;32m-----Successful success!-----"

.PHONY	:	all clean fclean re

all		:	$(NAME)

clean	:
			@$(RM) $(OBJS)
			@$(MAKE) clean -C ./libft
			@echo "\033[0;32m-------Clean completed-------"

fclean	:	clean
			@$(RM) $(NAME)
			@echo "\033[0;32m------Fclean completed-------"

re		:	fclean all
