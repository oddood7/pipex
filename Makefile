NAME			=	pipex

CC				=	gcc

FLAGS			=	-Wall -Wextra -Werror -g

C_FILE			=	child_process.c pipex.c close_free.c

SRC_DIR			=	./src/

SRC				=	$(addprefix $(SRC_DIR),$(C_FILE))

OBJS			=	$(SRC:.c=.o)

LIBFT_FILE		=	libft.a

LIBFT_PATH		=	./libft/

LIBFT_LIB		=	$(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

.c.o:
		$(CC) $(FLAGS) -c $< -o $@

all:		$(NAME)

lib:
		@echo "\033[0;33m\nCOMPILING $(LIBFT_PATH)\n"	
		@make -C $(LIBFT_PATH)
		@echo "\033[1;32m\n\nlibft.a CREATED\n"	

$(NAME):	$(OBJS) lib
			@echo "\033[0;33m\nCOMPILING PIPEX...\n"	
			$(CC) $(FLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME)
			@echo "\033[1;32m\n\n./pipex CREATED\n"	


clean:
		@make clean -sC $(LIBFT_PATH)
		@rm -f $(OBJS)

fclean:	clean
		@make fclean -C $(LIBFT_PATH)
		@rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
