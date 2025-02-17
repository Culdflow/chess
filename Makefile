CC = cc
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address
NAME = chess
CFILES = srcs/main.c \
\
		srcs/board/board.c \
\
		srcs/render/draw.c \
		srcs/render/images.c \
		srcs/render/images_utils.c \
\
		srcs/vector/vector.c \
		srcs/vector/vector_utils.c \
\
		srcs/moves/moves.c \
		srcs/moves/pion.c \
		srcs/moves/moves_render.c \

OBJS = ${CFILES:.c=.o}

.c.o:
	${CC} ${CFLAGS} -Iminilibx -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS}
	$(CC) ${CFLAGS} $(OBJS) -Lminilibx -lmlx -L/usr/lib -Iminilibx -lXext -lX11 -lm -lz -o $(NAME)

fclean:	clean
	rm -rf ${NAME}

clean:
	rm -rf ${OBJS}

re:	fclean all

.PHONY: all clean fclean re