SRC		=	srcs/main.c srcs/parsing.c srcs/utils.c srcs/utils_1.c srcs/child.c srcs/error.c srcs/init.c \

OBJ		=	$(SRC:.c=.o)

CC		=	cc
RM		=	rm -rf
CFLAGS	=	-Wall -Werror -Wextra -I./includes

NAME	=	pipex

all:	$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $(NAME)

clean:
			$(RM) $(OBJ)

fclean:	clean
			$(RM) $(NAME)

re:		fclean $(NAME)

.PHONY:		all clean fclean re