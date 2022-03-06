SRCS = main.c parsing.c

OBJs = $(SRCS:.c=.o)

CC = gcc
FLAGS = -Wextra -Wall -Werror

NAME = test.out

%.o: %.c
	$(CC) $(FLAGS) -Imlx -c $< -o $@

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(SRCS) -Lmlx -lmlx -Llibft -lft -framework OpenGL -framework AppKit -o $(NAME) -Imlx -Ilibft

clean:
	rm -rf *.o

fclean:
	rm -rf $(NAME)