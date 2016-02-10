SRC =	main.c \
	core/util.c \
	core/client.c \
	core/game.c \
	core/log.c

NAME =	softwars
OBJO =	$(SRC:%.c=%.o)
OBJC =	$(SRC)
CFLAGS = -W -Werror -Wall

all:	$(NAME)

$(NAME):	$(OBJO)
	gcc -W -Werror -Wall $(OBJO) -o $(NAME) -L. -lmy -pthread

clean:
	rm -f $(OBJO)
fclean:		clean
	rm -f $(NAME)

re:	fclean all
