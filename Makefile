SRCS = main.c parsing.c fdf_cleanup.c fdf_draw.c fdf_init.c	\
		fdf_input.c fdf_map.c fdf_utils.c parsing_utils.c

OBJs = $(SRCS:.c=.o)

CC = gcc
FLAGS = -Wextra -Wall -Werror

NAME = test.out

%.o: %.c
	$(CC) $(FLAGS) -Imlx -c $< -o $@

all: $(NAME)

$(NAME): $(SRCS)
#$(CC) $(SRCS) -Llibft -lft -Lminilibx-linux -lmlx -L/usr/lib -Iminilibx-linux -lXext -lX11 -lm -lz -o $(NAME) -Ilibft
	$(CC) $(SRCS) -Lmlx_macos -lmlx -Llibft -lft -framework OpenGL -framework AppKit -o $(NAME) -Imlx_macos -Ilibft
#$(CC) $(SRCS) -Lminilibx-linux -lminilibx-linux -Llibft -lft -framework OpenGL -framework AppKit -o $(NAME) -Iminilibs-linux -Ilibft

clean:
	rm -rf *.o

fclean:
	rm -rf $(NAME)
