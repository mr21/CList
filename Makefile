NAME		=	libCList.a

CC		=	gcc
CFLAGS		=	-Wall -Wextra -ansi -pedantic -g
CFLAGS		+=	-Iinc/

RM		=	@rm -f

SRC		=	src/CList_init.c		\
			src/CList_clear.c		\
			src/CList_find_data.c		\
			src/CList_find_n_destroy.c	\
			src/CList_foreach.c		\
			src/CList_pop.c			\
			src/CList_push.c		\

OBJ		=	$(SRC:.c=.o)

$(NAME)		:	$(OBJ)
			ar rcs $(NAME) $(OBJ)

all		:	$(NAME)

clean		:
			$(RM) $(OBJ)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean $(NAME)

.PHONY		:	all clean fclean re
