NAME		=	libCList.so

CC		=	gcc
CFLAGS		=	-Wall -Wextra -ansi -pedantic
CFLAGS		+=	-fPIC
CFLAGS		+=	-Iinc/

RM		=	@rm -f

OBJ		+=	src/CList_init.o
OBJ		+=	src/CLink_getters.o
OBJ		+=	src/CList_getters.o
OBJ		+=	src/CList_clear.o
OBJ		+=	src/CList_count.o
OBJ		+=	src/CList_foreach.o
OBJ		+=	src/CList_find.o
OBJ		+=	src/CList_pop.o
OBJ		+=	src/CList_push.o
OBJ		+=	src/CList_merge.o
OBJ		+=	src/CList_cut.o
OBJ		+=	src/CList_move.o

$(NAME)		:	$(OBJ)
			$(CC) -o $(NAME) $(OBJ) -shared

all		:	$(NAME)

clean		:
			$(RM) $(OBJ)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean $(NAME)

.PHONY		:	all clean fclean re
