SRCS = main.c parsing.c fdf_cleanup.c fdf_draw.c fdf_init.c	\
		fdf_input.c fdf_map.c fdf_utils.c parsing_utils.c

OBJS = $(SRCS:.c=.o)

CC = gcc -Ilibft -Imlx
CFLAGS = -Wextra -Wall -Werror -Ilibft -Iminilibx-linux -I/usr/include -O3

NAME = fdf
INCLUDES = ./libft

%o: %c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	$(MAKE) -C ./minilibx-linux
	$(CC) $(OBJS) -lm -Llibft -lft -Lminilibx-linux -lmlx -L/usr/lib -Iminilibx-linux -lXext -lX11 -lm -lz -o $(NAME) -Ilibft

clean:
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ./minilibx-linux
	rm -rf *.o

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -rf $(NAME)

re: fclean all
