NAME	=	minishell

SRCS	=	src/minishell.c			src/utils.c		src/get.c\
			src/error.c

LIB 	=	./libft/libft.a

HEADER	=	includes/minishell.h ./libft/libft.h

RM		=	rm -f

OBJS	=	$(SRCS:.c=.o)

GCC		= clang

CFLAGS	=	

FLAG	=	-lreadline -ltermcap -g -L/Users/$(USER)/.brew/opt/readline/lib/ -I/Users/$(USER)/.brew/opt/readline/includ

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