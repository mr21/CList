NAME		=	libCList.a

CC		=	gcc
CFLAGS		=	-Wall -Wextra -ansi -pedantic
CFLAGS		+=	-Iinc/

RM		=	@rm -f

SRC		=	src/CList_init.c	\
			src/CLink_getters.c	\
			src/CList_getters.c	\
			src/CList_clear.c	\
			src/CList_foreach.c	\
			src/CList_find.c	\
			src/CList_pop.c		\
			src/CList_push.c	\
			src/CList_merge.c	\
			src/CList_cut.c		\

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
