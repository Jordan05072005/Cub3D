SRC = srcs/error.c srcs/free.c srcs/main.c srcs/parser.c srcs/init.c srcs/minimap.c srcs/utils.c \
	srcs/projection.c srcs/brain.c srcs/frame.c srcs/draw_groundsky.c srcs/collision.c

OBJ = ${SRC:.c=.o}

LIBFT_DIR = libft

MLX_DIR = mlx

FRAMEWORK = -L$(MLX_DIR) -lmlx -Imlx -lXext -lX11 -lm -lz

.c.o:
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o}

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
NAME = cub3D

all : ${NAME}

${NAME}: ${OBJ}
	@make -C $(LIBFT_DIR)
	@make -C $(MLX_DIR)
	@${CC} ${CFLAGS} ${OBJ} $(FRAMEWORK) -o ${NAME} -L$(LIBFT_DIR) -lft

clean : 
	@${RM} srcs/*o
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)

fclean : clean
	@${RM} ${NAME}
	@make fclean -C $(LIBFT_DIR)

re : fclean all clean

.PHONY: all clean fclean re