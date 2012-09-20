NAME		=	a.out
CC		=	gcc
CFLAGS		=	-Wall -Wextra -ansi -pedantic -I../inc/
LDFLAGS		=	../libCList.so

RM		=	@rm -f

OBJ		=	demo.o

$(NAME)		:	$(OBJ)
			$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

all		:	$(NAME)

clean		:
			$(RM) $(OBJ)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean $(NAME)

.PHONY		:	all clean fclean re
