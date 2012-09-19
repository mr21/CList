NAME		=	libCList.so

CC		=	gcc
CFLAGS		=	-Wall -Wextra -ansi -pedantic -fPIC
CFLAGS		+=	-Iinc/

RM		=	@rm -f

SRC		=	src/

OBJ		+=	$(SRC)CList_init.o
OBJ		+=	$(SRC)CLink_getters.o
OBJ		+=	$(SRC)CList_getters.o
OBJ		+=	$(SRC)CList_clear.o
OBJ		+=	$(SRC)CList_count.o
OBJ		+=	$(SRC)CList_foreach.o
OBJ		+=	$(SRC)CList_find.o
OBJ		+=	$(SRC)CList_pop.o
OBJ		+=	$(SRC)CList_push.o
OBJ		+=	$(SRC)CList_merge.o
OBJ		+=	$(SRC)CList_cut.o
OBJ		+=	$(SRC)CList_move.o

$(NAME)		:	$(OBJ)
			$(CC) -o $(NAME) $(OBJ) -shared

all		:	$(NAME)

clean		:
			$(RM) $(OBJ)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean $(NAME)

.PHONY		:	all clean fclean re
