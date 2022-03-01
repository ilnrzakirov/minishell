NAME	=	minishell

SRCS	=	src/minishell.c				src/utils.c					src/error.c\
			src/exe/exe.c				src/exe/utils.c				src/builtins/echo_env.c\
			src/signals/signal.c		src/exe/buildins_hub.c\
			src/builtins/pwd.c			src/builtins/cd.c			src/builtins/exit.c\
			src/builtins/export.c		src/builtins/unset.c		src/utils2.c\
			src/here_doc/here_doc.c		src/parser/error_parser.c	src/parser/parser.c\
			src/parser/parser_pipe.c	src/parser/parser_redirects.c\
			src/parser/utils_parser.c	src/parser/preparser.c		src/parser/correct_line.c\
			src/builtins/export2.c		src/exe/exe2.c				src/here_doc/get_next_line.c

LIB 	=	./lib/libft.a

HEADER	=	includes/minishell.h ./lib/libft.h

RM		=	rm -f

OBJS	=	$(SRCS:.c=.o)

GCC		= clang

CFLAGS	=	-Wall -Wextra -Werror

FLAG	=	-lreadline -ltermcap -g -L/Users/$(USER)/.brew/opt/readline/lib/ -I/Users/$(USER)/.brew/opt/readline/include

$(NAME)	:	$(OBJS) $(HEADER)
			@$(MAKE) -C ./lib
			@$(GCC) $(CFLAGS) $(OBJS) $(LIB) $(FLAG) -o ${NAME}
			@echo "\033[0;32m-----Successful success!-----"

.PHONY	:	all clean fclean re

all		:	$(NAME)

clean	:
			@$(RM) $(OBJS)
			@$(MAKE) clean -C ./lib
			@echo "\033[0;32m-------Clean completed-------"

fclean	:	clean
			@$(RM) $(NAME)
			@echo "\033[0;32m------Fclean completed-------"

re		:	fclean all